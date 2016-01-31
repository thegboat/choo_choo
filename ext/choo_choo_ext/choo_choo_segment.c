//
//  choo_choo_segment.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//
#include "choo_choo.h"

static void propertyFree(segment_t* segment);
static inline VALUE segmentGetPropery(VALUE segment_rb, short element, short component);

static VALUE mChooChoo;
static VALUE cSegment;

static VALUE cISA;
static VALUE cBPR;
static VALUE cTRN;
static VALUE cCUR;
static VALUE cDTM;
static VALUE cPER;
static VALUE cMIA;
static VALUE cREF;
static VALUE cCAS;
static VALUE cIEA;
static VALUE cQTY;
static VALUE cSVC;
static VALUE cCLP;
static VALUE cPLB;
static VALUE cTS3;
static VALUE cTS2;
static VALUE cMOA;
static VALUE cRDM;
static VALUE cLX;
static VALUE cLQ;
static VALUE cN1;
static VALUE cN3;
static VALUE cN4;
static VALUE cGS;
static VALUE cST;
static VALUE cGE;
static VALUE cSE;
static VALUE cNM1;
static VALUE cAMT;

void segmentInitializer(segment_t *segment, char *src){
  long idx = strlen(src);
  idx = idx > MAX_NAME_SIZE ? MAX_NAME_SIZE : idx;
  memset(segment->name,0,(MAX_NAME_SIZE+1)*sizeof(char));
  memcpy(segment->name,src,idx*sizeof(char));
  segment->elements = 0;
  segment->depth = 0;
  segment->children = 0;
  segment->propertyCache = st_init_numtable();
}

void cacheProperty(segment_t *segment, char *data, short element, short component){
  unsigned long key = getPropertyKey(element, component);
  if(strlen(data)){
    st_add_direct(segment->propertyCache, (st_data_t)key, (unsigned long)strdup(data));
  }else{
    st_add_direct(segment->propertyCache, (st_data_t)key, (unsigned long)(""));
  }
}

void addChildSegment(segment_t *parent, segment_t *child){
  if(NULL == parent->firstSegment){
    parent->firstSegment = child;
  }else{
    parent->lastSegment->tail = child;
    child->head = parent->lastSegment;
  }
  parent->children++;
  parent->lastSegment = child;
  child->parent = parent;
  child->depth = parent->depth + 1;
}

void segmentFree(segment_t *segment){
  if(NULL != segment){    
    if(segment->propertyCache){
      propertyFree(segment);
    }
    ediParsingDealloc(segment);
  }
}

segment_t *rewindLoop(segment_t *loop){
  segment_t *tmp;
  tmp = loop;
  while(NULL != tmp){
    loop = tmp;
    tmp = loop->head;
  }
  return loop;
}

static void propertyFree(segment_t* segment){
  char *ptr;
  for(short element=1;element<=segment->elements; element++){
    for(short component=0; component<100; component++){
      if((ptr = propertyLookup(segment, element, component))){
        if(strlen(ptr)) ediParsingDealloc(ptr);
      }else{
        break;
      }
    }
  }
  st_free_table(segment->propertyCache);
  segment->propertyCache = NULL;
}

static inline VALUE segmentGetPropery(VALUE segment_rb, short element, short component){
  anchor_t *anchor = getAnchor(segment_rb);
  char *ptr = propertyLookup(anchor->segment, element, component);
  return (ptr ? rb_str_new_cstr(ptr) : Qnil);
}

