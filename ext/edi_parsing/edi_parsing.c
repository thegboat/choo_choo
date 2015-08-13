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

void *ediParsingMalloc(size_t size){
  void *any;
  any = calloc(1, size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}

segment_t *parseSegment(parser_t *parser){
  segment_t *segment = (segment_t *)ediParsingMalloc(sizeof(segment_t));
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
  return segment;
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

void parserFail(parser_t *parser, short error){
  parser->failure = true;
  parser->finished = true;
  
  if(parser->errorCount < MAX_ERROR_SIZE){
    parser->errors[parser->errorCount] = error;
    parser->errorCount++;
  }
}

void interchange_loop_835_free(VALUE self){
  parser835_t *parser;
  Data_Get_Struct(self, parser835_t, parser);
  parser835Free(parser);
}

void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

int cmpSegmentName(const void *p1, const void*p2){
  segment_t *me = (segment_t*)p1;
  segment_t *other = (segment_t*)p2;

  return strcmp(me->name, other->name);
}

int cmpSegmentDepth(const void *p1, const void*p2){
  segment_t *me = (segment_t*)p1;
  segment_t *other = (segment_t*)p2;
  if(me->depth > other->depth){
    return 1;
  }else if(me->depth < other->depth){
    return -1;
  }else{
    return strcmp(me->name, other->name);
  }
}

int cmpPropertyName(const void *p1, const void*p2){
  property_t *me = (property_t*)p1;
  property_t *other = (property_t*)p2;

  return strcmp(me->key, other->key);
}

int cmpPropertyDepth(const void *p1, const void*p2){
  property_t *me = (property_t*)p1;
  property_t *other = (property_t*)p2;
  if(me->owner->depth > other->owner->depth){
    return 1;
  }else if(me->owner->depth < other->owner->depth){
    return -1;
  }else{
    return strcmp(me->key, other->key);
  }
}

void buildIndexes(parser_t *parser, segment_t *root){
  allocIndexes(parser);
  indexSegment(parser, root, 0,0);
  qsort(parser->snIdx, parser->segmentCount, sizeof(segment_t), cmpSegmentName);
  qsort(parser->sdIdx, parser->segmentCount, sizeof(segment_t), cmpSegmentDepth);
  qsort(parser->pnIdx, parser->propertyCount, sizeof(property_t), cmpPropertyName);
  qsort(parser->pdIdx, parser->propertyCount, sizeof(property_t), cmpPropertyDepth);
}

void indexSegment(parser_t *parser, segment_t *segment, int segmentCount, int propertyCount){
  property_t *property = segment->firstProperty;
  segment_t *child = segment->firstSegment;
  segment->pkey = segmentCount;
  parser->snIdx[segmentCount] = segment;
  parser->sdIdx[segmentCount] = segment;
  parser->sPkey[segmentCount] = segment;
  segmentCount++;

  while(NULL != property){
    property->pkey = propertyCount;
    parser->pnIdx[propertyCount] = property;
    parser->pdIdx[propertyCount] = property;
    parser->pPkey[propertyCount] = property;
    property = property->tail;
    propertyCount++;
  }

  while(NULL != child){
    indexSegment(parser, child, segmentCount, propertyCount);
    child = child->tail;
  }
}

void allocIndexes(parser_t *parser){
  parser->pnIdx = ediParsingMalloc(sizeof(property_t*) * parser->propertyCount);
  parser->pdIdx = ediParsingMalloc(sizeof(property_t*) * parser->propertyCount);
  parser->pPkey = ediParsingMalloc(sizeof(property_t*) * parser->propertyCount);
  parser->snIdx = ediParsingMalloc(sizeof(segment_t*) * parser->segmentCount);
  parser->sdIdx = ediParsingMalloc(sizeof(segment_t*) * parser->segmentCount);
  parser->sPkey = ediParsingMalloc(sizeof(segment_t*) * parser->segmentCount);
}

VALUE interchange_loop_835_alloc(VALUE self){
  parser835_t *parser = (parser835_t *)ediParsingMalloc(sizeof(parser835_t));
  return Data_Wrap_Struct(self, NULL, interchange_loop_835_free, parser);
}

VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str){
  char *c_isa_str = StringValueCStr(isa_str);
  VALUE isa = rb_class_new_instance(0, NULL, cInterchangeLoop);
  parser835_t *parser;
  Data_Get_Struct(isa, parser835_t, parser);

  parse835(parser, c_isa_str);

  VALUE isas = rb_ary_new();
  rb_ary_push(isas, isa);
  return isas;
}

VALUE interchange_loop_835_to_hash(VALUE self){  
  parser835_t *parser;
  Data_Get_Struct(self, parser835_t, parser);
  if(parser->super.failure){
    return rb_hash_new(); 
  }else{
    rewind835Parser(parser);
    return segment_to_hash(parser->interchange);
  }

}

VALUE interchange_loop_835_errors(VALUE self){
  parser835_t *parser;
  VALUE array = rb_ary_new();
  Data_Get_Struct(self, parser835_t, parser);
  for(short i; i<parser->super.errorCount;i++){
    rb_ary_push(array, INT2NUM(parser->super.errors[i]));
  }
  return array;
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