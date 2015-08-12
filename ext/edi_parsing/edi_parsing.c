//
//  edi_parsing.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"

VALUE mChooChoo;
VALUE cSegment;
VALUE cParser;
VALUE cInterchangeLoop;

void *ediParsingCalloc(size_t nitems, size_t size){
  void *any;
  any = calloc(nitems, size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}

void *ediParsingMalloc(size_t size){
  void *any;
  any = malloc(size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}

void parseSegment(parser_t *parser){
  segment_t *segment = ediParsingCalloc(1,sizeof(segment_t));
  char *tok;
  char *saveptr;
  short cnt = 0;
  tok = strtok_r(parser->str, ELEMENT_SEPARATOR, &saveptr);
  segmentInitializer(segment, tok);
  tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  while (tok != NULL)
  {
    cnt++;
    if(strlen(parser->componentSeparator) == 1 && NULL != strstr(tok, parser->componentSeparator)){
      parseElement(segment, tok, parser->componentSeparator, cnt);
    }else{
      buildProperty(segment, tok, cnt, 0);
      parser->propertyCount++;
    }
    tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  }
  segment->elements = cnt;
}

void parseElement(segment_t *segment, char *str, const char componentSeparator[2], short seg_cnt){
  char *tok;
  char *saveptr;
  short cnt = 0;
  tok = strtok_r(str, componentSeparator, &saveptr);
  while (tok != NULL)
  {
    cnt++;
    buildProperty(segment, tok, seg_cnt, cnt);
    tok = strtok_r(NULL, componentSeparator, &saveptr);
  }
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

void Init_edi_parsing(void) {
  mChooChoo = rb_define_module("ChooChoo");
  cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  cInterchangeLoop = rb_define_class_under(mChooChoo, "InterchangeLoop", rb_cObject);
  cParser = rb_define_class_under(mChooChoo, "Parser", rb_cObject);

  rb_define_method(cParser, "_c_parse_835", choo_choo_parse_835, 1);

  rb_define_alloc_func(cInterchangeLoop, interchange_loop_835_alloc);
  rb_define_method(cInterchangeLoop, "to_hash", interchange_loop_835_to_hash, 0);
  rb_define_method(cInterchangeLoop, "_errors", interchange_loop_835_errors, 0);
}