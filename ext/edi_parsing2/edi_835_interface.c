//
//  edi_835_interface.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include <ruby.h>
#include "edi_835_parser.h"

ID id_hash_store;

VALUE mChooChoo;
VALUE cEDI_835;
VALUE cChooChooHash;

void choo_choo_edi_835_free(VALUE self){
  parser_t *parser;
  Data_Get_Struct(self, parser_t, parser);
  if(NULL != parser){
    parserFree(parser);
  }
}

// VALUE edi_835_isa(VALUE self){
//   parser_t *parser;
//   Data_Get_Struct(self, parser_t, parser);
//   VALUE hash = rb_class_new_instance(0, NULL, cChooChooHash);
//   rb_funcall(hash, )
//   rb_funcall(obj, rb_intern("=="), 1, Qnil);
//   return hash;
// }

VALUE choo_choo_edi_835_alloc(VALUE self) {
  parser_t *parser = calloc(1,sizeof(parser_t));
  parser->finished = false;
  parser->failure = false;
  return Data_Wrap_Struct(self, NULL, choo_choo_edi_835_free, parser);
}

VALUE choo_choo_parse_835(VALUE self, VALUE edi_file_string){
  char *ediFile = StringValueCStr(edi_file_string);
  parser_t *parser;
  VALUE edi835 = rb_class_new_instance(0, NULL, cEDI_835);
  Data_Get_Struct(edi835, parser_t, parser);
  parse835(parser, ediFile);
  return edi835;
}

void Init_edi_parsing(void) {
  mChooChoo = rb_define_module("ChooChoo");
  cEDI_835 = rb_define_class_under(mChooChoo, "EDI_835", rb_cObject);

  rb_define_alloc_func(cEDI_835, choo_choo_edi_835_alloc);
  rb_define_singleton_method(mChooChoo, "_c_parse_835", choo_choo_parse_835, 1);
  // rb_define_method(cEDI_835, "interchange_loop", edi_835_isa, 0);

  id_hash_store = rb_intern("store");

  cChooChooHash = rb_const_get(mChooChoo, rb_intern("Hash"));
}