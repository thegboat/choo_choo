//
//  edi_835_segment.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_835_parser.h"

void setSegmentName(segment_t *segment, char *src){
  long idx = strlen(src);
  idx = idx-1 > MAX_NAME_SIZE ? MAX_NAME_SIZE : idx;
  memcpy(segment->name,src,idx);
  segment->name[idx+1] = '\0';
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
  property_t *property = calloc(1,sizeof(property_t));
  buildKey(property->key, segment->name, seg_cnt, elem_cnt);
  property->value = calloc(strlen(data),sizeof(char));
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
    parent->lastSegment = child;
  }else{
    parent->lastSegment->tail = child;
    child->head = parent->lastSegment->tail;
    parent->lastSegment = child;
  }
}