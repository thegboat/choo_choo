//
//  edi_835_interface.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_835_parser.h"

VALUE interchange_loop_835_alloc(VALUE self){
  parser835_t *parser = ediParsingCalloc(1, sizeof(parser835_t));
  return Data_Wrap_Struct(self, NULL, interchange_loop_835_free, parser);
}

void interchange_loop_835_free(VALUE self){
  parser835_t *parser;
  Data_Get_Struct(self, parser835_t, parser);
  parser835Free(parser);
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
  if(parser->failure){
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
  for(short i; i<parser->errorCount;i++){
    rb_ary_push(array, INT2NUM(parser->errors[i]));
  }
  return array;
}