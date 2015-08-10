//
//  edi_835_interface.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include <ruby.h>
#include "edi_835_parser.h"

VALUE mChooChoo;
VALUE cSegment;
VALUE cParser;
VALUE cInterchangeLoop;

static VALUE interchange_loop_alloc(VALUE self);
static void interchange_loop_free(VALUE self);
static VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str);
static VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str);
static VALUE interchange_loop_to_hash(VALUE self);
static VALUE segment_to_hash(segment_t *segment);
void Init_edi_parsing(void);

static VALUE interchange_loop_alloc(VALUE self){
  parser_t *parser = calloc(1, sizeof(parser_t));
  return Data_Wrap_Struct(self, NULL, interchange_loop_free, parser);
}

static void interchange_loop_free(VALUE self){
  parser_t *parser;
  Data_Get_Struct(self, parser_t, parser);
  parserFree(parser);
}

static VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str){
  char *c_isa_str = StringValueCStr(isa_str);
  VALUE isa = rb_class_new_instance(0, NULL, cInterchangeLoop);
  parser_t *parser;
  Data_Get_Struct(isa, parser_t, parser);

  parse835(parser, c_isa_str);

  VALUE isas = rb_ary_new();
  rb_ary_push(isas, isa);
  return isas;
}

static VALUE parser_max_threads(){
  return INT2NUM(MAX_THREADS);
}

static VALUE interchange_loop_to_hash(VALUE self){
  VALUE hash = rb_iv_get(self, "@to_hash");
  if(hash != Qnil){
    return hash;
  }else{
    parser_t *parser;
    Data_Get_Struct(self, parser_t, parser);
    if(parser->failure){
      hash = rb_hash_new(); 
    }else{
      rewindParser(parser);
      hash = segment_to_hash(parser->interchange);
    }
  }
  rb_iv_set(self, "@to_hash", hash);
  return hash;
}

static VALUE interchange_loop_errors(VALUE self){
  parser_t *parser;
  VALUE array = rb_ary_new();
  Data_Get_Struct(self, parser_t, parser);
  for(short i; i<parser->errorCount;i++){
    rb_ary_push(array, INT2NUM(parser->errors[i]));
  }
  return array;
}

static VALUE segment_to_hash(segment_t *segment){
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
  rb_define_method(cParser, "max_threads", parser_max_threads, 0);

  rb_define_alloc_func(cInterchangeLoop, interchange_loop_alloc);
  rb_define_method(cInterchangeLoop, "to_hash", interchange_loop_to_hash, 0);
  rb_define_method(cInterchangeLoop, "_errors", interchange_loop_errors, 0);
}