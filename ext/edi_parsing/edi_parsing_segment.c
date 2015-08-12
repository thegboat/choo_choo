//
//  edi_parsing_segment.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_835_parser.h"

void segmentInitializer(segment_t *segment, char *src){
  long idx = strlen(src);
  idx = idx-1 > MAX_NAME_SIZE ? MAX_NAME_SIZE : idx;
  memcpy(segment->name,src,idx);
  segment->name[idx+1] = '\0';
  segment->elements = 0;
}

void addProperty(segment_t *segment, property_t *property){
  if(NULL == segment->firstProperty){
    segment->firstProperty = property;
    segment->lastProperty = property;
  }else{
    segment->lastProperty->tail = property;
    property->head = segment->lastProperty;
    segment->lastProperty = property;
  }
}

void buildProperty(segment_t *segment, char *data, short seg_cnt, short elem_cnt){
  property_t *property = ediParsingCalloc(1,sizeof(property_t));
  buildKey(property->key, segment->name, seg_cnt, elem_cnt);
  property->value = ediParsingCalloc(strlen(data),sizeof(char));
  memcpy(property->value, data, strlen(data));
  addProperty(segment, property);
}


void buildKey(char *key, char *seg_name, short seg_cnt, short elem_cnt){
  if(0 == elem_cnt){
    sprintf(key, "%s%02i", seg_name, seg_cnt);
  }else{
    sprintf(key, "%s%02i_%02i", seg_name, seg_cnt, elem_cnt);
  }
}

void addChildSegment(segment_t *parent, segment_t *child){
  if(NULL == parent->firstSegment){
    parent->firstSegment = child;
  }else{
    parent->lastSegment->tail = child;
    child->head = parent->lastSegment;
  }
  parent->lastSegment = child;
  child->parent = parent;
}

void loopFree(segment_t *loop){
  if(NULL != loop){
    segment_t *segment;
    segment_t *tmp;
    segment = loop->firstSegment;
    while(NULL != segment){
      tmp = segment->tail;
      if(segment != loop) segmentFree(segment);
      segment = tmp;
    }
  }
}

void segmentFree(segment_t *segment){
  if(NULL != segment){
    property_t *property;
    property_t *tmp;
    property = segment->firstProperty;
    while(NULL != property){
      tmp = property->tail;
      propertyFree(property);
      property = tmp;
    }
    free(segment);
  }
}

void propertyFree(property_t *property){
  free(property->value);
  free(property);
}

segment_t *rewindLoop(segment_t *loop){
  segment_t *tmp;
  tmp = loop;
  while(NULL != tmp){
    loop = tmp;
    tmp = loop->head;
  }
  return loop;
}

VALUE segment_to_hash(segment_t *segment){
  property_t *property = segment->firstProperty;
  segment_t *child = segment->firstSegment;
  VALUE proxy = rb_hash_new();
  VALUE children = rb_ary_new();

  while(NULL != property){
    VALUE key = ID2SYM(rb_intern(property->key));
    rb_hash_aset(proxy, key, rb_str_new_cstr(property->value));
    property = property->tail;
  }

  while(NULL != child){
    rb_ary_push(children, segment_to_hash(child));
    child = child->tail;
  }

  rb_hash_aset(proxy, ID2SYM(rb_intern("name")), rb_str_new_cstr(segment->name));
  rb_hash_aset(proxy, ID2SYM(rb_intern("children")), children);
  return proxy;
}