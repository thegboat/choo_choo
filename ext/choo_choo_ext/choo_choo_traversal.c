//
//  choo_choo_traversal.c
//  choo_choo
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//
#include "choo_choo.h"

#define getCname(rstring) RSTRING_PTR(rb_funcall((rstring),id_force_8_bit,0))

static int nameSortFunc(const void *p1, const void*p2);
static void indexSegment(parser_t *parser, segment_t *segment, int *segmentCount, int depth);
static inline bool hasProperty(segment_t *segment,  short element, short component, char *value);
static int nameIndexFunc(const void *p1, const void*p2);

static VALUE mChooChoo;
static VALUE cSegment;

static ID id_force_8_bit;
static ID id_length;
static ID id_iv_cache;
static VALUE sym_name;
static VALUE sym_children;



VALUE buildSegmentNode(parser_t *parser, segment_t *segment){
  VALUE segment_rb,class_rb, cache, cache_key = ULONG2NUM(segment->pkey);
  anchor_t *anchor;
  cache = rb_ivar_get(parser->doc,id_iv_cache);
  segment_rb = rb_hash_aref(cache, cache_key);

  if(segment_rb == Qnil){
    class_rb = rb_define_class_under(mChooChoo, segment->name, cSegment);
    segment_rb = rb_class_new_instance(0, NULL, class_rb);

    Data_Get_Struct(segment_rb, anchor_t, anchor);
    anchor->parser = parser;
    anchor->segment = segment;
    rb_hash_aset(cache, cache_key, segment_rb);
  }
  return segment_rb;
}

static inline VALUE buildSegmentNodes(parser_t *parser, segment_t **segments, int len){
  VALUE ary = rb_ary_new_capa(len);
  for(int i=0; i<len;i++){
    rb_ary_store(ary, i, buildSegmentNode(parser, segments[i]));
  }
  return ary;
}

void buildIndexes(parser_t *parser){
  int segmentCount = 0;
  parser->byName = choo_chooMalloc(parser->segmentCount,sizeof(segment_t*));
  parser->primaryIndex = choo_chooMalloc(parser->segmentCount,sizeof(segment_t*));
  index_stat_t tmp[parser->segmentCount];
  indexSegment(parser, parser->root, &segmentCount, 0);
  qsort(parser->byName, parser->segmentCount, sizeof(segment_t*), nameSortFunc);

  long index_i=-1;
  segment_t* segment;

  for(long data_i=0; data_i<parser->segmentCount; data_i++){
    segment = parser->byName[data_i];
    if(index_i == -1 || strcmp(tmp[index_i].name,segment->name)){
      index_i++;
      tmp[index_i].lower = data_i;
      tmp[index_i].upper = data_i;
      strcpy(tmp[index_i].name,segment->name);
    }else{
      tmp[index_i].upper = data_i;
    }
  }

  parser->nameCount = index_i+1;
  parser->nameIndex = choo_chooMalloc(parser->nameCount,sizeof(index_stat_t));
  memcpy(parser->nameIndex,tmp, parser->nameCount*sizeof(index_stat_t));
}

VALUE propertiesToHash(segment_t *segment){
  VALUE hash = rb_hash_new();
  char *ptr;
  char key_string[MAX_KEY_SIZE];
  short element = 0;
  short component = 0;
  VALUE sym;
  for(element=1;element<=segment->elements; element++){
    for(component=0; component<100; component++){
      if((ptr = propertyLookup(segment, element, component))){
        if(0 == component){
          sprintf(key_string, "%s%02i", segment->name, element);
        }else{
          sprintf(key_string, "%s%02i_%02i", segment->name, element, component);
        }
        sym = ID2SYM(rb_intern(key_string));
        rb_hash_aset(hash, sym, rb_str_new_cstr(ptr));
      }else{
        break;
      }
    }
  }
  return hash;
}

