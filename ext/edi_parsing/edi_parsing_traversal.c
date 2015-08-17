//
//  edi_parsing_traversal.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_parsing.h"

static int littleUSearch(parser_t *parser, const char *name, int idx);
static int littleLSearch(parser_t *parser, const char *name, int idx);
static index_stat_t nameIndexSearch(parser_t *parser, const char *name);
static int nameIndexFunc(const void *p1, const void*p2);
static void indexSegment(parser_t *parser, segment_t *segment, int *segmentCount, int depth);
static void allocIndexes(parser_t *parser);
static const int getNodeKey(VALUE segment_rb);
static segment_t *getNode(parser_t *parser, VALUE segment_rb);

void buildIndexes(parser_t *parser, segment_t *root){
  int segmentCount = 0;
  int propertyCount = 0;
  allocIndexes(parser);
  indexSegment(parser, root, &segmentCount, 0);
  qsort(parser->nameIndex, parser->segmentCount, sizeof(segment_t*), nameIndexFunc);
}

VALUE propertiesToHash(property_t *property){
  VALUE hash = rb_hash_new();
  while(NULL != property){
    VALUE key = ID2SYM(rb_intern(property->key));
    rb_hash_aset(hash, key, rb_str_new_cstr(property->value));
    property = property->tail;
  }
  return hash;
}

VALUE segmentChildren(parser_t *parser, VALUE segment_rb, VALUE names){
  segment_t *segment = getNode(parser, segment_rb);
  segment_t *child = segment->firstSegment;
  VALUE children = rb_ary_new();

  if(NULL != child){
    VALUE isa = rb_iv_get(segment_rb, ISA_LINK);
    while(NULL != child){
      VALUE child_rb = buildSegmentNode(isa, child);
      rb_ary_push(children, child_rb);
      child = child->tail;
    }
  }

  return children;
}

VALUE segmentParent(parser_t *parser, VALUE segment_rb){
  segment_t *segment = getNode(parser, segment_rb);
  if(NULL == segment->parent){
    return Qnil;
  }else{
    VALUE isa = rb_iv_get(segment_rb, ISA_LINK);
    return buildSegmentNode(isa, segment->parent);
  }
}

VALUE segmentToHash(segment_t *segment){
  segment_t *child = segment->firstSegment;
  VALUE proxy = propertiesToHash(segment->firstProperty);
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

VALUE segmentFind(parser_t *parser, VALUE segment_rb, VALUE names){
  const segment_t *segment = getNode(parser, segment_rb);
  VALUE result = rb_ary_new();
  const int length = NUM2INT(rb_funcall(names, rb_intern("length"), 0));
  VALUE isa = rb_iv_get(segment_rb, ISA_LINK);
  segment_t *descendant;

  if(length == 0){
    int max = (segment->boundary - segment->pkey) + 1;
    for(int i=1;i<max;i++){
      descendant = parser->primaryIndex[i+segment->pkey];
      VALUE child_rb = buildSegmentNode(isa, descendant);
      rb_ary_push(result, child_rb);
    }
  }else{
    VALUE name = rb_ary_pop(names);
    char *c_name;
    index_stat_t stat;
    while(name != Qnil){
      c_name = StringValueCStr(name);
      stat = nameIndexSearch(parser, c_name);
      int max = (stat.upper - stat.lower) + 1;
      if(stat.upper > -1){
        for(int i=0;i<max;i++){
          descendant = parser->nameIndex[i+stat.upper];
          if(descendant->pkey > segment->pkey && descendant->pkey <= segment->boundary){
            VALUE child_rb = buildSegmentNode(isa, descendant);
            rb_ary_push(result, child_rb);
          }
        }
      }
      name = rb_ary_pop(names);
    }
  }
  return result;
}

static index_stat_t nameIndexSearch(parser_t *parser, const char *name){
  index_stat_t stat = {-1,-1};
  int first = 0;
  int last = parser->segmentCount;
  int cmp = -1;
  int middle;
  segment_t* segment;

  while(first <= last) {
    middle = (first+last)/2;
    segment_t* segment = parser->nameIndex[middle];
    cmp = strcmp(segment->name, name);
    if(cmp < 0){
      first = middle + 1;
    }else if(cmp > 0){
      last = middle - 1;
    }else{
      break;
    }
  }

  if(cmp == 0){
    stat.lower = littleLSearch(parser, name, middle);
    stat.upper = littleLSearch(parser, name, middle);
  }
  return stat;
}

static int littleLSearch(parser_t *parser, const char *name, int idx){
  int cmp = 0;
  while(cmp == 0 && idx > 0){
    segment_t* segment = parser->nameIndex[idx-1];
    cmp = strcmp(segment->name, name);
    if(cmp == 0) idx--;
  }
  return idx;
}

static int littleUSearch(parser_t *parser, const char *name, int idx){
  int cmp = 0;
  while(cmp == 0 && idx < parser->segmentCount - 1){
    segment_t* segment = parser->nameIndex[idx+1];
    cmp = strcmp(segment->name, name);
    if(cmp == 0) idx++;
  }
  return idx;
}

static int nameIndexFunc(const void *p1, const void*p2){  
  const segment_t *seg1 = *((segment_t **)p1);
  const segment_t *seg2 = *((segment_t **)p2);
  const int cmp = strcmp(seg1->name, seg2->name);

  if(cmp == 0){
    return (seg1->pkey - seg2->pkey);
  }else{
    return cmp;
  }
}

static void indexSegment(parser_t *parser, segment_t *segment, int *segmentCount, int depth){
  property_t *property = segment->firstProperty;
  segment_t *child = segment->firstSegment;
  segment->pkey = *segmentCount;
  segment->depth = depth;
  parser->nameIndex[*segmentCount] = segment;
  parser->primaryIndex[*segmentCount] = segment;
  *segmentCount = *segmentCount + 1;

  while(NULL != child){
    indexSegment(parser, child, segmentCount, depth+1);
    child = child->tail;
  }
  segment->boundary = (*segmentCount) - 1;
}

static void allocIndexes(parser_t *parser){
  parser->nameIndex = ediParsingMalloc(sizeof(segment_t*) * parser->segmentCount);
  parser->primaryIndex = ediParsingMalloc(sizeof(segment_t*) * parser->segmentCount);
}

static const int getNodeKey(VALUE segment_rb){
  VALUE segment_id_rb = rb_iv_get(segment_rb, NODE_KEY);
  return segment_id_rb == Qnil ? 0 : NUM2INT(segment_id_rb);
}

static segment_t *getNode(parser_t *parser, VALUE segment_rb){
  const int nodeKey = getNodeKey(segment_rb);
  if(nodeKey+1 > parser->segmentCount){
    // error
    return NULL;
  }else{
    return parser->primaryIndex[nodeKey];
  }
}








