//
//  edi_parsing_interface.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.

#include "edi_parsing.h"

static parser835_t *segment835Parser(VALUE segment_rb);

void interchange_loop_835_free(VALUE self){
  parser835_t *parser;
  Data_Get_Struct(self, parser835_t, parser);
  parser835Free(parser);
}

VALUE interchange_loop_835_alloc(VALUE self){
  parser835_t *parser = (parser835_t *)ediParsingMalloc(sizeof(parser835_t));
  parser->super = (parser_t *)ediParsingMalloc(sizeof(parser_t));
  return Data_Wrap_Struct(self, NULL, interchange_loop_835_free, parser);
}

VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str){
  char *c_isa_str = StringValueCStr(isa_str);
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE cInterchangeLoop = rb_define_class_under(mChooChoo, "InterchangeLoop", rb_cObject);

  VALUE isa = rb_class_new_instance(0, NULL, cInterchangeLoop);
  parser835_t *parser;
  Data_Get_Struct(isa, parser835_t, parser);

  parse835(parser, c_isa_str);
  rewind835Parser(parser);
  rb_iv_set(isa, DOCUMENT_TYPE_KEY, ID2SYM(rb_intern("835")));
  rb_iv_set(isa, NODE_KEY, INT2NUM(0));
  rb_iv_set(isa, ISA_LINK, isa);
  rb_iv_set(isa, PROPERTIES, propertiesToHash(parser->interchange->firstProperty));
  VALUE isas = rb_ary_new();
  rb_ary_push(isas, isa);
  return isas;
}

VALUE interchange_loop_835_to_hash(VALUE self){  
  parser835_t *parser;
  Data_Get_Struct(self, parser835_t, parser);
  if(parser->super->failure){
    return rb_hash_new(); 
  }else{
    rewind835Parser(parser);
    return segmentToHash(parser->interchange);
  }

}

VALUE interchange_loop_835_errors(VALUE self){
  parser835_t *parser;
  VALUE array = rb_ary_new();
  Data_Get_Struct(self, parser835_t, parser);
  for(short i; i<parser->super->errorCount;i++){
    rb_ary_push(array, INT2NUM(parser->super->errors[i]));
  }
  return array;
}

VALUE segment835parent(VALUE self){
  parser835_t *parser = segment835Parser(self);
  return segmentParent(parser->super, self);
}

VALUE segment835children(VALUE self, VALUE names){
  parser835_t *parser = segment835Parser(self);
  return segmentChildren(parser->super, self, names);
}

static parser835_t *segment835Parser(VALUE segment_rb){
  parser835_t *parser;
  VALUE isa = rb_iv_get(segment_rb, ISA_LINK);
  Data_Get_Struct(isa, parser835_t, parser);
  return parser;
}

VALUE segment835Find(VALUE self, VALUE names){
  parser835_t *parser = segment835Parser(self);
  return segmentFind(parser->super, self, names);
}

VALUE buildSegmentNode(VALUE isa, segment_t *segment){
  VALUE document_type = rb_iv_get(isa, DOCUMENT_TYPE_KEY);
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE segment_rb = rb_class_new_instance(0, NULL, cSegment);
  rb_iv_set(segment_rb, SEGMENT_NAME, ID2SYM(rb_intern(segment->name)));
  rb_iv_set(segment_rb, DOCUMENT_TYPE_KEY, document_type);
  rb_iv_set(segment_rb, NODE_KEY, INT2NUM(segment->pkey));
  rb_iv_set(segment_rb, ISA_LINK, isa);
  rb_iv_set(segment_rb, PROPERTIES, propertiesToHash(segment->firstProperty));
  return segment_rb;
}

void Init_edi_parsing(void) {
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE cInterchangeLoop = rb_define_class_under(mChooChoo, "InterchangeLoop", rb_cObject);
  VALUE cParser = rb_define_class_under(mChooChoo, "Parser", rb_cObject);

  rb_define_method(cParser, "_c_parse_835", choo_choo_parse_835, 1);

  rb_define_private_method(cSegment, "_c_835_descendants", segment835Find, 1);
  rb_define_private_method(cSegment, "_c_835_children", segment835children, 1);
  rb_define_private_method(cSegment, "_c_835_parent", segment835parent, 0);
  
  rb_define_private_method(cInterchangeLoop, "_c_835_descendants", segment835Find, 1);
  rb_define_private_method(cInterchangeLoop, "_c_835_children", segment835children, 1);

  rb_define_alloc_func(cInterchangeLoop, interchange_loop_835_alloc);
  rb_define_method(cInterchangeLoop, "to_hash", interchange_loop_835_to_hash, 0);
  rb_define_method(cInterchangeLoop, "_errors", interchange_loop_835_errors, 0);
}