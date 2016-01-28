//
//  edi_parsing_traversal.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//
#include "edi_parsing.h"

#define getCname(rstring) RSTRING_PTR(rb_funcall((rstring),id_force_8_bit,0))

static int nameSortFunc(const void *p1, const void*p2);
static void indexSegment(parser_t *parser, segment_t *segment, int *segmentCount, int depth);
static bool hasProperty(segment_t *segment,  short element, short component, char *value);
static int nameIndexFunc(const void *p1, const void*p2);

static ID id_force_8_bit;

void buildIndexes(parser_t *parser){
  int segmentCount = 0;
  parser->byName = ediParsingMalloc(parser->segmentCount,sizeof(segment_t*));
  parser->primaryIndex = ediParsingMalloc(parser->segmentCount,sizeof(segment_t*));
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
  parser->nameIndex = ediParsingMalloc(parser->nameCount,sizeof(index_stat_t));
  memcpy(parser->nameIndex,&tmp, parser->nameCount*sizeof(index_stat_t));
}

VALUE propertiesToHash(segment_t *segment){
  VALUE hash = rb_hash_new();
  unsigned long key;
  unsigned long value;
  char key_string[MAX_KEY_SIZE];
  short element = 0;
  short component = 0;
  VALUE sym;
  for(element=1;element<=segment->elements; element++){
    for(component=0; component<100; component++){
      key = getPropertyKey(element,component);
      if(st_lookup(segment->propertyCache, key, &value)){
        if(0 == component){
          sprintf(key_string, "%s%02i", segment->name, element);
        }else{
          sprintf(key_string, "%s%02i_%02i", segment->name, element, component);
        }
        sym = ID2SYM(rb_intern(key_string));
        rb_hash_aset(hash, sym, rb_str_new_cstr((char*)(value)));
      }else{
        break;
      }
    }
  }
  return hash;
}

VALUE segmentWhere(parser_t *parser, segment_t *segment, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb, VALUE limit_rb){
  VALUE result = rb_ary_new();

  if(segment->children > 0){
    short element = NUM2SHORT(element_int_rb);
    short component = NUM2SHORT(component_int_rb);
    char *c_name = getCname(name_rb);
    index_stat_t stat = nameIndexSearch(parser, c_name);
    if(stat.lower > -1 && stat.upper > -1){
      int max = (stat.upper - stat.lower) + 1;
      char *value = getCname(value_rb);
      const int limit = NUM2INT(limit_rb);
      int cnt = 0;
      segment_t *descendant;
      for(int i=0;i<max;i++){
        if(limit > -1 && cnt >= limit) break;
        descendant = parser->byName[i+stat.lower];
        if(isDescendantOf(descendant, segment) && hasProperty(descendant, element, component, value)){
          VALUE child_rb = buildSegmentNode(parser, descendant);
          rb_ary_push(result, child_rb);
          cnt++;
        }
      }
    }
  }
  return result;
}

VALUE segmentExists(parser_t *parser, segment_t *segment, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb){
  if(segment->children > 0){
    short element = NUM2SHORT(element_int_rb);
    short component = NUM2SHORT(component_int_rb);
    char *c_name = getCname(name_rb);
    index_stat_t stat = nameIndexSearch(parser, c_name);
    if(stat.lower > -1 && stat.upper > -1){
      int max = (stat.upper - stat.lower) + 1;
      char *value = getCname(value_rb);
      segment_t *descendant;
      for(int i=0;i<max;i++){
        descendant = parser->byName[i+stat.lower];
        if(isDescendantOf(descendant, segment) && hasProperty(descendant, element, component, value)){
          return Qtrue;
        }
      }
    }
  }
  return Qfalse;
}

VALUE segmentChildren(parser_t *parser, segment_t *segment, VALUE names_rb, VALUE limit_rb){
  VALUE result = rb_ary_new();
  const int length = NUM2INT(rb_funcall(names_rb, rb_intern("length"), 0));
  const int limit = NUM2INT(limit_rb);
  segment_t *descendant;
  int cnt = 0;

  if(length == 0){
    descendant = segment->firstSegment;
    while(NULL != descendant && (limit == -1 || cnt < limit)){
      VALUE child_rb = buildSegmentNode(parser, descendant);
      rb_ary_push(result, child_rb);
      descendant = descendant->tail;
      cnt++;
    }
  }else{
    VALUE name = rb_ary_pop(names_rb);
    char *c_name;
    index_stat_t stat;
    while(name != Qnil && (limit == -1 || cnt < limit)){
      c_name = getCname(name);
      stat = nameIndexSearch(parser, c_name);
      int max = (stat.upper - stat.lower) + 1;
      if(stat.lower > -1 && stat.upper > -1){
        for(int i=0;i<max;i++){
          if(limit > -1 && cnt >= limit) break;
          descendant = parser->byName[i+stat.lower];
          if(isChildOf(descendant, segment)){
            VALUE child_rb = buildSegmentNode(parser, descendant);
            rb_ary_push(result, child_rb);
            cnt++;
          }
        }
      }
      name = rb_ary_pop(names_rb);
    }
  }
  return result;
}

