//
//  edi_parsing_interface.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.

#include "edi_parsing.h"

static void segment_free(anchor_t *anchor);
static VALUE segment_alloc(VALUE self);
static VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str);
static VALUE segment_parent(VALUE self);
static VALUE segment_children(VALUE self, VALUE names_rb, VALUE limit_rb);
static anchor_t *getAnchor(VALUE segment_rb);
static anchor_t *getAnchorUnsafe(VALUE segment_rb);
static VALUE segment_find(VALUE self, VALUE names_rb, VALUE limit_rb);
static VALUE segment_get_property(VALUE self, VALUE element_int_rb, VALUE component_int_rb);
static VALUE segment_where(VALUE self, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb, VALUE limit_rb);
static VALUE segment_name(VALUE self);
static VALUE segment_has_errors(VALUE self);
static VALUE segment_errors(VALUE self);
static VALUE segment_document_type(VALUE self);
static VALUE segment_exists(VALUE self, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb);

static void segment_free(anchor_t *anchor){
  if(NULL != anchor){
    if(NULL != anchor->parser){
      anchor->parser->references--;
      if(0 <= anchor->parser->references) parserFree(anchor->parser);
    }
    ediParsingDealloc(anchor);
  }
}

static VALUE segment_alloc(VALUE self){
  anchor_t *anchor = ediParsingMalloc(1,sizeof(anchor_t));
  return Data_Wrap_Struct(self, NULL, segment_free, anchor);
}

static VALUE choo_choo_parse_835(VALUE self, VALUE isa_str){
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);  
  VALUE class_rb = rb_define_class_under(mChooChoo, "ISA", cSegment);
  char *c_isa_str = StringValueCStr(isa_str);
  parser_t *parser = ediParsingMalloc(1,sizeof(parser_t));
  anchor_t *anchor;
  parserInitialization(parser);
  strcpy(parser->documentType, "835");
  VALUE isa = rb_class_new_instance(0, NULL, class_rb);
  Data_Get_Struct(isa, anchor_t, anchor);
  anchor->parser = parser;
  parse835(anchor, c_isa_str);
  return isa;
}

static VALUE segment_to_hash(VALUE self){  
  anchor_t *anchor = getAnchor(self);
  return segmentToHash(anchor->segment);
}

static VALUE segment_parent(VALUE self){
  anchor_t *anchor = getAnchor(self);
  if(NULL != anchor->segment->parent){
    return buildSegmentNode(anchor->parser, anchor->segment->parent);
  }else{
    return Qnil;
  }
}

static VALUE segment_children(VALUE self, VALUE names_rb, VALUE limit_rb){
  anchor_t *anchor = getAnchor(self);
  if(anchor->segment->children > 0){
    return segmentChildren(anchor->parser, anchor->segment, names_rb, limit_rb);
  }
  else{
    return rb_ary_new();
  }
}

static anchor_t *getAnchor(VALUE segment_rb){
  anchor_t *anchor;
  Data_Get_Struct(segment_rb, anchor_t, anchor);
  if(NULL == anchor || NULL == anchor->parser || NULL == anchor->segment){
    rb_raise(rb_eRuntimeError, "The reference to the parsed document has been lost.");
  }else if(anchor->parser->failure){
    rb_raise(rb_eRuntimeError, "Can not perform all operations when parsing fails.");
  }
  return anchor;
}

static anchor_t *getAnchorUnsafe(VALUE segment_rb){
  anchor_t *anchor;
  Data_Get_Struct(segment_rb, anchor_t, anchor);
  return anchor;
}

static VALUE segment_find(VALUE self, VALUE names_rb, VALUE limit_rb){
  anchor_t *anchor = getAnchor(self);
  if(anchor->segment->children > 0){
    return segmentFind(anchor->parser, anchor->segment, names_rb, limit_rb);
  }
  else{
    return rb_ary_new();
  }
}

