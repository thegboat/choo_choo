//
//  edi_parsing_interface.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.

#include "edi_parsing.h"

static void interchange_loop_free(VALUE self);
static VALUE interchange_loop_alloc(VALUE self);
static void segment_free(VALUE self);
static VALUE segment_alloc(VALUE self);
static VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str);
static VALUE interchange_loop_to_hash(VALUE self);
static VALUE interchange_loop_errors(VALUE self);
static VALUE segment_parent(VALUE self);
static VALUE segment_children(VALUE self, VALUE names);
static anchor_t *getAnchor(VALUE segment_rb);
static VALUE segment_find(VALUE self, VALUE names);
static VALUE documentType(VALUE self);

static void interchange_loop_free(VALUE self){
  anchor_t *anchor;
  Data_Get_Struct(self, anchor_t, anchor);
  parserFree(anchor->parser);
  free(anchor);
}

static VALUE interchange_loop_alloc(VALUE self){
  parser_t *parser = (parser_t *)ediParsingMalloc(sizeof(parser_t));
  anchor_t *anchor = (anchor_t *)ediParsingMalloc(sizeof(anchor_t));
  parserInitialization(parser);
  strcpy(parser->documentType, "835");
  anchor->parser = parser;
  return Data_Wrap_Struct(self, NULL, interchange_loop_free, anchor);
}

static void segment_free(VALUE self){
  anchor_t *anchor;
  Data_Get_Struct(self, anchor_t, anchor);
  free(anchor);
}

static VALUE segment_alloc(VALUE self){
  anchor_t *anchor = (anchor_t *)ediParsingMalloc(sizeof(anchor_t));
  return Data_Wrap_Struct(self, NULL, segment_free, anchor);
}

static VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str){
  char *c_isa_str = StringValueCStr(isa_str);
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE cInterchangeLoop = rb_define_class_under(mChooChoo, "InterchangeLoop", rb_cObject);

  VALUE isa = rb_class_new_instance(0, NULL, cInterchangeLoop);
  anchor_t *anchor;
  Data_Get_Struct(isa, anchor_t, anchor);

  parse835(anchor, c_isa_str);
  rb_iv_set(isa, PROPERTIES, propertiesToHash(anchor->segment->firstProperty));
  VALUE isas = rb_ary_new();
  rb_ary_push(isas, isa);
  segment_children(isa, rb_ary_new());
  return isas;
}

static VALUE interchange_loop_to_hash(VALUE self){  
  anchor_t *anchor = getAnchor(self);
  if(anchor->parser->failure){
    return rb_hash_new(); 
  }else{
    return segmentToHash(anchor->parser->root);
  }

}

static VALUE interchange_loop_errors(VALUE self){
  anchor_t *anchor = getAnchor(self);
  VALUE array = rb_ary_new();
  for(short i; i<anchor->parser->errorCount;i++){
    rb_ary_push(array, INT2NUM(anchor->parser->errors[i]));
  }
  return array;
}

static VALUE segment_parent(VALUE self){
  anchor_t *anchor = getAnchor(self);
  return buildSegmentNode(anchor->parser, anchor->segment);
}

static VALUE segment_children(VALUE self, VALUE names){
  anchor_t *anchor = getAnchor(self);
  return segmentChildren(anchor->parser, anchor->segment, names);
}

static anchor_t *getAnchor(VALUE segment_rb){
  anchor_t *anchor;
  Data_Get_Struct(segment_rb, anchor_t, anchor);
  return anchor;
}

static VALUE segment_find(VALUE self, VALUE names){
  anchor_t *anchor = getAnchor(self);
  return segmentFind(anchor->parser, anchor->segment, names);
}

VALUE buildSegmentNode(parser_t *parser, segment_t *segment){
  anchor_t *anchor;
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE segment_rb = rb_class_new_instance(0, NULL, cSegment);
  Data_Get_Struct(segment_rb, anchor_t, anchor);
  anchor->parser = parser;
  anchor->segment = segment;
  rb_iv_set(segment_rb, PROPERTIES, propertiesToHash(segment->firstProperty));
  return segment_rb;
}

static VALUE documentType(VALUE self){
  anchor_t *anchor = getAnchor(self);
  return rb_str_new_cstr(anchor->parser->documentType);
}

void Init_edi_parsing(void) {
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE cInterchangeLoop = rb_define_class_under(mChooChoo, "InterchangeLoop", rb_cObject);
  VALUE cParser = rb_define_class_under(mChooChoo, "Parser", rb_cObject);

  rb_define_method(cParser, "_c_parse_835", choo_choo_parse_835, 1);

  rb_define_alloc_func(cSegment, segment_alloc);
  rb_define_private_method(cSegment, "_c_descendants", segment_find, 1);
  rb_define_private_method(cSegment, "_c_children", segment_children, 1);
  rb_define_private_method(cSegment, "_c_parent", segment_parent, 0);
  rb_define_method(cSegment, "document_type", documentType, 0);
  
  rb_define_private_method(cInterchangeLoop, "_c_descendants", segment_find, 1);
  rb_define_private_method(cInterchangeLoop, "_c_children", segment_children, 1);
  rb_define_method(cInterchangeLoop, "document_type", documentType, 0);

  rb_define_alloc_func(cInterchangeLoop, interchange_loop_alloc);
  rb_define_method(cInterchangeLoop, "to_hash", interchange_loop_to_hash, 0);
  rb_define_method(cInterchangeLoop, "_errors", interchange_loop_errors, 0);
}