static VALUE isa01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE isa02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE isa03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE isa04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE isa05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE isa06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE isa07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE isa08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE isa09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE isa10(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE isa11(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE isa12(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE isa13(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE isa14(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE isa15(VALUE self){
  return segmentGetPropery(self, 15, 0);
}

static VALUE isa16(VALUE self){
  return segmentGetPropery(self, 16, 0);
}

static VALUE bpr01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE bpr02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE bpr03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE bpr04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE bpr05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE bpr06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE bpr07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE bpr08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE bpr09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE bpr10(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE bpr11(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE bpr12(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE bpr13(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE bpr14(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE bpr15(VALUE self){
  return segmentGetPropery(self, 15, 0);
}

static VALUE bpr16(VALUE self){
  return segmentGetPropery(self, 16, 0);
}

static VALUE bpr17(VALUE self){
  return segmentGetPropery(self, 17, 0);
}

static VALUE bpr18(VALUE self){
  return segmentGetPropery(self, 18, 0);
}

static VALUE bpr19(VALUE self){
  return segmentGetPropery(self, 19, 0);
}

static VALUE bpr20(VALUE self){
  return segmentGetPropery(self, 20, 0);
}

static VALUE bpr21(VALUE self){
  return segmentGetPropery(self, 21, 0);
}

static VALUE trn01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE trn02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE trn03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE trn04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE cur01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE cur02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE cur03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE cur04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE cur05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE cur06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE cur07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE cur08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE cur09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE cur10(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE cur11(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE cur12(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE cur13(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE cur14(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE cur15(VALUE self){
  return segmentGetPropery(self, 15, 0);
}

static VALUE cur16(VALUE self){
  return segmentGetPropery(self, 16, 0);
}

static VALUE cur17(VALUE self){
  return segmentGetPropery(self, 17, 0);
}

static VALUE cur18(VALUE self){
  return segmentGetPropery(self, 18, 0);
}

static VALUE cur19(VALUE self){
  return segmentGetPropery(self, 19, 0);
}

static VALUE cur20(VALUE self){
  return segmentGetPropery(self, 20, 0);
}

static VALUE cur21(VALUE self){
  return segmentGetPropery(self, 21, 0);
}

static VALUE dtm01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE dtm02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE dtm03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE dtm04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE dtm05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE dtm06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE per01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE per02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE per03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE per04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE per05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE per06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE per07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE per08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE per09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE mia01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE mia02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE mia03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE mia04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE mia05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE mia06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE mia07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE mia08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE mia09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE mia10(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE mia11(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE mia12(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE mia13(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE mia14(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE mia15(VALUE self){
  return segmentGetPropery(self, 15, 0);
}

static VALUE mia16(VALUE self){
  return segmentGetPropery(self, 16, 0);
}

static VALUE mia17(VALUE self){
  return segmentGetPropery(self, 17, 0);
}

static VALUE mia18(VALUE self){
  return segmentGetPropery(self, 18, 0);
}

static VALUE mia19(VALUE self){
  return segmentGetPropery(self, 19, 0);
}

static VALUE mia20(VALUE self){
  return segmentGetPropery(self, 20, 0);
}

static VALUE mia21(VALUE self){
  return segmentGetPropery(self, 21, 0);
}

static VALUE mia22(VALUE self){
  return segmentGetPropery(self, 22, 0);
}

static VALUE mia23(VALUE self){
  return segmentGetPropery(self, 23, 0);
}

static VALUE mia24(VALUE self){
  return segmentGetPropery(self, 24, 0);
}

static VALUE ref01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE ref02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE ref03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE ref04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE cas01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE cas02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE cas03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE cas04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE cas05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE cas06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE cas07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE cas08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE cas09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE cas10(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE cas11(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE cas12(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE cas13(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE cas14(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE cas15(VALUE self){
  return segmentGetPropery(self, 15, 0);
}

static VALUE cas16(VALUE self){
  return segmentGetPropery(self, 16, 0);
}

static VALUE cas17(VALUE self){
  return segmentGetPropery(self, 17, 0);
}

static VALUE cas18(VALUE self){
  return segmentGetPropery(self, 18, 0);
}

static VALUE cas19(VALUE self){
  return segmentGetPropery(self, 19, 0);
}

static VALUE iea01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE iea02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE qty01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE qty02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE qty03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE qty04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE svc01_01(VALUE self){
  return segmentGetPropery(self, 1, 1);
}

static VALUE svc01_02(VALUE self){
  return segmentGetPropery(self, 1, 2);
}

static VALUE svc01_03(VALUE self){
  return segmentGetPropery(self, 1, 3);
}

static VALUE svc01_04(VALUE self){
  return segmentGetPropery(self, 1, 4);
}

static VALUE svc01_05(VALUE self){
  return segmentGetPropery(self, 1, 5);
}

static VALUE svc01_06(VALUE self){
  return segmentGetPropery(self, 1, 6);
}

static VALUE svc01_07(VALUE self){
  return segmentGetPropery(self, 1, 7);
}

static VALUE svc02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE svc03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE svc04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE svc05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE svc06_01(VALUE self){
  return segmentGetPropery(self, 6, 1);
}

static VALUE svc06_02(VALUE self){
  return segmentGetPropery(self, 6, 2);
}

static VALUE svc06_03(VALUE self){
  return segmentGetPropery(self, 6, 3);
}

static VALUE svc06_04(VALUE self){
  return segmentGetPropery(self, 6, 4);
}

static VALUE svc06_05(VALUE self){
  return segmentGetPropery(self, 6, 5);
}

static VALUE svc06_06(VALUE self){
  return segmentGetPropery(self, 6, 6);
}

static VALUE svc06_07(VALUE self){
  return segmentGetPropery(self, 6, 7);
}

static VALUE svc06_08(VALUE self){
  return segmentGetPropery(self, 6, 8);
}

static VALUE svc07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE clp01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE clp02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE clp03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE clp04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE clp05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE clp06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE clp07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE clp08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE clp09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE clp10(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE clp11(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE clp12(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE clp13(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE clp14(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE plb01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE plb02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE plb03_01(VALUE self){
  return segmentGetPropery(self, 3, 1);
}

static VALUE plb03_02(VALUE self){
  return segmentGetPropery(self, 3, 2);
}

static VALUE plb04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE plb05_01(VALUE self){
  return segmentGetPropery(self, 5, 1);
}

static VALUE plb05_02(VALUE self){
  return segmentGetPropery(self, 5, 2);
}

static VALUE plb06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE plb07_01(VALUE self){
  return segmentGetPropery(self, 7, 1);
}

static VALUE plb07_02(VALUE self){
  return segmentGetPropery(self, 7, 2);
}

static VALUE plb08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE plb09_01(VALUE self){
  return segmentGetPropery(self, 9, 1);
}

static VALUE plb09_02(VALUE self){
  return segmentGetPropery(self, 9, 2);
}

static VALUE plb10(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE plb11_01(VALUE self){
  return segmentGetPropery(self, 11, 1);
}

static VALUE plb11_02(VALUE self){
  return segmentGetPropery(self, 11, 2);
}

static VALUE plb12(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE plb13_01(VALUE self){
  return segmentGetPropery(self, 13, 1);
}

static VALUE plb13_02(VALUE self){
  return segmentGetPropery(self, 13, 2);
}

static VALUE plb14(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE ts301(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE ts302(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE ts303(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE ts304(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE ts305(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE ts306(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE ts307(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE ts308(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE ts309(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE ts310(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE ts311(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE ts312(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE ts313(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE ts314(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE ts315(VALUE self){
  return segmentGetPropery(self, 15, 0);
}

static VALUE ts316(VALUE self){
  return segmentGetPropery(self, 16, 0);
}

static VALUE ts317(VALUE self){
  return segmentGetPropery(self, 17, 0);
}

static VALUE ts318(VALUE self){
  return segmentGetPropery(self, 18, 0);
}

static VALUE ts319(VALUE self){
  return segmentGetPropery(self, 19, 0);
}

static VALUE ts201(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE ts202(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE ts203(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE ts204(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE ts205(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE ts206(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE ts207(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE ts208(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE ts209(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE ts210(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE ts211(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE ts212(VALUE self){
  return segmentGetPropery(self, 12, 0);
}

static VALUE ts213(VALUE self){
  return segmentGetPropery(self, 13, 0);
}

static VALUE ts214(VALUE self){
  return segmentGetPropery(self, 14, 0);
}

static VALUE ts215(VALUE self){
  return segmentGetPropery(self, 15, 0);
}

static VALUE ts216(VALUE self){
  return segmentGetPropery(self, 16, 0);
}

static VALUE ts217(VALUE self){
  return segmentGetPropery(self, 17, 0);
}

static VALUE ts218(VALUE self){
  return segmentGetPropery(self, 18, 0);
}

static VALUE ts219(VALUE self){
  return segmentGetPropery(self, 19, 0);
}

static VALUE ts220(VALUE self){
  return segmentGetPropery(self, 20, 0);
}

static VALUE ts221(VALUE self){
  return segmentGetPropery(self, 21, 0);
}

static VALUE ts222(VALUE self){
  return segmentGetPropery(self, 22, 0);
}

static VALUE ts223(VALUE self){
  return segmentGetPropery(self, 23, 0);
}

static VALUE ts224(VALUE self){
  return segmentGetPropery(self, 24, 0);
}

static VALUE moa01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE moa02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE moa03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE moa04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE moa05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE moa06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE moa07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE moa08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE moa09(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE rdm01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE rdm02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE rdm03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE lx01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE lq01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE lq02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE n101(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE n102(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE n103(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE n104(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE n105(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE n106(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE n301(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE n302(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE n401(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE n402(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE n403(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE n404(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE n405(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE n406(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE gs01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE gs02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE gs03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE gs04(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE gs05(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE gs06(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE gs07(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE gs08(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE st01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE st02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE st03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE ge01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE ge02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE se01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE se02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE nm101(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE nm102(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE nm103(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

static VALUE nm104(VALUE self){
  return segmentGetPropery(self, 4, 0);
}

static VALUE nm105(VALUE self){
  return segmentGetPropery(self, 5, 0);
}

static VALUE nm106(VALUE self){
  return segmentGetPropery(self, 6, 0);
}

static VALUE nm107(VALUE self){
  return segmentGetPropery(self, 7, 0);
}

static VALUE nm108(VALUE self){
  return segmentGetPropery(self, 8, 0);
}

static VALUE nm109(VALUE self){
  return segmentGetPropery(self, 9, 0);
}

static VALUE nm110(VALUE self){
  return segmentGetPropery(self, 10, 0);
}

static VALUE nm111(VALUE self){
  return segmentGetPropery(self, 11, 0);
}

static VALUE amt01(VALUE self){
  return segmentGetPropery(self, 1, 0);
}

static VALUE amt02(VALUE self){
  return segmentGetPropery(self, 2, 0);
}

static VALUE amt03(VALUE self){
  return segmentGetPropery(self, 3, 0);
}

void init_choo_choo_segment(){
  mChooChoo = rb_define_module("ChooChoo");
  cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  cISA =  rb_define_class_under(mChooChoo, "ISA", cSegment);
  cBPR =  rb_define_class_under(mChooChoo, "BPR", cSegment);
  cTRN =  rb_define_class_under(mChooChoo, "TRN", cSegment);
  cCUR =  rb_define_class_under(mChooChoo, "CUR", cSegment);
  cDTM =  rb_define_class_under(mChooChoo, "DTM", cSegment);
  cPER =  rb_define_class_under(mChooChoo, "PER", cSegment);
  cMIA =  rb_define_class_under(mChooChoo, "MIA", cSegment);
  cREF =  rb_define_class_under(mChooChoo, "REF", cSegment);
  cCAS =  rb_define_class_under(mChooChoo, "CAS", cSegment);
  cIEA =  rb_define_class_under(mChooChoo, "IEA", cSegment);
  cQTY =  rb_define_class_under(mChooChoo, "QTY", cSegment);
  cSVC =  rb_define_class_under(mChooChoo, "SVC", cSegment);
  cCLP =  rb_define_class_under(mChooChoo, "CLP", cSegment);
  cPLB =  rb_define_class_under(mChooChoo, "PLB", cSegment);
  cTS3 =  rb_define_class_under(mChooChoo, "TS3", cSegment);
  cTS2 =  rb_define_class_under(mChooChoo, "TS2", cSegment);
  cMOA =  rb_define_class_under(mChooChoo, "MOA", cSegment);
  cRDM =  rb_define_class_under(mChooChoo, "RDM", cSegment);
  cLX =   rb_define_class_under(mChooChoo, "LX", cSegment);
  cLQ =   rb_define_class_under(mChooChoo, "LQ", cSegment);
  cN1 =   rb_define_class_under(mChooChoo, "N1", cSegment);
  cN3 =   rb_define_class_under(mChooChoo, "N3", cSegment);
  cN4 =   rb_define_class_under(mChooChoo, "N4", cSegment);
  cGS =   rb_define_class_under(mChooChoo, "GS", cSegment);
  cST =   rb_define_class_under(mChooChoo, "ST", cSegment);
  cGE =   rb_define_class_under(mChooChoo, "GE", cSegment);
  cSE =   rb_define_class_under(mChooChoo, "SE", cSegment);
  cNM1 =  rb_define_class_under(mChooChoo, "NM1", cSegment);
  cAMT =  rb_define_class_under(mChooChoo, "AMT", cSegment);
  rb_define_method(cISA, "ISA01", isa01, 0);
  rb_define_method(cISA, "ISA02", isa02, 0);
  rb_define_method(cISA, "ISA03", isa03, 0);
  rb_define_method(cISA, "ISA04", isa04, 0);
  rb_define_method(cISA, "ISA05", isa05, 0);
  rb_define_method(cISA, "ISA06", isa06, 0);
  rb_define_method(cISA, "ISA07", isa07, 0);
  rb_define_method(cISA, "ISA08", isa08, 0);
  rb_define_method(cISA, "ISA09", isa09, 0);
  rb_define_method(cISA, "ISA10", isa10, 0);
  rb_define_method(cISA, "ISA11", isa11, 0);
  rb_define_method(cISA, "ISA12", isa12, 0);
  rb_define_method(cISA, "ISA13", isa13, 0);
  rb_define_method(cISA, "ISA14", isa14, 0);
  rb_define_method(cISA, "ISA15", isa15, 0);
  rb_define_method(cISA, "ISA16", isa16, 0);
  rb_define_method(cBPR, "BPR01", bpr01, 0);
  rb_define_method(cBPR, "BPR02", bpr02, 0);
  rb_define_method(cBPR, "BPR03", bpr03, 0);
  rb_define_method(cBPR, "BPR04", bpr04, 0);
  rb_define_method(cBPR, "BPR05", bpr05, 0);
  rb_define_method(cBPR, "BPR06", bpr06, 0);
  rb_define_method(cBPR, "BPR07", bpr07, 0);
  rb_define_method(cBPR, "BPR08", bpr08, 0);
  rb_define_method(cBPR, "BPR09", bpr09, 0);
  rb_define_method(cBPR, "BPR10", bpr10, 0);
  rb_define_method(cBPR, "BPR11", bpr11, 0);
  rb_define_method(cBPR, "BPR12", bpr12, 0);
  rb_define_method(cBPR, "BPR13", bpr13, 0);
  rb_define_method(cBPR, "BPR14", bpr14, 0);
  rb_define_method(cBPR, "BPR15", bpr15, 0);
  rb_define_method(cBPR, "BPR16", bpr16, 0);
  rb_define_method(cBPR, "BPR17", bpr17, 0);
  rb_define_method(cBPR, "BPR18", bpr18, 0);
  rb_define_method(cBPR, "BPR19", bpr19, 0);
  rb_define_method(cBPR, "BPR20", bpr20, 0);
  rb_define_method(cBPR, "BPR21", bpr21, 0);
  rb_define_method(cTRN, "TRN01", trn01, 0);
  rb_define_method(cTRN, "TRN02", trn02, 0);
  rb_define_method(cTRN, "TRN03", trn03, 0);
  rb_define_method(cTRN, "TRN04", trn04, 0);
  rb_define_method(cCUR, "CUR01", cur01, 0);
  rb_define_method(cCUR, "CUR02", cur02, 0);
  rb_define_method(cCUR, "CUR03", cur03, 0);
  rb_define_method(cCUR, "CUR04", cur04, 0);
  rb_define_method(cCUR, "CUR05", cur05, 0);
  rb_define_method(cCUR, "CUR06", cur06, 0);
  rb_define_method(cCUR, "CUR07", cur07, 0);
  rb_define_method(cCUR, "CUR08", cur08, 0);
  rb_define_method(cCUR, "CUR09", cur09, 0);
  rb_define_method(cCUR, "CUR10", cur10, 0);
  rb_define_method(cCUR, "CUR11", cur11, 0);
  rb_define_method(cCUR, "CUR12", cur12, 0);
  rb_define_method(cCUR, "CUR13", cur13, 0);
  rb_define_method(cCUR, "CUR14", cur14, 0);
  rb_define_method(cCUR, "CUR15", cur15, 0);
  rb_define_method(cCUR, "CUR16", cur16, 0);
  rb_define_method(cCUR, "CUR17", cur17, 0);
  rb_define_method(cCUR, "CUR18", cur18, 0);
  rb_define_method(cCUR, "CUR19", cur19, 0);
  rb_define_method(cCUR, "CUR20", cur20, 0);
  rb_define_method(cCUR, "CUR21", cur21, 0);
  rb_define_method(cDTM, "DTM01", dtm01, 0);
  rb_define_method(cDTM, "DTM02", dtm02, 0);
  rb_define_method(cDTM, "DTM03", dtm03, 0);
  rb_define_method(cDTM, "DTM04", dtm04, 0);
  rb_define_method(cDTM, "DTM05", dtm05, 0);
  rb_define_method(cDTM, "DTM06", dtm06, 0);
  rb_define_method(cPER, "PER01", per01, 0);
  rb_define_method(cPER, "PER02", per02, 0);
  rb_define_method(cPER, "PER03", per03, 0);
  rb_define_method(cPER, "PER04", per04, 0);
  rb_define_method(cPER, "PER05", per05, 0);
  rb_define_method(cPER, "PER06", per06, 0);
  rb_define_method(cPER, "PER07", per07, 0);
  rb_define_method(cPER, "PER08", per08, 0);
  rb_define_method(cPER, "PER09", per09, 0);
  rb_define_method(cMIA, "MIA01", mia01, 0);
  rb_define_method(cMIA, "MIA02", mia02, 0);
  rb_define_method(cMIA, "MIA03", mia03, 0);
  rb_define_method(cMIA, "MIA04", mia04, 0);
  rb_define_method(cMIA, "MIA05", mia05, 0);
  rb_define_method(cMIA, "MIA06", mia06, 0);
  rb_define_method(cMIA, "MIA07", mia07, 0);
  rb_define_method(cMIA, "MIA08", mia08, 0);
  rb_define_method(cMIA, "MIA09", mia09, 0);
  rb_define_method(cMIA, "MIA10", mia10, 0);
  rb_define_method(cMIA, "MIA11", mia11, 0);
  rb_define_method(cMIA, "MIA12", mia12, 0);
  rb_define_method(cMIA, "MIA13", mia13, 0);
  rb_define_method(cMIA, "MIA14", mia14, 0);
  rb_define_method(cMIA, "MIA15", mia15, 0);
  rb_define_method(cMIA, "MIA16", mia16, 0);
  rb_define_method(cMIA, "MIA17", mia17, 0);
  rb_define_method(cMIA, "MIA18", mia18, 0);
  rb_define_method(cMIA, "MIA19", mia19, 0);
  rb_define_method(cMIA, "MIA20", mia20, 0);
  rb_define_method(cMIA, "MIA21", mia21, 0);
  rb_define_method(cMIA, "MIA22", mia22, 0);
  rb_define_method(cMIA, "MIA23", mia23, 0);
  rb_define_method(cMIA, "MIA24", mia24, 0);
  rb_define_method(cREF, "REF01", ref01, 0);
  rb_define_method(cREF, "REF02", ref02, 0);
  rb_define_method(cREF, "REF03", ref03, 0);
  rb_define_method(cREF, "REF04", ref04, 0);
  rb_define_method(cCAS, "CAS01", cas01, 0);
  rb_define_method(cCAS, "CAS02", cas02, 0);
  rb_define_method(cCAS, "CAS03", cas03, 0);
  rb_define_method(cCAS, "CAS04", cas04, 0);
  rb_define_method(cCAS, "CAS05", cas05, 0);
  rb_define_method(cCAS, "CAS06", cas06, 0);
  rb_define_method(cCAS, "CAS07", cas07, 0);
  rb_define_method(cCAS, "CAS08", cas08, 0);
  rb_define_method(cCAS, "CAS09", cas09, 0);
  rb_define_method(cCAS, "CAS10", cas10, 0);
  rb_define_method(cCAS, "CAS11", cas11, 0);
  rb_define_method(cCAS, "CAS12", cas12, 0);
  rb_define_method(cCAS, "CAS13", cas13, 0);
  rb_define_method(cCAS, "CAS14", cas14, 0);
  rb_define_method(cCAS, "CAS15", cas15, 0);
  rb_define_method(cCAS, "CAS16", cas16, 0);
  rb_define_method(cCAS, "CAS17", cas17, 0);
  rb_define_method(cCAS, "CAS18", cas18, 0);
  rb_define_method(cCAS, "CAS19", cas19, 0);
  rb_define_method(cIEA, "IEA01", iea01, 0);
  rb_define_method(cIEA, "IEA02", iea02, 0);
  rb_define_method(cQTY, "QTY01", qty01, 0);
  rb_define_method(cQTY, "QTY02", qty02, 0);
  rb_define_method(cQTY, "QTY03", qty03, 0);
  rb_define_method(cQTY, "QTY04", qty04, 0);
  rb_define_method(cSVC, "SVC01_01", svc01_01, 0);
  rb_define_method(cSVC, "SVC01_02", svc01_02, 0);
  rb_define_method(cSVC, "SVC01_03", svc01_03, 0);
  rb_define_method(cSVC, "SVC01_04", svc01_04, 0);
  rb_define_method(cSVC, "SVC01_05", svc01_05, 0);
  rb_define_method(cSVC, "SVC01_06", svc01_06, 0);
  rb_define_method(cSVC, "SVC01_07", svc01_07, 0);
  rb_define_method(cSVC, "SVC02", svc02, 0);
  rb_define_method(cSVC, "SVC03", svc03, 0);
  rb_define_method(cSVC, "SVC04", svc04, 0);
  rb_define_method(cSVC, "SVC05", svc05, 0);
  rb_define_method(cSVC, "SVC06_01", svc06_01, 0);
  rb_define_method(cSVC, "SVC06_02", svc06_02, 0);
  rb_define_method(cSVC, "SVC06_03", svc06_03, 0);
  rb_define_method(cSVC, "SVC06_04", svc06_04, 0);
  rb_define_method(cSVC, "SVC06_05", svc06_05, 0);
  rb_define_method(cSVC, "SVC06_06", svc06_06, 0);
  rb_define_method(cSVC, "SVC06_07", svc06_07, 0);
  rb_define_method(cSVC, "SVC06_08", svc06_08, 0);
  rb_define_method(cSVC, "SVC07", svc07, 0);
  rb_define_method(cCLP, "CLP01", clp01, 0);
  rb_define_method(cCLP, "CLP02", clp02, 0);
  rb_define_method(cCLP, "CLP03", clp03, 0);
  rb_define_method(cCLP, "CLP04", clp04, 0);
  rb_define_method(cCLP, "CLP05", clp05, 0);
  rb_define_method(cCLP, "CLP06", clp06, 0);
  rb_define_method(cCLP, "CLP07", clp07, 0);
  rb_define_method(cCLP, "CLP08", clp08, 0);
  rb_define_method(cCLP, "CLP09", clp09, 0);
  rb_define_method(cCLP, "CLP10", clp10, 0);
  rb_define_method(cCLP, "CLP11", clp11, 0);
  rb_define_method(cCLP, "CLP12", clp12, 0);
  rb_define_method(cCLP, "CLP13", clp13, 0);
  rb_define_method(cCLP, "CLP14", clp14, 0);
  rb_define_method(cPLB, "PLB01", plb01, 0);
  rb_define_method(cPLB, "PLB02", plb02, 0);
  rb_define_method(cPLB, "PLB03_01", plb03_01, 0);
  rb_define_method(cPLB, "PLB03_02", plb03_02, 0);
  rb_define_method(cPLB, "PLB04", plb04, 0);
  rb_define_method(cPLB, "PLB05_01", plb05_01, 0);
  rb_define_method(cPLB, "PLB05_02", plb05_02, 0);
  rb_define_method(cPLB, "PLB06", plb06, 0);
  rb_define_method(cPLB, "PLB07_01", plb07_01, 0);
  rb_define_method(cPLB, "PLB07_02", plb07_02, 0);
  rb_define_method(cPLB, "PLB08", plb08, 0);
  rb_define_method(cPLB, "PLB09_01", plb09_01, 0);
  rb_define_method(cPLB, "PLB09_02", plb09_02, 0);
  rb_define_method(cPLB, "PLB10", plb10, 0);
  rb_define_method(cPLB, "PLB11_01", plb11_01, 0);
  rb_define_method(cPLB, "PLB11_02", plb11_02, 0);
  rb_define_method(cPLB, "PLB12", plb12, 0);
  rb_define_method(cPLB, "PLB13_01", plb13_01, 0);
  rb_define_method(cPLB, "PLB13_02", plb13_02, 0);
  rb_define_method(cPLB, "PLB14", plb14, 0);
  rb_define_method(cTS3, "TS301", ts301, 0);
  rb_define_method(cTS3, "TS302", ts302, 0);
  rb_define_method(cTS3, "TS303", ts303, 0);
  rb_define_method(cTS3, "TS304", ts304, 0);
  rb_define_method(cTS3, "TS305", ts305, 0);
  rb_define_method(cTS3, "TS306", ts306, 0);
  rb_define_method(cTS3, "TS307", ts307, 0);
  rb_define_method(cTS3, "TS308", ts308, 0);
  rb_define_method(cTS3, "TS309", ts309, 0);
  rb_define_method(cTS3, "TS310", ts310, 0);
  rb_define_method(cTS3, "TS311", ts311, 0);
  rb_define_method(cTS3, "TS312", ts312, 0);
  rb_define_method(cTS3, "TS313", ts313, 0);
  rb_define_method(cTS3, "TS314", ts314, 0);
  rb_define_method(cTS3, "TS315", ts315, 0);
  rb_define_method(cTS3, "TS316", ts316, 0);
  rb_define_method(cTS3, "TS317", ts317, 0);
  rb_define_method(cTS3, "TS318", ts318, 0);
  rb_define_method(cTS3, "TS319", ts319, 0);
  rb_define_method(cTS2, "TS201", ts201, 0);
  rb_define_method(cTS2, "TS202", ts202, 0);
  rb_define_method(cTS2, "TS203", ts203, 0);
  rb_define_method(cTS2, "TS204", ts204, 0);
  rb_define_method(cTS2, "TS205", ts205, 0);
  rb_define_method(cTS2, "TS206", ts206, 0);
  rb_define_method(cTS2, "TS207", ts207, 0);
  rb_define_method(cTS2, "TS208", ts208, 0);
  rb_define_method(cTS2, "TS209", ts209, 0);
  rb_define_method(cTS2, "TS210", ts210, 0);
  rb_define_method(cTS2, "TS211", ts211, 0);
  rb_define_method(cTS2, "TS212", ts212, 0);
  rb_define_method(cTS2, "TS213", ts213, 0);
  rb_define_method(cTS2, "TS214", ts214, 0);
  rb_define_method(cTS2, "TS215", ts215, 0);
  rb_define_method(cTS2, "TS216", ts216, 0);
  rb_define_method(cTS2, "TS217", ts217, 0);
  rb_define_method(cTS2, "TS218", ts218, 0);
  rb_define_method(cTS2, "TS219", ts219, 0);
  rb_define_method(cTS2, "TS220", ts220, 0);
  rb_define_method(cTS2, "TS221", ts221, 0);
  rb_define_method(cTS2, "TS222", ts222, 0);
  rb_define_method(cTS2, "TS223", ts223, 0);
  rb_define_method(cTS2, "TS224", ts224, 0);
  rb_define_method(cMOA, "MOA01", moa01, 0);
  rb_define_method(cMOA, "MOA02", moa02, 0);
  rb_define_method(cMOA, "MOA03", moa03, 0);
  rb_define_method(cMOA, "MOA04", moa04, 0);
  rb_define_method(cMOA, "MOA05", moa05, 0);
  rb_define_method(cMOA, "MOA06", moa06, 0);
  rb_define_method(cMOA, "MOA07", moa07, 0);
  rb_define_method(cMOA, "MOA08", moa08, 0);
  rb_define_method(cMOA, "MOA09", moa09, 0);
  rb_define_method(cRDM, "RDM01", rdm01, 0);
  rb_define_method(cRDM, "RDM02", rdm02, 0);
  rb_define_method(cRDM, "RDM03", rdm03, 0);
  rb_define_method(cLX, "LX01", lx01, 0);
  rb_define_method(cLQ, "LQ01", lq01, 0);
  rb_define_method(cLQ, "LQ02", lq02, 0);
  rb_define_method(cN1, "N101", n101, 0);
  rb_define_method(cN1, "N102", n102, 0);
  rb_define_method(cN1, "N103", n103, 0);
  rb_define_method(cN1, "N104", n104, 0);
  rb_define_method(cN1, "N105", n105, 0);
  rb_define_method(cN1, "N106", n106, 0);
  rb_define_method(cN3, "N301", n301, 0);
  rb_define_method(cN3, "N302", n302, 0);
  rb_define_method(cN4, "N401", n401, 0);
  rb_define_method(cN4, "N402", n402, 0);
  rb_define_method(cN4, "N403", n403, 0);
  rb_define_method(cN4, "N404", n404, 0);
  rb_define_method(cN4, "N405", n405, 0);
  rb_define_method(cN4, "N406", n406, 0);
  rb_define_method(cGS, "GS01", gs01, 0);
  rb_define_method(cGS, "GS02", gs02, 0);
  rb_define_method(cGS, "GS03", gs03, 0);
  rb_define_method(cGS, "GS04", gs04, 0);
  rb_define_method(cGS, "GS05", gs05, 0);
  rb_define_method(cGS, "GS06", gs06, 0);
  rb_define_method(cGS, "GS07", gs07, 0);
  rb_define_method(cGS, "GS08", gs08, 0);
  rb_define_method(cST, "ST01", st01, 0);
  rb_define_method(cST, "ST02", st02, 0);
  rb_define_method(cST, "ST03", st03, 0);
  rb_define_method(cGE, "GE01", ge01, 0);
  rb_define_method(cGE, "GE02", ge02, 0);
  rb_define_method(cSE, "SE01", se01, 0);
  rb_define_method(cSE, "SE02", se02, 0);
  rb_define_method(cNM1, "NM101", nm101, 0);
  rb_define_method(cNM1, "NM102", nm102, 0);
  rb_define_method(cNM1, "NM103", nm103, 0);
  rb_define_method(cNM1, "NM104", nm104, 0);
  rb_define_method(cNM1, "NM105", nm105, 0);
  rb_define_method(cNM1, "NM106", nm106, 0);
  rb_define_method(cNM1, "NM107", nm107, 0);
  rb_define_method(cNM1, "NM108", nm108, 0);
  rb_define_method(cNM1, "NM109", nm109, 0);
  rb_define_method(cNM1, "NM110", nm110, 0);
  rb_define_method(cNM1, "NM111", nm111, 0);
  rb_define_method(cAMT, "AMT01", amt01, 0);
  rb_define_method(cAMT, "AMT02", amt02, 0);
  rb_define_method(cAMT, "AMT03", amt03, 0);
}
