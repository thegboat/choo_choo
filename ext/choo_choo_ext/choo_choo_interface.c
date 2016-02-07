//
//  choo_choo_interface.c
//  choo_choo
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.

#include "choo_choo.h"

static void segment_free(anchor_t *anchor);
static VALUE segment_alloc(VALUE self);
static VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str);
static VALUE segment_parent(VALUE self);
static VALUE segment_children(VALUE self, VALUE names_rb, VALUE limit_rb);
static inline anchor_t *getAnchorUnsafe(VALUE segment_rb);
static VALUE segment_find(VALUE self, VALUE names_rb, VALUE limit_rb);
static VALUE segment_get_property(VALUE self, VALUE element_int_rb, VALUE component_int_rb);
static VALUE segment_where(VALUE self, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb, VALUE limit_rb);
static VALUE segment_name(VALUE self);
static VALUE document_has_errors(VALUE self);
static VALUE document_errors(VALUE self);
static VALUE segment_document_type(VALUE self);
static VALUE segment_exists(VALUE self, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb);
static anchor_t *parserSetup(const char documentType[10]);
static VALUE choo_choo_empty(VALUE self);
static VALUE segment_root(VALUE self);
static VALUE getDocClass(const char *doctype);
static void segment_mark(anchor_t *anchor);

static VALUE mChooChoo;
static VALUE cSegment;
static VALUE cParser;
static VALUE cDocument;
static VALUE mEDI835;
static VALUE cISA;
static VALUE cDoc835;

static ID id_force_8_bit;

static void segment_free(anchor_t *anchor){
  choo_chooDealloc(anchor);
}

static void document_free(anchor_t *anchor){
  if(NULL != anchor){
    parserFree(anchor->parser);
    choo_chooDealloc(anchor);
  }
}

static VALUE segment_alloc(VALUE self){
  anchor_t *anchor = choo_chooMalloc(1,sizeof(anchor_t));
  return Data_Wrap_Struct(self, segment_mark, segment_free, anchor);
}

static void segment_mark(anchor_t *anchor){
  if(!anchor) return;
  if(!anchor->parser) return;
  rb_gc_mark(anchor->parser->doc);
}

static VALUE document_alloc(VALUE self){
  anchor_t *anchor = choo_chooMalloc(1,sizeof(anchor_t));
  return Data_Wrap_Struct(self, NULL, document_free, anchor);
}

static VALUE choo_choo_parse_835(VALUE self, VALUE isa_str){
  VALUE copy = rb_funcall(isa_str, id_force_8_bit, 0);
  anchor_t *anchor = parserSetup("835");
  parse835(anchor->parser, RSTRING_PTR(copy));
  rb_str_free(copy);
  return anchor->parser->doc;
}

static anchor_t *parserSetup(const char *documentType){
  anchor_t *anchor;
  VALUE doc = rb_class_new_instance(0, NULL, getDocClass(documentType));
  Data_Get_Struct(doc, anchor_t, anchor);
  anchor->parser = choo_chooMalloc(1,sizeof(parser_t));
  anchor->parser->doc = doc;
  parserInitialization(anchor->parser);
  strcpy(anchor->parser->documentType, documentType);
  return anchor;
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

anchor_t *getAnchor(VALUE segment_rb){
  anchor_t *anchor;
  Data_Get_Struct(segment_rb, anchor_t, anchor);
  if(!anchor || !anchor->parser || (!anchor->segment && segment_rb != anchor->parser->doc)){
    rb_raise(rb_eRuntimeError, "The reference to the parsed document has been lost.");
  }else if(anchor->parser->failure){
    rb_raise(rb_eRuntimeError, "Can not perform all operations when parsing fails.");
  }
  return anchor;
}

static inline anchor_t *getAnchorUnsafe(VALUE segment_rb){
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

static VALUE segment_get_property(VALUE self, VALUE element, VALUE component){
  anchor_t *anchor = getAnchor(self);
  char *ptr = propertyLookup(anchor->segment, NUM2SHORT(element), NUM2SHORT(component));
  return (ptr ? rb_str_new_cstr(ptr) : Qnil);
}

static VALUE document_errors(VALUE self){
  anchor_t *anchor = getAnchorUnsafe(self);
  return getErrors(anchor->parser);
}

static VALUE document_has_errors(VALUE self){
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

static VALUE getDocClass(const char *doctype){
  VALUE doc;
  if(strcmp(doctype, "835") == 0){
    doc = cDoc835;
  }else{
    rb_raise(rb_eRuntimeError, "Unable to create document.");
  }
  return doc;
}

static VALUE segment_document_type(VALUE self){
  anchor_t *anchor = getAnchor(self);
  return getDocClass(anchor->parser->documentType);
}

static VALUE segment_root(VALUE self){
  anchor_t *anchor = getAnchor(self);
  return buildSegmentNode(anchor->parser, anchor->parser->root);
}

static VALUE segment_document(VALUE self){
  anchor_t *anchor = getAnchor(self);
  return anchor->parser->doc;
}

void Init_choo_choo_ext(void) {
  mEDI835 = rb_define_module("EDI835");
  mChooChoo = rb_define_module("ChooChoo");
  cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  cParser = rb_define_class_under(mChooChoo, "Parser", rb_cObject);
  cDocument = rb_define_class_under(mChooChoo, "Document", rb_cObject);
  cISA = rb_define_class_under(mChooChoo, "ISA", cSegment);
  cDoc835 = rb_define_class_under(mEDI835, "Document", cDocument);

  rb_define_alloc_func(cDocument, document_alloc);
  rb_define_method(cDocument, "_c_isa_segment", segment_root,0);
  rb_define_method(cDocument, "_c_errors", document_errors, 0);
  rb_define_method(cDocument, "_c_errors?", document_has_errors, 0);

  rb_define_method(cParser, "_c_parse_835", choo_choo_parse_835, 1);

  rb_define_alloc_func(cSegment, segment_alloc);
  rb_define_method(cSegment, "_c_document_type", segment_document_type, 0);
  rb_define_method(cSegment, "_c_name", segment_name, 0);
  rb_define_method(cSegment, "_c_isa_segment", segment_root, 0);
  rb_define_method(cSegment, "_c_doc", segment_document, 0);
  rb_define_method(cSegment, "_c_to_hash", segment_to_hash, 0);
  rb_define_method(cSegment, "_c_descendants", segment_find, 2);
  rb_define_method(cSegment, "_c_children", segment_children, 2);
  rb_define_method(cSegment, "_c_parent", segment_parent, 0);
  rb_define_method(cSegment, "_c_get_property", segment_get_property, 2);
  rb_define_method(cSegment, "_c_where", segment_where, 5);
  rb_define_method(cSegment, "_c_exists?", segment_exists, 4);

  id_force_8_bit = rb_intern("b");

  //init_choo_choo_835();
  init_choo_choo_traversal();
  init_choo_choo_segment();
}