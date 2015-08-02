
#include <ruby.h>
#include "libedi.h"

extern VALUE mChooChoo;
extern VALUE cRemittanceObject;
extern VALUE cClaimLevelObject;
extern VALUE cChargeLevelObject;
extern VALUE cCheckLevelObject;


static VALUE choo_choo_parse_remittance(VALUE mChooChoo, const VALUE filestring, const VALUE filestring_length) {
  char *data = StringValueCStr(filestring);
  char buf[FIX2LONG(filestring_length)];
  edi_parser_t *p;
  edi_interchange_t *i;
  
  p = edi_parser_create(NULL);
  i = edi_parser_parse(p, data);
  
  edi_interchange_build(i, NULL, buf, sizeof(buf));
  edi_interchange_destroy(i);
    
  edi_parser_destroy(p);


  return rb_str_new_cstr(buf);
}



void Init_remittance_object(void){
  cRemittanceObject = rb_define_class_under(mChooChoo, "RemittanceObject", rb_cObject);
}

void Init_charge_level_object(void){
  cChargeLevelObject = rb_define_class_under(mChooChoo, "ChargeLevelObject", rb_cObject);
}

void Init_claim_level_object(void){
  cClaimLevelObject = rb_define_class_under(mChooChoo, "ClaimLevelObject", rb_cObject);
}

void Init_check_level_object(void){
  cCheckLevelObject = rb_define_class_under(mChooChoo, "CheckLevelObject", rb_cObject);
}

void Init_choo_choo_parsing(void) {
  mChooChoo = rb_define_module("ChooChoo");
  rb_define_singleton_method(mChooChoo, "_parse_remittance", choo_choo_parse_remittance, 2);

  Init_remittance_object();
  Init_charge_level_object();
  Init_claim_level_object();
  Init_check_level_object();
}