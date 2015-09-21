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
  segment->propertyCache = st_init_numtable();
}

void cacheProperty(segment_t *segment, char *data, short element, short component){
  unsigned long key = getPropertyKey(element, component);
  if(strcmp(data, CHOOCHOO_EMPTY) == 0){
    st_add_direct(segment->propertyCache, (st_data_t)key, (unsigned long)(""));
  }else{
    long len = strlen(data);
    char *allocated = ediParsingMalloc(len+1,sizeof(char));
    strcpy(allocated, data);
    st_add_direct(segment->propertyCache, (st_data_t)key, (unsigned long)allocated);
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
  if(NULL != segment){    if(segment->propertyCache){
      st_free_table(segment->propertyCache);
      segment->propertyCache = NULL;
    }
    ediParsingDealloc(segment);
  }
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