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
static int nameIndexFunc(const void *p1, const void*p2);
static void indexSegment(parser_t *parser, segment_t *segment, int *segmentCount, int depth);
static void allocIndexes(parser_t *parser);

void buildIndexes(parser_t *parser){
  int segmentCount = 0;
  int propertyCount = 0;
  allocIndexes(parser);
  indexSegment(parser, parser->root, &segmentCount, 0);
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

VALUE segmentChildren(parser_t *parser, segment_t *segment, VALUE names){
  VALUE result = rb_ary_new();
  const int length = NUM2INT(rb_funcall(names, rb_intern("length"), 0));
  segment_t *descendant;

  if(length == 0){
    descendant = segment->firstSegment;

    while(NULL != descendant){
      VALUE child_rb = buildSegmentNode(parser, descendant);
      rb_ary_push(result, child_rb);
      descendant = descendant->tail;
    }
  }else{
    VALUE name = rb_ary_pop(names);
    char *c_name;
    index_stat_t stat;
    while(name != Qnil){
      c_name = StringValueCStr(name);
      stat = nameIndexSearch(parser, c_name);
      int max = (stat.upper - stat.lower) + 1;
      if(stat.lower >= 0 && stat.upper >= 0){
        for(int i=0;i<max;i++){
          descendant = parser->nameIndex[i+stat.lower];
          if(segment->depth + 1 == descendant->depth && descendant->pkey > segment->pkey && descendant->pkey <= segment->boundary){
            VALUE child_rb = buildSegmentNode(parser, descendant);
            rb_ary_push(result, child_rb);
          }
        }
      }
      name = rb_ary_pop(names);
    }
  }
  return result;
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

VALUE segmentFind(parser_t *parser, segment_t *segment, VALUE names){
  VALUE result = rb_ary_new();
  const int length = NUM2INT(rb_funcall(names, rb_intern("length"), 0));
  segment_t *descendant;

  if(length == 0){
    int max = (segment->boundary - segment->pkey) + 1;
    for(int i=1;i<max;i++){
      descendant = parser->primaryIndex[i+segment->pkey];
      if(descendant->pkey > segment->pkey && descendant->pkey <= segment->boundary){
        VALUE child_rb = buildSegmentNode(parser, descendant);
        rb_ary_push(result, child_rb);
      }
    }
  }else{
    VALUE name = rb_ary_pop(names);
    char *c_name;
    index_stat_t stat;
    while(name != Qnil){
      c_name = StringValueCStr(name);
      stat = nameIndexSearch(parser, c_name);
      int max = (stat.upper - stat.lower) + 1;
      if(stat.lower >= 0 && stat.upper >= 0){
        for(int i=0;i<max;i++){
          descendant = parser->nameIndex[i+stat.lower];
          if(descendant->pkey > segment->pkey && descendant->pkey <= segment->boundary){
            VALUE child_rb = buildSegmentNode(parser, descendant);
            rb_ary_push(result, child_rb);
          }
        }
      }
      name = rb_ary_pop(names);
    }
  }
  return result;
}

index_stat_t nameIndexSearch(parser_t *parser, const char *name){
  index_stat_t stat = {-1,-1};
  int first = 0;
  int last = parser->segmentCount;
  int cmp = -1;
  int middle = (first+last)/2;
  segment_t* segment;

  while(first <= last) {
    segment = parser->nameIndex[middle];
    cmp = strcmp(segment->name, name);
    if(cmp < 0){
      first = middle + 1;
    }else if(cmp > 0){
      last = middle - 1;
    }else{
      break;
    }
    middle = (first+last)/2;
  }

  if(cmp == 0){
    stat.lower = littleLSearch(parser, name, middle);
    stat.upper = littleUSearch(parser, name, middle);
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

bool missingSegment(parser_t *parser, char *src){
  index_stat_t stat = nameIndexSearch(parser, src);
  return stat.lower < 0 || stat.upper < 0;
}

int segmentsWithName(parser_t *parser, char *src){
  index_stat_t stat = nameIndexSearch(parser, src);
  return (stat.lower < 0 || stat.upper < 0) ? 0 : ((stat.upper - stat.lower) + 1);
}

bool multipleWithName(parser_t *parser, char *src){
  return segmentsWithName(parser, src) > 1;
}








