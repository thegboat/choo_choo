//
//  edi_835_loop.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_835_parser.h"


void loopInitializer(loop_t *loop, const char *name){
  memcpy(loop->name, name, MAX_NAME_SIZE);
  loop->name[MAX_NAME_SIZE+1] = '\0';
}

void addSegment(loop_t *loop, segment_t * child){
  if(NULL == loop->firstSegment){
    loop->firstSegment = child;
  }else{
    loop->lastSegment->tail = child;
    child->head = loop->lastSegment;
  }
  loop->lastSegment = child;
}
