//
//  edi_parsing_segment.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//
#include "edi_parsing.h"

static void propertyFree(segment_t* segment);

void segmentInitializer(segment_t *segment, char *src){
  long idx = strlen(src);
  idx = idx > MAX_NAME_SIZE ? MAX_NAME_SIZE : idx;
  memset(segment->name,0,(MAX_NAME_SIZE+1)*sizeof(char));
  memcpy(segment->name,src,idx*sizeof(char));
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
    st_add_direct(segment->propertyCache, (st_data_t)key, (unsigned long)strdup(data));
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
    if(segment->propertyCache){
      propertyFree(segment);
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

static void propertyFree(segment_t* segment){
  char *ptr;
  for(short element=1;element<=segment->elements; element++){
    for(short component=0; component<100; component++){
      if((ptr = propertyLookup(segment, element, component))){
        if(strlen(ptr)) ediParsingDealloc(ptr);
      }else{
        break;
      }
    }
  }
  st_free_table(segment->propertyCache);
  segment->propertyCache = NULL;
}