VALUE segmentWhere(parser_t *parser, segment_t *segment, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb, VALUE limit_rb){
  short element,component;
  char *c_name, *value;
  index_stat_t stat;
  int max, cnt = 0;
  segment_t *descendant;
  int limit = NUM2INT(limit_rb);
  if(limit == -1) limit = (segment->boundary-segment->pkey)+1;
  segment_t *descendants[limit];

  if(segment->children > 0){
    c_name = getCname(name_rb);
    stat = nameIndexSearch(parser, c_name);
    if(stat.lower > -1 && stat.upper > -1){
      element = NUM2SHORT(element_int_rb);
      component = NUM2SHORT(component_int_rb);
      max = (stat.upper - stat.lower)+1;
      value = getCname(value_rb);
      for(int i=0;i<max;i++){
        if(cnt >= limit) break;
        descendant = parser->byName[i+stat.lower];
        if(isDescendantOf(descendant, segment)){
          if(hasProperty(descendant, element, component, value)){
            descendants[cnt] = descendant;
            cnt++;
          }
        }else if(descendant->pkey > segment->boundary){
          break;
        }
      }
    }
  }
  return buildSegmentNodes(parser, descendants, cnt);
}

VALUE segmentExists(parser_t *parser, segment_t *segment, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb){
  short element, component;
  char *c_name, *value;
  index_stat_t stat;
  int max;
  segment_t *descendant;
  if(segment->children > 0){
    element = NUM2SHORT(element_int_rb);
    component = NUM2SHORT(component_int_rb);
    c_name = getCname(name_rb);
    stat = nameIndexSearch(parser, c_name);
    if(stat.lower > -1 && stat.upper > -1){
      max = (stat.upper - stat.lower)+1;
      value = getCname(value_rb);
      for(int i=0;i<max;i++){
        descendant = parser->byName[i+stat.lower];
        if(descendant->pkey > segment->boundary){
          return Qfalse;
        }else if(isDescendantOf(descendant, segment) && hasProperty(descendant, element, component, value)){
          return Qtrue;
        }
      }
    }
  }
  return Qfalse;
}

VALUE segmentChildren(parser_t *parser, segment_t *segment, VALUE names_rb, VALUE limit_rb){
  VALUE name, child_rb;
  int length = NUM2INT(rb_funcall(names_rb, id_length, 0));
  int limit = NUM2INT(limit_rb);
  if(limit == -1) limit = segment->children;
  segment_t *children[limit];
  segment_t *descendant;
  int max, lower, cnt = 0;
  char *c_name;
  index_stat_t stat;

  if(length == 0){
    descendant = segment->firstSegment;
    while(NULL != descendant && cnt < limit){
      children[cnt] = descendant;
      descendant = descendant->tail;
      cnt++;
    }
  }else{
    name = rb_ary_pop(names_rb);
    while(name != Qnil && cnt < limit){
      c_name = getCname(name);
      stat = nameIndexSearch(parser, c_name);
      max = (stat.upper - stat.lower)+1;
      if(stat.lower > -1 && stat.upper > -1){
        for(int i=0;i<max;i++){
          if(limit > -1 && cnt >= limit) break;
          descendant = parser->byName[i+stat.lower];
          if(isChildOf(descendant, segment)){
            children[cnt] = descendant;
            cnt++;
          }else if(descendant->pkey > segment->boundary){
            break;
          } 
        }
      }
      name = rb_ary_pop(names_rb);
    }
  }
  return buildSegmentNodes(parser, children, cnt);
}

VALUE segmentToHash(segment_t *segment){
  segment_t *child = segment->firstSegment;
  VALUE proxy = propertiesToHash(segment);
  VALUE children = rb_ary_new_capa(segment->children);

  if(NULL != child){
    while(NULL != child){
      rb_ary_push(children, segmentToHash(child));
      child = child->tail;
    }
    rb_hash_aset(proxy, sym_children, children);
  }

  rb_hash_aset(proxy, sym_name, rb_str_new_cstr(segment->name));
  return proxy;
}