static VALUE segment_exists(VALUE self, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb){
  anchor_t *anchor = getAnchor(self);
  if(anchor->segment->children > 0){
    return segmentExists(anchor->parser, anchor->segment, name_rb, element_int_rb, component_int_rb, value_rb);
  }else{
    return Qnil;
  }
}

static VALUE segment_name(VALUE self){
  anchor_t *anchor = getAnchorUnsafe(self);
  ID id_name = rb_intern(anchor->segment->name);
  return ID2SYM(id_name);
}

static VALUE segment_get_property(VALUE self, VALUE element_int_rb, VALUE component_int_rb){
  short element = NUM2SHORT(element_int_rb);
  short component = NUM2SHORT(component_int_rb);
  anchor_t *anchor = getAnchor(self);
  property_t *property = anchor->segment->firstProperty;
  short cnt = 0;
  while(NULL != property && cnt < 10000){
    if(element == property->element && component == property->component) return rb_str_new_cstr(property->value);
    property = property->tail;
    cnt++;
  }

  return Qnil;
}

static VALUE segment_errors(VALUE self){
  anchor_t *anchor = getAnchorUnsafe(self);
  return getErrors(anchor->parser);
}

static VALUE segment_has_errors(VALUE self){
  anchor_t *anchor = getAnchorUnsafe(self);
  return (anchor->parser->errorCount == 0 ? Qfalse : Qtrue);
}

static VALUE segment_where(VALUE self, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb, VALUE limit_rb){
  anchor_t *anchor = getAnchor(self);
  if(anchor->segment->children > 0){
    return segmentWhere(anchor->parser, anchor->segment, name_rb, element_int_rb, component_int_rb, value_rb, limit_rb);
  }
  else{
    return rb_ary_new();
  }
}

static VALUE segment_document_type(VALUE self){
  anchor_t *anchor = getAnchor(self);
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cDocument = rb_define_class_under(mChooChoo, "Document", rb_cObject);
  VALUE mEDI;
  VALUE doc;
  if(strcmp(anchor->parser->documentType, "835") == 0){
    mEDI = rb_define_module("EDI835");
    doc = rb_define_class_under(mEDI, "Document", cDocument);
  }else{
    rb_raise(rb_eRuntimeError, "Can not perform all operations when parsing fails.");
  }
  return doc;
}

VALUE buildSegmentNode(parser_t *parser, segment_t *segment){
  anchor_t *anchor;
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);

  VALUE class_rb = rb_define_class_under(mChooChoo, segment->name, cSegment);
  VALUE segment_rb = rb_class_new_instance(0, NULL, class_rb);

  Data_Get_Struct(segment_rb, anchor_t, anchor);
  parser->references++;
  anchor->parser = parser;
  anchor->segment = segment;
  return segment_rb;
}

VALUE choo_choo_empty(self){
  return rb_str_new_cstr(CHOOCHOO_EMPTY);
}

void Init_edi_parsing(void) {
  VALUE mChooChoo = rb_define_module("ChooChoo");
  VALUE cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE cParser = rb_define_class_under(mChooChoo, "Parser", rb_cObject);

  rb_define_method(cParser, "_c_parse_835", choo_choo_parse_835, 1);
  rb_define_method(cParser, "empty", choo_choo_empty, 0);

  rb_define_alloc_func(cSegment, segment_alloc);
  rb_define_method(cSegment, "document_type", segment_document_type, 0);
  rb_define_method(cSegment, "_c_name", segment_name, 0);
  rb_define_method(cSegment, "to_hash", segment_to_hash, 0);
  rb_define_method(cSegment, "_c_descendants", segment_find, 2);
  rb_define_method(cSegment, "_c_children", segment_children, 2);
  rb_define_method(cSegment, "_c_parent", segment_parent, 0);
  rb_define_method(cSegment, "_c_get_property", segment_get_property, 2);
  rb_define_method(cSegment, "_c_where", segment_where, 5);
  rb_define_method(cSegment, "_c_errors", segment_errors, 0);
  rb_define_method(cSegment, "_c_errors?", segment_has_errors, 0);
  rb_define_method(cSegment, "_c_exists?", segment_exists, 4);
}