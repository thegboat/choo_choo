//
//  edi_parsing_segment.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_parsing.h"

void segmentInitializer(segment_t *segment, char *src){
  long idx = strlen(src);
  idx = idx > MAX_NAME_SIZE ? MAX_NAME_SIZE : idx;
  memset(segment->name,0,MAX_NAME_SIZE*sizeof(char));
  memcpy(segment->name,src,idx*sizeof(char));
  segment->name[idx+1] = '\0';
  segment->elements = 0;
  segment->depth = 0;
  segment->children = 0;
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
  property_t *property = ediParsingMalloc(sizeof(property_t));
  property->owner = segment;
  property->element = seg_cnt;
  property->component = elem_cnt;
  long len = (strcmp(data, CHOOCHOO_EMPTY) == 0) ? 0 : strlen(data);
  property->value = ediParsingMalloc(sizeof(char)*(len+1));
  memcpy(property->value, data, sizeof(char)*len);
  property->value[len] = '\0';
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
  parent->children++;
  parent->lastSegment = child;
  child->parent = parent;
  child->depth = parent->depth + 1;
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
    xfree(segment);
  }
}

void propertyFree(property_t *property){
  if(NULL != property->value)xfree(property->value);
  xfree(property);
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

bool elementCountIn(segment_t *segment, int start, int end){
  return segment->elements >= start && segment->elements <= end;
}