VALUE segmentFind(parser_t *parser, segment_t *segment, VALUE names_rb, VALUE limit_rb){
  VALUE name;
  int length = NUM2INT(rb_funcall(names_rb, id_length, 0));
  int limit = NUM2INT(limit_rb);
  segment_t *descendant;
  if(limit == -1) limit = (segment->boundary - segment->pkey) + 1;
  segment_t *descendants[limit];
  int max, cnt = 0;
  char *c_name;
  index_stat_t stat;

  if(length == 0){
    int max = (segment->boundary - segment->pkey) + 1;
    for(int i=1;i<max;i++){
      if(limit > -1 && cnt >= limit) break;
      descendants[cnt] = parser->primaryIndex[i+segment->pkey];
      cnt++;
    }
  }else{
    name = rb_ary_pop(names_rb);
    while(name != Qnil && cnt < limit){
      c_name = getCname(name);
      stat = nameIndexSearch(parser, c_name);
      max = (stat.upper - stat.lower) + 1;
      if(stat.lower >= 0 && stat.upper >= 0){
        for(int i=0;i<max;i++){
          if(limit > -1 && cnt >= limit) break;
          descendant = parser->byName[i+stat.lower];
          if(isDescendantOf(descendant, segment)){
            descendants[cnt] = descendant;
            cnt++;
          }else if(descendant->pkey > segment->boundary){
            break;
          } 
        }
      }
      name = rb_ary_pop(names_rb);
    }
  }
  return buildSegmentNodes(parser, descendants, cnt);
}

VALUE segmentGetProperty(segment_t *segment, VALUE element_int_rb, VALUE component_int_rb){
  short element = NUM2SHORT(element_int_rb);
  short component = NUM2SHORT(component_int_rb);
  char *ptr = propertyLookup(segment, element, component);
  return (ptr ? rb_str_new_cstr(ptr) : Qnil);
}

index_stat_t nameIndexSearch(parser_t *parser, const char *name){
  index_stat_t stat;
  strcpy(stat.name,name);
  index_stat_t *rtn = bsearch(&stat, parser->nameIndex, parser->nameCount, sizeof(index_stat_t), nameIndexFunc);
  if(NULL == rtn){
    stat.upper = -1;
    stat.lower = -1;
    return stat;
  }
  return *rtn;
}

static int nameSortFunc(const void *p1, const void*p2){  
  const segment_t *seg1 = *((segment_t **)p1);
  const segment_t *seg2 = *((segment_t **)p2);
  const int cmp = strcmp(seg1->name, seg2->name);

  return cmp ? cmp : (seg1->pkey - seg2->pkey);
}

static int nameIndexFunc(const void *p1, const void*p2){  
  const index_stat_t stat1 = *((index_stat_t *)p1);
  const index_stat_t stat2 = *((index_stat_t *)p2);
  return strcmp(stat1.name, stat2.name);
}

static void indexSegment(parser_t *parser, segment_t *segment, int *segmentCount, int depth){
  segment_t *child = segment->firstSegment;
  segment->pkey = *segmentCount;
  segment->depth = depth;
  parser->byName[*segmentCount] = segment;
  parser->primaryIndex[*segmentCount] = segment;
  *segmentCount = *segmentCount + 1;
  long key;

  while(NULL != child){
    indexSegment(parser, child, segmentCount, depth+1);
    child = child->tail;
  }
  segment->boundary = (*segmentCount) - 1;
}

bool missingSegment(parser_t *parser, char *src){
  index_stat_t stat = nameIndexSearch(parser, src);
  return stat.lower < 0 || stat.upper < 0;
}

int segmentsWithName(parser_t *parser, char *src){
  index_stat_t stat = nameIndexSearch(parser, src);
  return (stat.lower < 0 || stat.upper < 0) ? 0 : ((stat.upper - stat.lower) + 1);
}

static inline bool hasProperty(segment_t *segment,  short element, short component, char *value){
  char *hash_value = propertyLookup(segment, element, component);
  return (hash_value ? !strcmp(value, hash_value) : false);
}

char *propertyLookup(segment_t *segment,  short element, short component){
  unsigned long value;
  unsigned long key = getPropertyKey(element, component);
  if(st_lookup(segment->propertyCache, key, &value)){
    return (char*)value;
  }else{
    return NULL;
  }
}

void init_choo_choo_traversal(){
  mChooChoo = rb_define_module("ChooChoo");
  cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  id_iv_cache = rb_intern("@segment_cache");
  id_force_8_bit = rb_intern("b");
  id_length = rb_intern("length");
  sym_children =ID2SYM(rb_intern("children"));
  sym_name =ID2SYM(rb_intern("name"));
}

