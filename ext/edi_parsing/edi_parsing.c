//
//  edi_parsing.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"

void *edi_parsing_calloc(size_t nitems, size_t size){
  void *any;
  any = calloc(nitems, size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}

void *edi_parsing_malloc(size_t size){
  void *any;
  any = malloc(size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}



int compare835node(const void *pa, const void *pb){
  if (*(se *) pa < *(int *) pb)
      return -1;
  if (*(int *) pa > *(int *) pb)
      return 1;
  return 0;
}