VALUE segmentToHash(segment_t *segment){
  segment_t *child = segment->firstSegment;
  VALUE proxy = propertiesToHash(segment);
  VALUE children = rb_ary_new();

  if(NULL != child){
    while(NULL != child){
      rb_ary_push(children, segmentToHash(child));
      child = child->tail;
    }
    rb_hash_aset(proxy, ID2SYM(rb_intern("children")), children);
  }

  rb_hash_aset(proxy, ID2SYM(rb_intern("name")), rb_str_new_cstr(segment->name));
  return proxy;
}

VALUE segmentFind(parser_t *parser, segment_t *segment, VALUE names_rb, VALUE limit_rb){
  VALUE result = rb_ary_new();
  const int length = NUM2INT(rb_funcall(names_rb, rb_intern("length"), 0));
  const int limit = NUM2INT(limit_rb);
  segment_t *descendant;
  int cnt = 0;

  if(length == 0){
    int max = (segment->boundary - segment->pkey) + 1;
    for(int i=1;i<max;i++){
      if(limit > -1 && cnt >= limit) break;
      descendant = parser->primaryIndex[i+segment->pkey];
      if(descendant->pkey > segment->pkey && descendant->pkey <= segment->boundary){
        VALUE child_rb = buildSegmentNode(parser, descendant);
        rb_ary_push(result, child_rb);
      }
    }
  }else{
    VALUE name = rb_ary_pop(names_rb);
    char *c_name;
    index_stat_t stat;
    while(name != Qnil && (limit == -1 || cnt < limit)){
      c_name = getCname(name);
      stat = nameIndexSearch(parser, c_name);
      int max = (stat.upper - stat.lower) + 1;
      if(stat.lower >= 0 && stat.upper >= 0){
        for(int i=0;i<max;i++){
          if(limit > -1 && cnt >= limit) break;
          descendant = parser->byName[i+stat.lower];
          if(isDescendantOf(descendant, segment)){
            VALUE child_rb = buildSegmentNode(parser, descendant);
            rb_ary_push(result, child_rb);
            cnt++;
          }
        }
      }
      name = rb_ary_pop(names_rb);
    }
  }
  return result;
}

VALUE segmentGetProperty(segment_t *segment, VALUE element_int_rb, VALUE component_int_rb){
  short element = NUM2SHORT(element_int_rb);
  short component = NUM2SHORT(component_int_rb);
  unsigned long key = getPropertyKey(element,component);
  unsigned long value; 
  if(st_lookup(segment->propertyCache, key, &value)){
    return rb_str_new_cstr((char*)value);
  }else{
    return Qnil;
  }
}

index_stat_t nameIndexSearch(parser_t *parser, const char *name){
  index_stat_t stat;
  stat.upper = -1;
  stat.lower = -1;
  strcpy(stat.name, name);
  index_stat_t *rtn = bsearch(&stat, parser->nameIndex, parser->nameCount, sizeof(index_stat_t), nameIndexFunc);
  return rtn ? *rtn : stat;
}

static int nameSortFunc(const void *p1, const void*p2){  
  const segment_t *seg1 = *((segment_t **)p1);
  const segment_t *seg2 = *((segment_t **)p2);
  const int cmp = strcmp(seg1->name, seg2->name);

  if(cmp == 0){
    return (seg1->pkey - seg2->pkey);
  }else{
    return cmp;
  }
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

static bool hasProperty(segment_t *segment,  short element, short component, char *value){
  unsigned long hash_value;
  unsigned long key = getPropertyKey(element, component);
  if(st_lookup(segment->propertyCache, key, &hash_value)){
    return strcmp(value, (char*)hash_value) == 0;
  }else{
    return false;
  }
}

void init_edi_parsing_traversal(){
  id_force_8_bit = rb_intern("b");
}

