//
//  choo_choo_segment.c
//  choo_choo
//
//  Created by Grady Griffin on 1/28/16.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//

#include "choo_choo.h"

static VALUE segmentGetPropery(VALUE segment_rb, const char *key, short element, short component);
static void propertyFree(segment_t* segment);

static VALUE mChooChoo;
static VALUE mEDI835;
static VALUE cSegment;

// static VALUE cISA;
// static VALUE cBPR;
// static VALUE cTRN;
// static VALUE cCUR;
// static VALUE cDTM;
// static VALUE cPER;
// static VALUE cMIA;
// static VALUE cREF;
// static VALUE cCAS;
// static VALUE cIEA;
// static VALUE cQTY;
// static VALUE cSVC;
// static VALUE cCLP;
// static VALUE cPLB;
// static VALUE cTS3;
// static VALUE cTS2;
// static VALUE cMOA;
// static VALUE cRDM;
// static VALUE cLX;
// static VALUE cLQ;
// static VALUE cN1;
// static VALUE cN3;
// static VALUE cN4;
// static VALUE cGS;
// static VALUE cST;
// static VALUE cGE;
// static VALUE cSE;
// static VALUE cNM1;
// static VALUE cAMT;

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
    choo_chooDealloc(segment);
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
        if(strlen(ptr)) choo_chooDealloc(ptr);
      }else{
        break;
      }
    }
  }
  st_free_table(segment->propertyCache);
  segment->propertyCache = NULL;
}

static VALUE segmentGetPropery(VALUE segment_rb, const char *key, short element, short component){
  ID id_key = rb_intern(key);
  VALUE rtn = rb_ivar_get(segment_rb,id_key);
  anchor_t *anchor;
  char *ptr;

  if(rtn == Qnil){
    anchor = getAnchor(segment_rb);
    ptr = propertyLookup(anchor->segment, element, component);
    rtn = (ptr ? rb_ivar_set(segment_rb,id_key, rb_str_new_cstr(ptr)) : Qnil);
  }
  return rtn;
}

static VALUE isa01(VALUE self){
  return segmentGetPropery(self, "@isa01", 1, 0);
}

static VALUE isa02(VALUE self){
  return segmentGetPropery(self, "@isa02", 2, 0);
}

static VALUE isa03(VALUE self){
  return segmentGetPropery(self, "@isa03", 3, 0);
}

static VALUE isa04(VALUE self){
  return segmentGetPropery(self, "@isa04", 4, 0);
}

static VALUE isa05(VALUE self){
  return segmentGetPropery(self, "@isa05", 5, 0);
}

static VALUE isa06(VALUE self){
  return segmentGetPropery(self, "@isa06", 6, 0);
}

static VALUE isa07(VALUE self){
  return segmentGetPropery(self, "@isa07", 7, 0);
}

static VALUE isa08(VALUE self){
  return segmentGetPropery(self, "@isa08", 8, 0);
}

static VALUE isa09(VALUE self){
  return segmentGetPropery(self, "@isa09", 9, 0);
}

static VALUE isa10(VALUE self){
  return segmentGetPropery(self, "@isa10", 10, 0);
}

static VALUE isa11(VALUE self){
  return segmentGetPropery(self, "@isa11", 11, 0);
}

static VALUE isa12(VALUE self){
  return segmentGetPropery(self, "@isa12", 12, 0);
}

static VALUE isa13(VALUE self){
  return segmentGetPropery(self, "@isa13", 13, 0);
}

static VALUE isa14(VALUE self){
  return segmentGetPropery(self, "@isa14", 14, 0);
}

static VALUE isa15(VALUE self){
  return segmentGetPropery(self, "@isa15", 15, 0);
}

static VALUE isa16(VALUE self){
  return segmentGetPropery(self, "@isa16", 16, 0);
}

static VALUE bpr01(VALUE self){
  return segmentGetPropery(self, "@bpr01", 1, 0);
}

static VALUE bpr02(VALUE self){
  return segmentGetPropery(self, "@bpr02", 2, 0);
}

static VALUE bpr03(VALUE self){
  return segmentGetPropery(self, "@bpr03", 3, 0);
}

static VALUE bpr04(VALUE self){
  return segmentGetPropery(self, "@bpr04", 4, 0);
}

static VALUE bpr05(VALUE self){
  return segmentGetPropery(self, "@bpr05", 5, 0);
}

static VALUE bpr06(VALUE self){
  return segmentGetPropery(self, "@bpr06", 6, 0);
}

static VALUE bpr07(VALUE self){
  return segmentGetPropery(self, "@bpr07", 7, 0);
}

static VALUE bpr08(VALUE self){
  return segmentGetPropery(self, "@bpr08", 8, 0);
}

static VALUE bpr09(VALUE self){
  return segmentGetPropery(self, "@bpr09", 9, 0);
}

static VALUE bpr10(VALUE self){
  return segmentGetPropery(self, "@bpr10", 10, 0);
}

static VALUE bpr11(VALUE self){
  return segmentGetPropery(self, "@bpr11", 11, 0);
}

static VALUE bpr12(VALUE self){
  return segmentGetPropery(self, "@bpr12", 12, 0);
}

static VALUE bpr13(VALUE self){
  return segmentGetPropery(self, "@bpr13", 13, 0);
}

static VALUE bpr14(VALUE self){
  return segmentGetPropery(self, "@bpr14", 14, 0);
}

static VALUE bpr15(VALUE self){
  return segmentGetPropery(self, "@bpr15", 15, 0);
}

static VALUE bpr16(VALUE self){
  return segmentGetPropery(self, "@bpr16", 16, 0);
}

static VALUE bpr17(VALUE self){
  return segmentGetPropery(self, "@bpr17", 17, 0);
}

static VALUE bpr18(VALUE self){
  return segmentGetPropery(self, "@bpr18", 18, 0);
}

static VALUE bpr19(VALUE self){
  return segmentGetPropery(self, "@bpr19", 19, 0);
}

static VALUE bpr20(VALUE self){
  return segmentGetPropery(self, "@bpr20", 20, 0);
}

static VALUE bpr21(VALUE self){
  return segmentGetPropery(self, "@bpr21", 21, 0);
}

static VALUE trn01(VALUE self){
  return segmentGetPropery(self, "@trn01", 1, 0);
}

static VALUE trn02(VALUE self){
  return segmentGetPropery(self, "@trn02", 2, 0);
}

static VALUE trn03(VALUE self){
  return segmentGetPropery(self, "@trn03", 3, 0);
}

static VALUE trn04(VALUE self){
  return segmentGetPropery(self, "@trn04", 4, 0);
}

static VALUE cur01(VALUE self){
  return segmentGetPropery(self, "@cur01", 1, 0);
}

static VALUE cur02(VALUE self){
  return segmentGetPropery(self, "@cur02", 2, 0);
}

static VALUE cur03(VALUE self){
  return segmentGetPropery(self, "@cur03", 3, 0);
}

static VALUE cur04(VALUE self){
  return segmentGetPropery(self, "@cur04", 4, 0);
}

static VALUE cur05(VALUE self){
  return segmentGetPropery(self, "@cur05", 5, 0);
}

static VALUE cur06(VALUE self){
  return segmentGetPropery(self, "@cur06", 6, 0);
}

static VALUE cur07(VALUE self){
  return segmentGetPropery(self, "@cur07", 7, 0);
}

static VALUE cur08(VALUE self){
  return segmentGetPropery(self, "@cur08", 8, 0);
}

static VALUE cur09(VALUE self){
  return segmentGetPropery(self, "@cur09", 9, 0);
}

static VALUE cur10(VALUE self){
  return segmentGetPropery(self, "@cur10", 10, 0);
}

static VALUE cur11(VALUE self){
  return segmentGetPropery(self, "@cur11", 11, 0);
}

static VALUE cur12(VALUE self){
  return segmentGetPropery(self, "@cur12", 12, 0);
}

static VALUE cur13(VALUE self){
  return segmentGetPropery(self, "@cur13", 13, 0);
}

static VALUE cur14(VALUE self){
  return segmentGetPropery(self, "@cur14", 14, 0);
}

static VALUE cur15(VALUE self){
  return segmentGetPropery(self, "@cur15", 15, 0);
}

static VALUE cur16(VALUE self){
  return segmentGetPropery(self, "@cur16", 16, 0);
}

static VALUE cur17(VALUE self){
  return segmentGetPropery(self, "@cur17", 17, 0);
}

static VALUE cur18(VALUE self){
  return segmentGetPropery(self, "@cur18", 18, 0);
}

static VALUE cur19(VALUE self){
  return segmentGetPropery(self, "@cur19", 19, 0);
}

static VALUE cur20(VALUE self){
  return segmentGetPropery(self, "@cur20", 20, 0);
}

static VALUE cur21(VALUE self){
  return segmentGetPropery(self, "@cur21", 21, 0);
}

static VALUE dtm01(VALUE self){
  return segmentGetPropery(self, "@dtm01", 1, 0);
}

static VALUE dtm02(VALUE self){
  return segmentGetPropery(self, "@dtm02", 2, 0);
}

static VALUE dtm03(VALUE self){
  return segmentGetPropery(self, "@dtm03", 3, 0);
}

static VALUE dtm04(VALUE self){
  return segmentGetPropery(self, "@dtm04", 4, 0);
}

static VALUE dtm05(VALUE self){
  return segmentGetPropery(self, "@dtm05", 5, 0);
}

static VALUE dtm06(VALUE self){
  return segmentGetPropery(self, "@dtm06", 6, 0);
}

static VALUE per01(VALUE self){
  return segmentGetPropery(self, "@per01", 1, 0);
}

static VALUE per02(VALUE self){
  return segmentGetPropery(self, "@per02", 2, 0);
}

static VALUE per03(VALUE self){
  return segmentGetPropery(self, "@per03", 3, 0);
}

static VALUE per04(VALUE self){
  return segmentGetPropery(self, "@per04", 4, 0);
}

static VALUE per05(VALUE self){
  return segmentGetPropery(self, "@per05", 5, 0);
}

static VALUE per06(VALUE self){
  return segmentGetPropery(self, "@per06", 6, 0);
}

static VALUE per07(VALUE self){
  return segmentGetPropery(self, "@per07", 7, 0);
}

static VALUE per08(VALUE self){
  return segmentGetPropery(self, "@per08", 8, 0);
}

static VALUE per09(VALUE self){
  return segmentGetPropery(self, "@per09", 9, 0);
}

static VALUE mia01(VALUE self){
  return segmentGetPropery(self, "@mia01", 1, 0);
}

static VALUE mia02(VALUE self){
  return segmentGetPropery(self, "@mia02", 2, 0);
}

static VALUE mia03(VALUE self){
  return segmentGetPropery(self, "@mia03", 3, 0);
}

static VALUE mia04(VALUE self){
  return segmentGetPropery(self, "@mia04", 4, 0);
}

static VALUE mia05(VALUE self){
  return segmentGetPropery(self, "@mia05", 5, 0);
}

static VALUE mia06(VALUE self){
  return segmentGetPropery(self, "@mia06", 6, 0);
}

static VALUE mia07(VALUE self){
  return segmentGetPropery(self, "@mia07", 7, 0);
}

static VALUE mia08(VALUE self){
  return segmentGetPropery(self, "@mia08", 8, 0);
}

static VALUE mia09(VALUE self){
  return segmentGetPropery(self, "@mia09", 9, 0);
}

static VALUE mia10(VALUE self){
  return segmentGetPropery(self, "@mia10", 10, 0);
}

static VALUE mia11(VALUE self){
  return segmentGetPropery(self, "@mia11", 11, 0);
}

static VALUE mia12(VALUE self){
  return segmentGetPropery(self, "@mia12", 12, 0);
}

static VALUE mia13(VALUE self){
  return segmentGetPropery(self, "@mia13", 13, 0);
}

static VALUE mia14(VALUE self){
  return segmentGetPropery(self, "@mia14", 14, 0);
}

static VALUE mia15(VALUE self){
  return segmentGetPropery(self, "@mia15", 15, 0);
}

static VALUE mia16(VALUE self){
  return segmentGetPropery(self, "@mia16", 16, 0);
}

static VALUE mia17(VALUE self){
  return segmentGetPropery(self, "@mia17", 17, 0);
}

static VALUE mia18(VALUE self){
  return segmentGetPropery(self, "@mia18", 18, 0);
}

static VALUE mia19(VALUE self){
  return segmentGetPropery(self, "@mia19", 19, 0);
}

static VALUE mia20(VALUE self){
  return segmentGetPropery(self, "@mia20", 20, 0);
}

static VALUE mia21(VALUE self){
  return segmentGetPropery(self, "@mia21", 21, 0);
}

static VALUE mia22(VALUE self){
  return segmentGetPropery(self, "@mia22", 22, 0);
}

static VALUE mia23(VALUE self){
  return segmentGetPropery(self, "@mia23", 23, 0);
}

static VALUE mia24(VALUE self){
  return segmentGetPropery(self, "@mia24", 24, 0);
}

static VALUE ref01(VALUE self){
  return segmentGetPropery(self, "@ref01", 1, 0);
}

static VALUE ref02(VALUE self){
  return segmentGetPropery(self, "@ref02", 2, 0);
}

static VALUE ref03(VALUE self){
  return segmentGetPropery(self, "@ref03", 3, 0);
}

static VALUE ref04(VALUE self){
  return segmentGetPropery(self, "@ref04", 4, 0);
}

static VALUE cas01(VALUE self){
  return segmentGetPropery(self, "@cas01", 1, 0);
}

static VALUE cas02(VALUE self){
  return segmentGetPropery(self, "@cas02", 2, 0);
}

static VALUE cas03(VALUE self){
  return segmentGetPropery(self, "@cas03", 3, 0);
}

static VALUE cas04(VALUE self){
  return segmentGetPropery(self, "@cas04", 4, 0);
}

static VALUE cas05(VALUE self){
  return segmentGetPropery(self, "@cas05", 5, 0);
}

static VALUE cas06(VALUE self){
  return segmentGetPropery(self, "@cas06", 6, 0);
}

static VALUE cas07(VALUE self){
  return segmentGetPropery(self, "@cas07", 7, 0);
}

static VALUE cas08(VALUE self){
  return segmentGetPropery(self, "@cas08", 8, 0);
}

static VALUE cas09(VALUE self){
  return segmentGetPropery(self, "@cas09", 9, 0);
}

static VALUE cas10(VALUE self){
  return segmentGetPropery(self, "@cas10", 10, 0);
}

static VALUE cas11(VALUE self){
  return segmentGetPropery(self, "@cas11", 11, 0);
}

static VALUE cas12(VALUE self){
  return segmentGetPropery(self, "@cas12", 12, 0);
}

static VALUE cas13(VALUE self){
  return segmentGetPropery(self, "@cas13", 13, 0);
}

static VALUE cas14(VALUE self){
  return segmentGetPropery(self, "@cas14", 14, 0);
}

static VALUE cas15(VALUE self){
  return segmentGetPropery(self, "@cas15", 15, 0);
}

static VALUE cas16(VALUE self){
  return segmentGetPropery(self, "@cas16", 16, 0);
}

static VALUE cas17(VALUE self){
  return segmentGetPropery(self, "@cas17", 17, 0);
}

static VALUE cas18(VALUE self){
  return segmentGetPropery(self, "@cas18", 18, 0);
}

static VALUE cas19(VALUE self){
  return segmentGetPropery(self, "@cas19", 19, 0);
}

static VALUE iea01(VALUE self){
  return segmentGetPropery(self, "@iea01", 1, 0);
}

static VALUE iea02(VALUE self){
  return segmentGetPropery(self, "@iea02", 2, 0);
}

static VALUE qty01(VALUE self){
  return segmentGetPropery(self, "@qty01", 1, 0);
}

static VALUE qty02(VALUE self){
  return segmentGetPropery(self, "@qty02", 2, 0);
}

static VALUE qty03(VALUE self){
  return segmentGetPropery(self, "@qty03", 3, 0);
}

static VALUE qty04(VALUE self){
  return segmentGetPropery(self, "@qty04", 4, 0);
}

static VALUE svc01_01(VALUE self){
  return segmentGetPropery(self, "@svc01_01", 1, 1);
}

static VALUE svc01_02(VALUE self){
  return segmentGetPropery(self, "@svc01_02", 1, 2);
}

static VALUE svc01_03(VALUE self){
  return segmentGetPropery(self, "@svc01_03", 1, 3);
}

static VALUE svc01_04(VALUE self){
  return segmentGetPropery(self, "@svc01_04", 1, 4);
}

static VALUE svc01_05(VALUE self){
  return segmentGetPropery(self, "@svc01_05", 1, 5);
}

static VALUE svc01_06(VALUE self){
  return segmentGetPropery(self, "@svc01_06", 1, 6);
}

static VALUE svc01_07(VALUE self){
  return segmentGetPropery(self, "@svc01_07", 1, 7);
}

static VALUE svc02(VALUE self){
  return segmentGetPropery(self, "@svc02", 2, 0);
}

static VALUE svc03(VALUE self){
  return segmentGetPropery(self, "@svc03", 3, 0);
}

static VALUE svc04(VALUE self){
  return segmentGetPropery(self, "@svc04", 4, 0);
}

static VALUE svc05(VALUE self){
  return segmentGetPropery(self, "@svc05", 5, 0);
}

static VALUE svc06_01(VALUE self){
  return segmentGetPropery(self, "@svc06_01", 6, 1);
}

static VALUE svc06_02(VALUE self){
  return segmentGetPropery(self, "@svc06_02", 6, 2);
}

static VALUE svc06_03(VALUE self){
  return segmentGetPropery(self, "@svc06_03", 6, 3);
}

static VALUE svc06_04(VALUE self){
  return segmentGetPropery(self, "@svc06_04", 6, 4);
}

static VALUE svc06_05(VALUE self){
  return segmentGetPropery(self, "@svc06_05", 6, 5);
}

static VALUE svc06_06(VALUE self){
  return segmentGetPropery(self, "@svc06_06", 6, 6);
}

static VALUE svc06_07(VALUE self){
  return segmentGetPropery(self, "@svc06_07", 6, 7);
}

static VALUE svc06_08(VALUE self){
  return segmentGetPropery(self, "@svc06_08", 6, 8);
}

static VALUE svc07(VALUE self){
  return segmentGetPropery(self, "@svc07", 7, 0);
}

static VALUE clp01(VALUE self){
  return segmentGetPropery(self, "@clp01", 1, 0);
}

static VALUE clp02(VALUE self){
  return segmentGetPropery(self, "@clp02", 2, 0);
}

static VALUE clp03(VALUE self){
  return segmentGetPropery(self, "@clp03", 3, 0);
}

static VALUE clp04(VALUE self){
  return segmentGetPropery(self, "@clp04", 4, 0);
}

static VALUE clp05(VALUE self){
  return segmentGetPropery(self, "@clp05", 5, 0);
}

static VALUE clp06(VALUE self){
  return segmentGetPropery(self, "@clp06", 6, 0);
}

static VALUE clp07(VALUE self){
  return segmentGetPropery(self, "@clp07", 7, 0);
}

static VALUE clp08(VALUE self){
  return segmentGetPropery(self, "@clp08", 8, 0);
}

static VALUE clp09(VALUE self){
  return segmentGetPropery(self, "@clp09", 9, 0);
}

static VALUE clp10(VALUE self){
  return segmentGetPropery(self, "@clp10", 10, 0);
}

static VALUE clp11(VALUE self){
  return segmentGetPropery(self, "@clp11", 11, 0);
}

static VALUE clp12(VALUE self){
  return segmentGetPropery(self, "@clp12", 12, 0);
}

static VALUE clp13(VALUE self){
  return segmentGetPropery(self, "@clp13", 13, 0);
}

static VALUE clp14(VALUE self){
  return segmentGetPropery(self, "@clp14", 14, 0);
}

static VALUE plb01(VALUE self){
  return segmentGetPropery(self, "@plb01", 1, 0);
}

static VALUE plb02(VALUE self){
  return segmentGetPropery(self, "@plb02", 2, 0);
}

static VALUE plb03_01(VALUE self){
  return segmentGetPropery(self, "@plb03_01", 3, 1);
}

static VALUE plb03_02(VALUE self){
  return segmentGetPropery(self, "@plb03_02", 3, 2);
}

static VALUE plb04(VALUE self){
  return segmentGetPropery(self, "@plb04", 4, 0);
}

static VALUE plb05_01(VALUE self){
  return segmentGetPropery(self, "@plb05_01", 5, 1);
}

static VALUE plb05_02(VALUE self){
  return segmentGetPropery(self, "@plb05_02", 5, 2);
}

static VALUE plb06(VALUE self){
  return segmentGetPropery(self, "@plb06", 6, 0);
}

static VALUE plb07_01(VALUE self){
  return segmentGetPropery(self, "@plb07_01", 7, 1);
}

static VALUE plb07_02(VALUE self){
  return segmentGetPropery(self, "@plb07_02", 7, 2);
}

static VALUE plb08(VALUE self){
  return segmentGetPropery(self, "@plb08", 8, 0);
}

static VALUE plb09_01(VALUE self){
  return segmentGetPropery(self, "@plb09_01", 9, 1);
}

static VALUE plb09_02(VALUE self){
  return segmentGetPropery(self, "@plb09_02", 9, 2);
}

static VALUE plb10(VALUE self){
  return segmentGetPropery(self, "@plb10", 10, 0);
}

static VALUE plb11_01(VALUE self){
  return segmentGetPropery(self, "@plb11_01", 11, 1);
}

static VALUE plb11_02(VALUE self){
  return segmentGetPropery(self, "@plb11_02", 11, 2);
}

static VALUE plb12(VALUE self){
  return segmentGetPropery(self, "@plb12", 12, 0);
}

static VALUE plb13_01(VALUE self){
  return segmentGetPropery(self, "@plb13_01", 13, 1);
}

static VALUE plb13_02(VALUE self){
  return segmentGetPropery(self, "@plb13_02", 13, 2);
}

static VALUE plb14(VALUE self){
  return segmentGetPropery(self, "@plb14", 14, 0);
}

static VALUE ts301(VALUE self){
  return segmentGetPropery(self, "@ts301", 1, 0);
}

static VALUE ts302(VALUE self){
  return segmentGetPropery(self, "@ts302", 2, 0);
}

static VALUE ts303(VALUE self){
  return segmentGetPropery(self, "@ts303", 3, 0);
}

static VALUE ts304(VALUE self){
  return segmentGetPropery(self, "@ts304", 4, 0);
}

static VALUE ts305(VALUE self){
  return segmentGetPropery(self, "@ts305", 5, 0);
}

static VALUE ts306(VALUE self){
  return segmentGetPropery(self, "@ts306", 6, 0);
}

static VALUE ts307(VALUE self){
  return segmentGetPropery(self, "@ts307", 7, 0);
}

static VALUE ts308(VALUE self){
  return segmentGetPropery(self, "@ts308", 8, 0);
}

static VALUE ts309(VALUE self){
  return segmentGetPropery(self, "@ts309", 9, 0);
}

static VALUE ts310(VALUE self){
  return segmentGetPropery(self, "@ts310", 10, 0);
}

static VALUE ts311(VALUE self){
  return segmentGetPropery(self, "@ts311", 11, 0);
}

static VALUE ts312(VALUE self){
  return segmentGetPropery(self, "@ts312", 12, 0);
}

static VALUE ts313(VALUE self){
  return segmentGetPropery(self, "@ts313", 13, 0);
}

static VALUE ts314(VALUE self){
  return segmentGetPropery(self, "@ts314", 14, 0);
}

static VALUE ts315(VALUE self){
  return segmentGetPropery(self, "@ts315", 15, 0);
}

static VALUE ts316(VALUE self){
  return segmentGetPropery(self, "@ts316", 16, 0);
}

static VALUE ts317(VALUE self){
  return segmentGetPropery(self, "@ts317", 17, 0);
}

static VALUE ts318(VALUE self){
  return segmentGetPropery(self, "@ts318", 18, 0);
}

static VALUE ts319(VALUE self){
  return segmentGetPropery(self, "@ts319", 19, 0);
}

static VALUE ts201(VALUE self){
  return segmentGetPropery(self, "@ts201", 1, 0);
}

static VALUE ts202(VALUE self){
  return segmentGetPropery(self, "@ts202", 2, 0);
}

static VALUE ts203(VALUE self){
  return segmentGetPropery(self, "@ts203", 3, 0);
}

static VALUE ts204(VALUE self){
  return segmentGetPropery(self, "@ts204", 4, 0);
}

static VALUE ts205(VALUE self){
  return segmentGetPropery(self, "@ts205", 5, 0);
}

static VALUE ts206(VALUE self){
  return segmentGetPropery(self, "@ts206", 6, 0);
}

static VALUE ts207(VALUE self){
  return segmentGetPropery(self, "@ts207", 7, 0);
}

static VALUE ts208(VALUE self){
  return segmentGetPropery(self, "@ts208", 8, 0);
}

static VALUE ts209(VALUE self){
  return segmentGetPropery(self, "@ts209", 9, 0);
}

static VALUE ts210(VALUE self){
  return segmentGetPropery(self, "@ts210", 10, 0);
}

static VALUE ts211(VALUE self){
  return segmentGetPropery(self, "@ts211", 11, 0);
}

static VALUE ts212(VALUE self){
  return segmentGetPropery(self, "@ts212", 12, 0);
}

static VALUE ts213(VALUE self){
  return segmentGetPropery(self, "@ts213", 13, 0);
}

static VALUE ts214(VALUE self){
  return segmentGetPropery(self, "@ts214", 14, 0);
}

static VALUE ts215(VALUE self){
  return segmentGetPropery(self, "@ts215", 15, 0);
}

static VALUE ts216(VALUE self){
  return segmentGetPropery(self, "@ts216", 16, 0);
}

static VALUE ts217(VALUE self){
  return segmentGetPropery(self, "@ts217", 17, 0);
}

static VALUE ts218(VALUE self){
  return segmentGetPropery(self, "@ts218", 18, 0);
}

static VALUE ts219(VALUE self){
  return segmentGetPropery(self, "@ts219", 19, 0);
}

static VALUE ts220(VALUE self){
  return segmentGetPropery(self, "@ts220", 20, 0);
}

static VALUE ts221(VALUE self){
  return segmentGetPropery(self, "@ts221", 21, 0);
}

static VALUE ts222(VALUE self){
  return segmentGetPropery(self, "@ts222", 22, 0);
}

static VALUE ts223(VALUE self){
  return segmentGetPropery(self, "@ts223", 23, 0);
}

static VALUE ts224(VALUE self){
  return segmentGetPropery(self, "@ts224", 24, 0);
}

static VALUE moa01(VALUE self){
  return segmentGetPropery(self, "@moa01", 1, 0);
}

static VALUE moa02(VALUE self){
  return segmentGetPropery(self, "@moa02", 2, 0);
}

static VALUE moa03(VALUE self){
  return segmentGetPropery(self, "@moa03", 3, 0);
}

static VALUE moa04(VALUE self){
  return segmentGetPropery(self, "@moa04", 4, 0);
}

static VALUE moa05(VALUE self){
  return segmentGetPropery(self, "@moa05", 5, 0);
}

static VALUE moa06(VALUE self){
  return segmentGetPropery(self, "@moa06", 6, 0);
}

static VALUE moa07(VALUE self){
  return segmentGetPropery(self, "@moa07", 7, 0);
}

static VALUE moa08(VALUE self){
  return segmentGetPropery(self, "@moa08", 8, 0);
}

static VALUE moa09(VALUE self){
  return segmentGetPropery(self, "@moa09", 9, 0);
}

static VALUE rdm01(VALUE self){
  return segmentGetPropery(self, "@rdm01", 1, 0);
}

static VALUE rdm02(VALUE self){
  return segmentGetPropery(self, "@rdm02", 2, 0);
}

static VALUE rdm03(VALUE self){
  return segmentGetPropery(self, "@rdm03", 3, 0);
}

static VALUE lx01(VALUE self){
  return segmentGetPropery(self, "@lx01", 1, 0);
}

static VALUE lq01(VALUE self){
  return segmentGetPropery(self, "@lq01", 1, 0);
}

static VALUE lq02(VALUE self){
  return segmentGetPropery(self, "@lq02", 2, 0);
}

static VALUE n101(VALUE self){
  return segmentGetPropery(self, "@n101", 1, 0);
}

static VALUE n102(VALUE self){
  return segmentGetPropery(self, "@n102", 2, 0);
}

static VALUE n103(VALUE self){
  return segmentGetPropery(self, "@n103", 3, 0);
}

static VALUE n104(VALUE self){
  return segmentGetPropery(self, "@n104", 4, 0);
}

static VALUE n105(VALUE self){
  return segmentGetPropery(self, "@n105", 5, 0);
}

static VALUE n106(VALUE self){
  return segmentGetPropery(self, "@n106", 6, 0);
}

static VALUE n301(VALUE self){
  return segmentGetPropery(self, "@n301", 1, 0);
}

static VALUE n302(VALUE self){
  return segmentGetPropery(self, "@n302", 2, 0);
}

static VALUE n401(VALUE self){
  return segmentGetPropery(self, "@n401", 1, 0);
}

static VALUE n402(VALUE self){
  return segmentGetPropery(self, "@n402", 2, 0);
}

static VALUE n403(VALUE self){
  return segmentGetPropery(self, "@n403", 3, 0);
}

static VALUE n404(VALUE self){
  return segmentGetPropery(self, "@n404", 4, 0);
}

static VALUE n405(VALUE self){
  return segmentGetPropery(self, "@n405", 5, 0);
}

static VALUE n406(VALUE self){
  return segmentGetPropery(self, "@n406", 6, 0);
}

static VALUE gs01(VALUE self){
  return segmentGetPropery(self, "@gs01", 1, 0);
}

static VALUE gs02(VALUE self){
  return segmentGetPropery(self, "@gs02", 2, 0);
}

static VALUE gs03(VALUE self){
  return segmentGetPropery(self, "@gs03", 3, 0);
}

static VALUE gs04(VALUE self){
  return segmentGetPropery(self, "@gs04", 4, 0);
}

static VALUE gs05(VALUE self){
  return segmentGetPropery(self, "@gs05", 5, 0);
}

static VALUE gs06(VALUE self){
  return segmentGetPropery(self, "@gs06", 6, 0);
}

static VALUE gs07(VALUE self){
  return segmentGetPropery(self, "@gs07", 7, 0);
}

static VALUE gs08(VALUE self){
  return segmentGetPropery(self, "@gs08", 8, 0);
}

static VALUE st01(VALUE self){
  return segmentGetPropery(self, "@st01", 1, 0);
}

static VALUE st02(VALUE self){
  return segmentGetPropery(self, "@st02", 2, 0);
}

static VALUE st03(VALUE self){
  return segmentGetPropery(self, "@st03", 3, 0);
}

static VALUE ge01(VALUE self){
  return segmentGetPropery(self, "@ge01", 1, 0);
}

static VALUE ge02(VALUE self){
  return segmentGetPropery(self, "@ge02", 2, 0);
}

static VALUE se01(VALUE self){
  return segmentGetPropery(self, "@se01", 1, 0);
}

static VALUE se02(VALUE self){
  return segmentGetPropery(self, "@se02", 2, 0);
}

static VALUE nm101(VALUE self){
  return segmentGetPropery(self, "@nm101", 1, 0);
}

static VALUE nm102(VALUE self){
  return segmentGetPropery(self, "@nm102", 2, 0);
}

static VALUE nm103(VALUE self){
  return segmentGetPropery(self, "@nm103", 3, 0);
}

static VALUE nm104(VALUE self){
  return segmentGetPropery(self, "@nm104", 4, 0);
}

static VALUE nm105(VALUE self){
  return segmentGetPropery(self, "@nm105", 5, 0);
}

static VALUE nm106(VALUE self){
  return segmentGetPropery(self, "@nm106", 6, 0);
}

static VALUE nm107(VALUE self){
  return segmentGetPropery(self, "@nm107", 7, 0);
}

static VALUE nm108(VALUE self){
  return segmentGetPropery(self, "@nm108", 8, 0);
}

static VALUE nm109(VALUE self){
  return segmentGetPropery(self, "@nm109", 9, 0);
}

static VALUE nm110(VALUE self){
  return segmentGetPropery(self, "@nm110", 10, 0);
}

static VALUE nm111(VALUE self){
  return segmentGetPropery(self, "@nm111", 11, 0);
}

static VALUE amt01(VALUE self){
  return segmentGetPropery(self, "@amt01", 1, 0);
}

static VALUE amt02(VALUE self){
  return segmentGetPropery(self, "@amt02", 2, 0);
}

static VALUE amt03(VALUE self){
  return segmentGetPropery(self, "@amt03", 3, 0);
}

void init_choo_choo_segment(){
  mEDI835 = rb_define_module("EDI835");
  mChooChoo = rb_define_module("ChooChoo");
  cSegment = rb_define_class_under(mChooChoo, "Segment", rb_cObject);
  VALUE cISA = rb_define_class_under(mChooChoo, "ISA", cSegment);
  VALUE cBPR = rb_define_class_under(mChooChoo, "BPR", cSegment);
  VALUE cTRN = rb_define_class_under(mChooChoo, "TRN", cSegment);
  VALUE cCUR = rb_define_class_under(mChooChoo, "CUR", cSegment);
  VALUE cDTM = rb_define_class_under(mChooChoo, "DTM", cSegment);
  VALUE cPER = rb_define_class_under(mChooChoo, "PER", cSegment);
  VALUE cMIA = rb_define_class_under(mChooChoo, "MIA", cSegment);
  VALUE cREF = rb_define_class_under(mChooChoo, "REF", cSegment);
  VALUE cCAS = rb_define_class_under(mChooChoo, "CAS", cSegment);
  VALUE cIEA = rb_define_class_under(mChooChoo, "IEA", cSegment);
  VALUE cQTY = rb_define_class_under(mChooChoo, "QTY", cSegment);
  VALUE cSVC = rb_define_class_under(mChooChoo, "SVC", cSegment);
  VALUE cCLP = rb_define_class_under(mChooChoo, "CLP", cSegment);
  VALUE cPLB = rb_define_class_under(mChooChoo, "PLB", cSegment);
  VALUE cTS3 = rb_define_class_under(mChooChoo, "TS3", cSegment);
  VALUE cTS2 = rb_define_class_under(mChooChoo, "TS2", cSegment);
  VALUE cMOA = rb_define_class_under(mChooChoo, "MOA", cSegment);
  VALUE cRDM = rb_define_class_under(mChooChoo, "RDM", cSegment);
  VALUE cLX = rb_define_class_under(mChooChoo, "LX", cSegment);
  VALUE cLQ = rb_define_class_under(mChooChoo, "LQ", cSegment);
  VALUE cN1 = rb_define_class_under(mChooChoo, "N1", cSegment);
  VALUE cN3 = rb_define_class_under(mChooChoo, "N3", cSegment);
  VALUE cN4 = rb_define_class_under(mChooChoo, "N4", cSegment);
  VALUE cGS = rb_define_class_under(mChooChoo, "GS", cSegment);
  VALUE cST = rb_define_class_under(mChooChoo, "ST", cSegment);
  VALUE cGE = rb_define_class_under(mChooChoo, "GE", cSegment);
  VALUE cSE = rb_define_class_under(mChooChoo, "SE", cSegment);
  VALUE cNM1 = rb_define_class_under(mChooChoo, "NM1", cSegment);
  VALUE cAMT = rb_define_class_under(mChooChoo, "AMT", cSegment);
  rb_define_method(cISA, "ISA01", isa01, 0);
  rb_define_method(cISA, "isa01", isa01, 0);
  rb_define_method(cISA, "ISA02", isa02, 0);
  rb_define_method(cISA, "isa02", isa02, 0);
  rb_define_method(cISA, "ISA03", isa03, 0);
  rb_define_method(cISA, "isa03", isa03, 0);
  rb_define_method(cISA, "ISA04", isa04, 0);
  rb_define_method(cISA, "isa04", isa04, 0);
  rb_define_method(cISA, "ISA05", isa05, 0);
  rb_define_method(cISA, "isa05", isa05, 0);
  rb_define_method(cISA, "ISA06", isa06, 0);
  rb_define_method(cISA, "isa06", isa06, 0);
  rb_define_method(cISA, "ISA07", isa07, 0);
  rb_define_method(cISA, "isa07", isa07, 0);
  rb_define_method(cISA, "ISA08", isa08, 0);
  rb_define_method(cISA, "isa08", isa08, 0);
  rb_define_method(cISA, "ISA09", isa09, 0);
  rb_define_method(cISA, "isa09", isa09, 0);
  rb_define_method(cISA, "ISA10", isa10, 0);
  rb_define_method(cISA, "isa10", isa10, 0);
  rb_define_method(cISA, "ISA11", isa11, 0);
  rb_define_method(cISA, "isa11", isa11, 0);
  rb_define_method(cISA, "ISA12", isa12, 0);
  rb_define_method(cISA, "isa12", isa12, 0);
  rb_define_method(cISA, "ISA13", isa13, 0);
  rb_define_method(cISA, "isa13", isa13, 0);
  rb_define_method(cISA, "ISA14", isa14, 0);
  rb_define_method(cISA, "isa14", isa14, 0);
  rb_define_method(cISA, "ISA15", isa15, 0);
  rb_define_method(cISA, "isa15", isa15, 0);
  rb_define_method(cISA, "ISA16", isa16, 0);
  rb_define_method(cISA, "isa16", isa16, 0);
  rb_define_method(cBPR, "BPR01", bpr01, 0);
  rb_define_method(cBPR, "bpr01", bpr01, 0);
  rb_define_method(cBPR, "BPR02", bpr02, 0);
  rb_define_method(cBPR, "bpr02", bpr02, 0);
  rb_define_method(cBPR, "BPR03", bpr03, 0);
  rb_define_method(cBPR, "bpr03", bpr03, 0);
  rb_define_method(cBPR, "BPR04", bpr04, 0);
  rb_define_method(cBPR, "bpr04", bpr04, 0);
  rb_define_method(cBPR, "BPR05", bpr05, 0);
  rb_define_method(cBPR, "bpr05", bpr05, 0);
  rb_define_method(cBPR, "BPR06", bpr06, 0);
  rb_define_method(cBPR, "bpr06", bpr06, 0);
  rb_define_method(cBPR, "BPR07", bpr07, 0);
  rb_define_method(cBPR, "bpr07", bpr07, 0);
  rb_define_method(cBPR, "BPR08", bpr08, 0);
  rb_define_method(cBPR, "bpr08", bpr08, 0);
  rb_define_method(cBPR, "BPR09", bpr09, 0);
  rb_define_method(cBPR, "bpr09", bpr09, 0);
  rb_define_method(cBPR, "BPR10", bpr10, 0);
  rb_define_method(cBPR, "bpr10", bpr10, 0);
  rb_define_method(cBPR, "BPR11", bpr11, 0);
  rb_define_method(cBPR, "bpr11", bpr11, 0);
  rb_define_method(cBPR, "BPR12", bpr12, 0);
  rb_define_method(cBPR, "bpr12", bpr12, 0);
  rb_define_method(cBPR, "BPR13", bpr13, 0);
  rb_define_method(cBPR, "bpr13", bpr13, 0);
  rb_define_method(cBPR, "BPR14", bpr14, 0);
  rb_define_method(cBPR, "bpr14", bpr14, 0);
  rb_define_method(cBPR, "BPR15", bpr15, 0);
  rb_define_method(cBPR, "bpr15", bpr15, 0);
  rb_define_method(cBPR, "BPR16", bpr16, 0);
  rb_define_method(cBPR, "bpr16", bpr16, 0);
  rb_define_method(cBPR, "BPR17", bpr17, 0);
  rb_define_method(cBPR, "bpr17", bpr17, 0);
  rb_define_method(cBPR, "BPR18", bpr18, 0);
  rb_define_method(cBPR, "bpr18", bpr18, 0);
  rb_define_method(cBPR, "BPR19", bpr19, 0);
  rb_define_method(cBPR, "bpr19", bpr19, 0);
  rb_define_method(cBPR, "BPR20", bpr20, 0);
  rb_define_method(cBPR, "bpr20", bpr20, 0);
  rb_define_method(cBPR, "BPR21", bpr21, 0);
  rb_define_method(cBPR, "bpr21", bpr21, 0);
  rb_define_method(cTRN, "TRN01", trn01, 0);
  rb_define_method(cTRN, "trn01", trn01, 0);
  rb_define_method(cTRN, "TRN02", trn02, 0);
  rb_define_method(cTRN, "trn02", trn02, 0);
  rb_define_method(cTRN, "TRN03", trn03, 0);
  rb_define_method(cTRN, "trn03", trn03, 0);
  rb_define_method(cTRN, "TRN04", trn04, 0);
  rb_define_method(cTRN, "trn04", trn04, 0);
  rb_define_method(cCUR, "CUR01", cur01, 0);
  rb_define_method(cCUR, "cur01", cur01, 0);
  rb_define_method(cCUR, "CUR02", cur02, 0);
  rb_define_method(cCUR, "cur02", cur02, 0);
  rb_define_method(cCUR, "CUR03", cur03, 0);
  rb_define_method(cCUR, "cur03", cur03, 0);
  rb_define_method(cCUR, "CUR04", cur04, 0);
  rb_define_method(cCUR, "cur04", cur04, 0);
  rb_define_method(cCUR, "CUR05", cur05, 0);
  rb_define_method(cCUR, "cur05", cur05, 0);
  rb_define_method(cCUR, "CUR06", cur06, 0);
  rb_define_method(cCUR, "cur06", cur06, 0);
  rb_define_method(cCUR, "CUR07", cur07, 0);
  rb_define_method(cCUR, "cur07", cur07, 0);
  rb_define_method(cCUR, "CUR08", cur08, 0);
  rb_define_method(cCUR, "cur08", cur08, 0);
  rb_define_method(cCUR, "CUR09", cur09, 0);
  rb_define_method(cCUR, "cur09", cur09, 0);
  rb_define_method(cCUR, "CUR10", cur10, 0);
  rb_define_method(cCUR, "cur10", cur10, 0);
  rb_define_method(cCUR, "CUR11", cur11, 0);
  rb_define_method(cCUR, "cur11", cur11, 0);
  rb_define_method(cCUR, "CUR12", cur12, 0);
  rb_define_method(cCUR, "cur12", cur12, 0);
  rb_define_method(cCUR, "CUR13", cur13, 0);
  rb_define_method(cCUR, "cur13", cur13, 0);
  rb_define_method(cCUR, "CUR14", cur14, 0);
  rb_define_method(cCUR, "cur14", cur14, 0);
  rb_define_method(cCUR, "CUR15", cur15, 0);
  rb_define_method(cCUR, "cur15", cur15, 0);
  rb_define_method(cCUR, "CUR16", cur16, 0);
  rb_define_method(cCUR, "cur16", cur16, 0);
  rb_define_method(cCUR, "CUR17", cur17, 0);
  rb_define_method(cCUR, "cur17", cur17, 0);
  rb_define_method(cCUR, "CUR18", cur18, 0);
  rb_define_method(cCUR, "cur18", cur18, 0);
  rb_define_method(cCUR, "CUR19", cur19, 0);
  rb_define_method(cCUR, "cur19", cur19, 0);
  rb_define_method(cCUR, "CUR20", cur20, 0);
  rb_define_method(cCUR, "cur20", cur20, 0);
  rb_define_method(cCUR, "CUR21", cur21, 0);
  rb_define_method(cCUR, "cur21", cur21, 0);
  rb_define_method(cDTM, "DTM01", dtm01, 0);
  rb_define_method(cDTM, "dtm01", dtm01, 0);
  rb_define_method(cDTM, "DTM02", dtm02, 0);
  rb_define_method(cDTM, "dtm02", dtm02, 0);
  rb_define_method(cDTM, "DTM03", dtm03, 0);
  rb_define_method(cDTM, "dtm03", dtm03, 0);
  rb_define_method(cDTM, "DTM04", dtm04, 0);
  rb_define_method(cDTM, "dtm04", dtm04, 0);
  rb_define_method(cDTM, "DTM05", dtm05, 0);
  rb_define_method(cDTM, "dtm05", dtm05, 0);
  rb_define_method(cDTM, "DTM06", dtm06, 0);
  rb_define_method(cDTM, "dtm06", dtm06, 0);
  rb_define_method(cPER, "PER01", per01, 0);
  rb_define_method(cPER, "per01", per01, 0);
  rb_define_method(cPER, "PER02", per02, 0);
  rb_define_method(cPER, "per02", per02, 0);
  rb_define_method(cPER, "PER03", per03, 0);
  rb_define_method(cPER, "per03", per03, 0);
  rb_define_method(cPER, "PER04", per04, 0);
  rb_define_method(cPER, "per04", per04, 0);
  rb_define_method(cPER, "PER05", per05, 0);
  rb_define_method(cPER, "per05", per05, 0);
  rb_define_method(cPER, "PER06", per06, 0);
  rb_define_method(cPER, "per06", per06, 0);
  rb_define_method(cPER, "PER07", per07, 0);
  rb_define_method(cPER, "per07", per07, 0);
  rb_define_method(cPER, "PER08", per08, 0);
  rb_define_method(cPER, "per08", per08, 0);
  rb_define_method(cPER, "PER09", per09, 0);
  rb_define_method(cPER, "per09", per09, 0);
  rb_define_method(cMIA, "MIA01", mia01, 0);
  rb_define_method(cMIA, "mia01", mia01, 0);
  rb_define_method(cMIA, "MIA02", mia02, 0);
  rb_define_method(cMIA, "mia02", mia02, 0);
  rb_define_method(cMIA, "MIA03", mia03, 0);
  rb_define_method(cMIA, "mia03", mia03, 0);
  rb_define_method(cMIA, "MIA04", mia04, 0);
  rb_define_method(cMIA, "mia04", mia04, 0);
  rb_define_method(cMIA, "MIA05", mia05, 0);
  rb_define_method(cMIA, "mia05", mia05, 0);
  rb_define_method(cMIA, "MIA06", mia06, 0);
  rb_define_method(cMIA, "mia06", mia06, 0);
  rb_define_method(cMIA, "MIA07", mia07, 0);
  rb_define_method(cMIA, "mia07", mia07, 0);
  rb_define_method(cMIA, "MIA08", mia08, 0);
  rb_define_method(cMIA, "mia08", mia08, 0);
  rb_define_method(cMIA, "MIA09", mia09, 0);
  rb_define_method(cMIA, "mia09", mia09, 0);
  rb_define_method(cMIA, "MIA10", mia10, 0);
  rb_define_method(cMIA, "mia10", mia10, 0);
  rb_define_method(cMIA, "MIA11", mia11, 0);
  rb_define_method(cMIA, "mia11", mia11, 0);
  rb_define_method(cMIA, "MIA12", mia12, 0);
  rb_define_method(cMIA, "mia12", mia12, 0);
  rb_define_method(cMIA, "MIA13", mia13, 0);
  rb_define_method(cMIA, "mia13", mia13, 0);
  rb_define_method(cMIA, "MIA14", mia14, 0);
  rb_define_method(cMIA, "mia14", mia14, 0);
  rb_define_method(cMIA, "MIA15", mia15, 0);
  rb_define_method(cMIA, "mia15", mia15, 0);
  rb_define_method(cMIA, "MIA16", mia16, 0);
  rb_define_method(cMIA, "mia16", mia16, 0);
  rb_define_method(cMIA, "MIA17", mia17, 0);
  rb_define_method(cMIA, "mia17", mia17, 0);
  rb_define_method(cMIA, "MIA18", mia18, 0);
  rb_define_method(cMIA, "mia18", mia18, 0);
  rb_define_method(cMIA, "MIA19", mia19, 0);
  rb_define_method(cMIA, "mia19", mia19, 0);
  rb_define_method(cMIA, "MIA20", mia20, 0);
  rb_define_method(cMIA, "mia20", mia20, 0);
  rb_define_method(cMIA, "MIA21", mia21, 0);
  rb_define_method(cMIA, "mia21", mia21, 0);
  rb_define_method(cMIA, "MIA22", mia22, 0);
  rb_define_method(cMIA, "mia22", mia22, 0);
  rb_define_method(cMIA, "MIA23", mia23, 0);
  rb_define_method(cMIA, "mia23", mia23, 0);
  rb_define_method(cMIA, "MIA24", mia24, 0);
  rb_define_method(cMIA, "mia24", mia24, 0);
  rb_define_method(cREF, "REF01", ref01, 0);
  rb_define_method(cREF, "ref01", ref01, 0);
  rb_define_method(cREF, "REF02", ref02, 0);
  rb_define_method(cREF, "ref02", ref02, 0);
  rb_define_method(cREF, "REF03", ref03, 0);
  rb_define_method(cREF, "ref03", ref03, 0);
  rb_define_method(cREF, "REF04", ref04, 0);
  rb_define_method(cREF, "ref04", ref04, 0);
  rb_define_method(cCAS, "CAS01", cas01, 0);
  rb_define_method(cCAS, "cas01", cas01, 0);
  rb_define_method(cCAS, "CAS02", cas02, 0);
  rb_define_method(cCAS, "cas02", cas02, 0);
  rb_define_method(cCAS, "CAS03", cas03, 0);
  rb_define_method(cCAS, "cas03", cas03, 0);
  rb_define_method(cCAS, "CAS04", cas04, 0);
  rb_define_method(cCAS, "cas04", cas04, 0);
  rb_define_method(cCAS, "CAS05", cas05, 0);
  rb_define_method(cCAS, "cas05", cas05, 0);
  rb_define_method(cCAS, "CAS06", cas06, 0);
  rb_define_method(cCAS, "cas06", cas06, 0);
  rb_define_method(cCAS, "CAS07", cas07, 0);
  rb_define_method(cCAS, "cas07", cas07, 0);
  rb_define_method(cCAS, "CAS08", cas08, 0);
  rb_define_method(cCAS, "cas08", cas08, 0);
  rb_define_method(cCAS, "CAS09", cas09, 0);
  rb_define_method(cCAS, "cas09", cas09, 0);
  rb_define_method(cCAS, "CAS10", cas10, 0);
  rb_define_method(cCAS, "cas10", cas10, 0);
  rb_define_method(cCAS, "CAS11", cas11, 0);
  rb_define_method(cCAS, "cas11", cas11, 0);
  rb_define_method(cCAS, "CAS12", cas12, 0);
  rb_define_method(cCAS, "cas12", cas12, 0);
  rb_define_method(cCAS, "CAS13", cas13, 0);
  rb_define_method(cCAS, "cas13", cas13, 0);
  rb_define_method(cCAS, "CAS14", cas14, 0);
  rb_define_method(cCAS, "cas14", cas14, 0);
  rb_define_method(cCAS, "CAS15", cas15, 0);
  rb_define_method(cCAS, "cas15", cas15, 0);
  rb_define_method(cCAS, "CAS16", cas16, 0);
  rb_define_method(cCAS, "cas16", cas16, 0);
  rb_define_method(cCAS, "CAS17", cas17, 0);
  rb_define_method(cCAS, "cas17", cas17, 0);
  rb_define_method(cCAS, "CAS18", cas18, 0);
  rb_define_method(cCAS, "cas18", cas18, 0);
  rb_define_method(cCAS, "CAS19", cas19, 0);
  rb_define_method(cCAS, "cas19", cas19, 0);
  rb_define_method(cIEA, "IEA01", iea01, 0);
  rb_define_method(cIEA, "iea01", iea01, 0);
  rb_define_method(cIEA, "IEA02", iea02, 0);
  rb_define_method(cIEA, "iea02", iea02, 0);
  rb_define_method(cQTY, "QTY01", qty01, 0);
  rb_define_method(cQTY, "qty01", qty01, 0);
  rb_define_method(cQTY, "QTY02", qty02, 0);
  rb_define_method(cQTY, "qty02", qty02, 0);
  rb_define_method(cQTY, "QTY03", qty03, 0);
  rb_define_method(cQTY, "qty03", qty03, 0);
  rb_define_method(cQTY, "QTY04", qty04, 0);
  rb_define_method(cQTY, "qty04", qty04, 0);
  rb_define_method(cSVC, "SVC01_01", svc01_01, 0);
  rb_define_method(cSVC, "svc01_01", svc01_01, 0);
  rb_define_method(cSVC, "SVC01_02", svc01_02, 0);
  rb_define_method(cSVC, "svc01_02", svc01_02, 0);
  rb_define_method(cSVC, "SVC01_03", svc01_03, 0);
  rb_define_method(cSVC, "svc01_03", svc01_03, 0);
  rb_define_method(cSVC, "SVC01_04", svc01_04, 0);
  rb_define_method(cSVC, "svc01_04", svc01_04, 0);
  rb_define_method(cSVC, "SVC01_05", svc01_05, 0);
  rb_define_method(cSVC, "svc01_05", svc01_05, 0);
  rb_define_method(cSVC, "SVC01_06", svc01_06, 0);
  rb_define_method(cSVC, "svc01_06", svc01_06, 0);
  rb_define_method(cSVC, "SVC01_07", svc01_07, 0);
  rb_define_method(cSVC, "svc01_07", svc01_07, 0);
  rb_define_method(cSVC, "SVC02", svc02, 0);
  rb_define_method(cSVC, "svc02", svc02, 0);
  rb_define_method(cSVC, "SVC03", svc03, 0);
  rb_define_method(cSVC, "svc03", svc03, 0);
  rb_define_method(cSVC, "SVC04", svc04, 0);
  rb_define_method(cSVC, "svc04", svc04, 0);
  rb_define_method(cSVC, "SVC05", svc05, 0);
  rb_define_method(cSVC, "svc05", svc05, 0);
  rb_define_method(cSVC, "SVC06_01", svc06_01, 0);
  rb_define_method(cSVC, "svc06_01", svc06_01, 0);
  rb_define_method(cSVC, "SVC06_02", svc06_02, 0);
  rb_define_method(cSVC, "svc06_02", svc06_02, 0);
  rb_define_method(cSVC, "SVC06_03", svc06_03, 0);
  rb_define_method(cSVC, "svc06_03", svc06_03, 0);
  rb_define_method(cSVC, "SVC06_04", svc06_04, 0);
  rb_define_method(cSVC, "svc06_04", svc06_04, 0);
  rb_define_method(cSVC, "SVC06_05", svc06_05, 0);
  rb_define_method(cSVC, "svc06_05", svc06_05, 0);
  rb_define_method(cSVC, "SVC06_06", svc06_06, 0);
  rb_define_method(cSVC, "svc06_06", svc06_06, 0);
  rb_define_method(cSVC, "SVC06_07", svc06_07, 0);
  rb_define_method(cSVC, "svc06_07", svc06_07, 0);
  rb_define_method(cSVC, "SVC06_08", svc06_08, 0);
  rb_define_method(cSVC, "svc06_08", svc06_08, 0);
  rb_define_method(cSVC, "SVC07", svc07, 0);
  rb_define_method(cSVC, "svc07", svc07, 0);
  rb_define_method(cCLP, "CLP01", clp01, 0);
  rb_define_method(cCLP, "clp01", clp01, 0);
  rb_define_method(cCLP, "CLP02", clp02, 0);
  rb_define_method(cCLP, "clp02", clp02, 0);
  rb_define_method(cCLP, "CLP03", clp03, 0);
  rb_define_method(cCLP, "clp03", clp03, 0);
  rb_define_method(cCLP, "CLP04", clp04, 0);
  rb_define_method(cCLP, "clp04", clp04, 0);
  rb_define_method(cCLP, "CLP05", clp05, 0);
  rb_define_method(cCLP, "clp05", clp05, 0);
  rb_define_method(cCLP, "CLP06", clp06, 0);
  rb_define_method(cCLP, "clp06", clp06, 0);
  rb_define_method(cCLP, "CLP07", clp07, 0);
  rb_define_method(cCLP, "clp07", clp07, 0);
  rb_define_method(cCLP, "CLP08", clp08, 0);
  rb_define_method(cCLP, "clp08", clp08, 0);
  rb_define_method(cCLP, "CLP09", clp09, 0);
  rb_define_method(cCLP, "clp09", clp09, 0);
  rb_define_method(cCLP, "CLP10", clp10, 0);
  rb_define_method(cCLP, "clp10", clp10, 0);
  rb_define_method(cCLP, "CLP11", clp11, 0);
  rb_define_method(cCLP, "clp11", clp11, 0);
  rb_define_method(cCLP, "CLP12", clp12, 0);
  rb_define_method(cCLP, "clp12", clp12, 0);
  rb_define_method(cCLP, "CLP13", clp13, 0);
  rb_define_method(cCLP, "clp13", clp13, 0);
  rb_define_method(cCLP, "CLP14", clp14, 0);
  rb_define_method(cCLP, "clp14", clp14, 0);
  rb_define_method(cPLB, "PLB01", plb01, 0);
  rb_define_method(cPLB, "plb01", plb01, 0);
  rb_define_method(cPLB, "PLB02", plb02, 0);
  rb_define_method(cPLB, "plb02", plb02, 0);
  rb_define_method(cPLB, "PLB03_01", plb03_01, 0);
  rb_define_method(cPLB, "plb03_01", plb03_01, 0);
  rb_define_method(cPLB, "PLB03_02", plb03_02, 0);
  rb_define_method(cPLB, "plb03_02", plb03_02, 0);
  rb_define_method(cPLB, "PLB04", plb04, 0);
  rb_define_method(cPLB, "plb04", plb04, 0);
  rb_define_method(cPLB, "PLB05_01", plb05_01, 0);
  rb_define_method(cPLB, "plb05_01", plb05_01, 0);
  rb_define_method(cPLB, "PLB05_02", plb05_02, 0);
  rb_define_method(cPLB, "plb05_02", plb05_02, 0);
  rb_define_method(cPLB, "PLB06", plb06, 0);
  rb_define_method(cPLB, "plb06", plb06, 0);
  rb_define_method(cPLB, "PLB07_01", plb07_01, 0);
  rb_define_method(cPLB, "plb07_01", plb07_01, 0);
  rb_define_method(cPLB, "PLB07_02", plb07_02, 0);
  rb_define_method(cPLB, "plb07_02", plb07_02, 0);
  rb_define_method(cPLB, "PLB08", plb08, 0);
  rb_define_method(cPLB, "plb08", plb08, 0);
  rb_define_method(cPLB, "PLB09_01", plb09_01, 0);
  rb_define_method(cPLB, "plb09_01", plb09_01, 0);
  rb_define_method(cPLB, "PLB09_02", plb09_02, 0);
  rb_define_method(cPLB, "plb09_02", plb09_02, 0);
  rb_define_method(cPLB, "PLB10", plb10, 0);
  rb_define_method(cPLB, "plb10", plb10, 0);
  rb_define_method(cPLB, "PLB11_01", plb11_01, 0);
  rb_define_method(cPLB, "plb11_01", plb11_01, 0);
  rb_define_method(cPLB, "PLB11_02", plb11_02, 0);
  rb_define_method(cPLB, "plb11_02", plb11_02, 0);
  rb_define_method(cPLB, "PLB12", plb12, 0);
  rb_define_method(cPLB, "plb12", plb12, 0);
  rb_define_method(cPLB, "PLB13_01", plb13_01, 0);
  rb_define_method(cPLB, "plb13_01", plb13_01, 0);
  rb_define_method(cPLB, "PLB13_02", plb13_02, 0);
  rb_define_method(cPLB, "plb13_02", plb13_02, 0);
  rb_define_method(cPLB, "PLB14", plb14, 0);
  rb_define_method(cPLB, "plb14", plb14, 0);
  rb_define_method(cTS3, "TS301", ts301, 0);
  rb_define_method(cTS3, "ts301", ts301, 0);
  rb_define_method(cTS3, "TS302", ts302, 0);
  rb_define_method(cTS3, "ts302", ts302, 0);
  rb_define_method(cTS3, "TS303", ts303, 0);
  rb_define_method(cTS3, "ts303", ts303, 0);
  rb_define_method(cTS3, "TS304", ts304, 0);
  rb_define_method(cTS3, "ts304", ts304, 0);
  rb_define_method(cTS3, "TS305", ts305, 0);
  rb_define_method(cTS3, "ts305", ts305, 0);
  rb_define_method(cTS3, "TS306", ts306, 0);
  rb_define_method(cTS3, "ts306", ts306, 0);
  rb_define_method(cTS3, "TS307", ts307, 0);
  rb_define_method(cTS3, "ts307", ts307, 0);
  rb_define_method(cTS3, "TS308", ts308, 0);
  rb_define_method(cTS3, "ts308", ts308, 0);
  rb_define_method(cTS3, "TS309", ts309, 0);
  rb_define_method(cTS3, "ts309", ts309, 0);
  rb_define_method(cTS3, "TS310", ts310, 0);
  rb_define_method(cTS3, "ts310", ts310, 0);
  rb_define_method(cTS3, "TS311", ts311, 0);
  rb_define_method(cTS3, "ts311", ts311, 0);
  rb_define_method(cTS3, "TS312", ts312, 0);
  rb_define_method(cTS3, "ts312", ts312, 0);
  rb_define_method(cTS3, "TS313", ts313, 0);
  rb_define_method(cTS3, "ts313", ts313, 0);
  rb_define_method(cTS3, "TS314", ts314, 0);
  rb_define_method(cTS3, "ts314", ts314, 0);
  rb_define_method(cTS3, "TS315", ts315, 0);
  rb_define_method(cTS3, "ts315", ts315, 0);
  rb_define_method(cTS3, "TS316", ts316, 0);
  rb_define_method(cTS3, "ts316", ts316, 0);
  rb_define_method(cTS3, "TS317", ts317, 0);
  rb_define_method(cTS3, "ts317", ts317, 0);
  rb_define_method(cTS3, "TS318", ts318, 0);
  rb_define_method(cTS3, "ts318", ts318, 0);
  rb_define_method(cTS3, "TS319", ts319, 0);
  rb_define_method(cTS3, "ts319", ts319, 0);
  rb_define_method(cTS2, "TS201", ts201, 0);
  rb_define_method(cTS2, "ts201", ts201, 0);
  rb_define_method(cTS2, "TS202", ts202, 0);
  rb_define_method(cTS2, "ts202", ts202, 0);
  rb_define_method(cTS2, "TS203", ts203, 0);
  rb_define_method(cTS2, "ts203", ts203, 0);
  rb_define_method(cTS2, "TS204", ts204, 0);
  rb_define_method(cTS2, "ts204", ts204, 0);
  rb_define_method(cTS2, "TS205", ts205, 0);
  rb_define_method(cTS2, "ts205", ts205, 0);
  rb_define_method(cTS2, "TS206", ts206, 0);
  rb_define_method(cTS2, "ts206", ts206, 0);
  rb_define_method(cTS2, "TS207", ts207, 0);
  rb_define_method(cTS2, "ts207", ts207, 0);
  rb_define_method(cTS2, "TS208", ts208, 0);
  rb_define_method(cTS2, "ts208", ts208, 0);
  rb_define_method(cTS2, "TS209", ts209, 0);
  rb_define_method(cTS2, "ts209", ts209, 0);
  rb_define_method(cTS2, "TS210", ts210, 0);
  rb_define_method(cTS2, "ts210", ts210, 0);
  rb_define_method(cTS2, "TS211", ts211, 0);
  rb_define_method(cTS2, "ts211", ts211, 0);
  rb_define_method(cTS2, "TS212", ts212, 0);
  rb_define_method(cTS2, "ts212", ts212, 0);
  rb_define_method(cTS2, "TS213", ts213, 0);
  rb_define_method(cTS2, "ts213", ts213, 0);
  rb_define_method(cTS2, "TS214", ts214, 0);
  rb_define_method(cTS2, "ts214", ts214, 0);
  rb_define_method(cTS2, "TS215", ts215, 0);
  rb_define_method(cTS2, "ts215", ts215, 0);
  rb_define_method(cTS2, "TS216", ts216, 0);
  rb_define_method(cTS2, "ts216", ts216, 0);
  rb_define_method(cTS2, "TS217", ts217, 0);
  rb_define_method(cTS2, "ts217", ts217, 0);
  rb_define_method(cTS2, "TS218", ts218, 0);
  rb_define_method(cTS2, "ts218", ts218, 0);
  rb_define_method(cTS2, "TS219", ts219, 0);
  rb_define_method(cTS2, "ts219", ts219, 0);
  rb_define_method(cTS2, "TS220", ts220, 0);
  rb_define_method(cTS2, "ts220", ts220, 0);
  rb_define_method(cTS2, "TS221", ts221, 0);
  rb_define_method(cTS2, "ts221", ts221, 0);
  rb_define_method(cTS2, "TS222", ts222, 0);
  rb_define_method(cTS2, "ts222", ts222, 0);
  rb_define_method(cTS2, "TS223", ts223, 0);
  rb_define_method(cTS2, "ts223", ts223, 0);
  rb_define_method(cTS2, "TS224", ts224, 0);
  rb_define_method(cTS2, "ts224", ts224, 0);
  rb_define_method(cMOA, "MOA01", moa01, 0);
  rb_define_method(cMOA, "moa01", moa01, 0);
  rb_define_method(cMOA, "MOA02", moa02, 0);
  rb_define_method(cMOA, "moa02", moa02, 0);
  rb_define_method(cMOA, "MOA03", moa03, 0);
  rb_define_method(cMOA, "moa03", moa03, 0);
  rb_define_method(cMOA, "MOA04", moa04, 0);
  rb_define_method(cMOA, "moa04", moa04, 0);
  rb_define_method(cMOA, "MOA05", moa05, 0);
  rb_define_method(cMOA, "moa05", moa05, 0);
  rb_define_method(cMOA, "MOA06", moa06, 0);
  rb_define_method(cMOA, "moa06", moa06, 0);
  rb_define_method(cMOA, "MOA07", moa07, 0);
  rb_define_method(cMOA, "moa07", moa07, 0);
  rb_define_method(cMOA, "MOA08", moa08, 0);
  rb_define_method(cMOA, "moa08", moa08, 0);
  rb_define_method(cMOA, "MOA09", moa09, 0);
  rb_define_method(cMOA, "moa09", moa09, 0);
  rb_define_method(cRDM, "RDM01", rdm01, 0);
  rb_define_method(cRDM, "rdm01", rdm01, 0);
  rb_define_method(cRDM, "RDM02", rdm02, 0);
  rb_define_method(cRDM, "rdm02", rdm02, 0);
  rb_define_method(cRDM, "RDM03", rdm03, 0);
  rb_define_method(cRDM, "rdm03", rdm03, 0);
  rb_define_method(cLX, "LX01", lx01, 0);
  rb_define_method(cLX, "lx01", lx01, 0);
  rb_define_method(cLQ, "LQ01", lq01, 0);
  rb_define_method(cLQ, "lq01", lq01, 0);
  rb_define_method(cLQ, "LQ02", lq02, 0);
  rb_define_method(cLQ, "lq02", lq02, 0);
  rb_define_method(cN1, "N101", n101, 0);
  rb_define_method(cN1, "n101", n101, 0);
  rb_define_method(cN1, "N102", n102, 0);
  rb_define_method(cN1, "n102", n102, 0);
  rb_define_method(cN1, "N103", n103, 0);
  rb_define_method(cN1, "n103", n103, 0);
  rb_define_method(cN1, "N104", n104, 0);
  rb_define_method(cN1, "n104", n104, 0);
  rb_define_method(cN1, "N105", n105, 0);
  rb_define_method(cN1, "n105", n105, 0);
  rb_define_method(cN1, "N106", n106, 0);
  rb_define_method(cN1, "n106", n106, 0);
  rb_define_method(cN3, "N301", n301, 0);
  rb_define_method(cN3, "n301", n301, 0);
  rb_define_method(cN3, "N302", n302, 0);
  rb_define_method(cN3, "n302", n302, 0);
  rb_define_method(cN4, "N401", n401, 0);
  rb_define_method(cN4, "n401", n401, 0);
  rb_define_method(cN4, "N402", n402, 0);
  rb_define_method(cN4, "n402", n402, 0);
  rb_define_method(cN4, "N403", n403, 0);
  rb_define_method(cN4, "n403", n403, 0);
  rb_define_method(cN4, "N404", n404, 0);
  rb_define_method(cN4, "n404", n404, 0);
  rb_define_method(cN4, "N405", n405, 0);
  rb_define_method(cN4, "n405", n405, 0);
  rb_define_method(cN4, "N406", n406, 0);
  rb_define_method(cN4, "n406", n406, 0);
  rb_define_method(cGS, "GS01", gs01, 0);
  rb_define_method(cGS, "gs01", gs01, 0);
  rb_define_method(cGS, "GS02", gs02, 0);
  rb_define_method(cGS, "gs02", gs02, 0);
  rb_define_method(cGS, "GS03", gs03, 0);
  rb_define_method(cGS, "gs03", gs03, 0);
  rb_define_method(cGS, "GS04", gs04, 0);
  rb_define_method(cGS, "gs04", gs04, 0);
  rb_define_method(cGS, "GS05", gs05, 0);
  rb_define_method(cGS, "gs05", gs05, 0);
  rb_define_method(cGS, "GS06", gs06, 0);
  rb_define_method(cGS, "gs06", gs06, 0);
  rb_define_method(cGS, "GS07", gs07, 0);
  rb_define_method(cGS, "gs07", gs07, 0);
  rb_define_method(cGS, "GS08", gs08, 0);
  rb_define_method(cGS, "gs08", gs08, 0);
  rb_define_method(cST, "ST01", st01, 0);
  rb_define_method(cST, "st01", st01, 0);
  rb_define_method(cST, "ST02", st02, 0);
  rb_define_method(cST, "st02", st02, 0);
  rb_define_method(cST, "ST03", st03, 0);
  rb_define_method(cST, "st03", st03, 0);
  rb_define_method(cGE, "GE01", ge01, 0);
  rb_define_method(cGE, "ge01", ge01, 0);
  rb_define_method(cGE, "GE02", ge02, 0);
  rb_define_method(cGE, "ge02", ge02, 0);
  rb_define_method(cSE, "SE01", se01, 0);
  rb_define_method(cSE, "se01", se01, 0);
  rb_define_method(cSE, "SE02", se02, 0);
  rb_define_method(cSE, "se02", se02, 0);
  rb_define_method(cNM1, "NM101", nm101, 0);
  rb_define_method(cNM1, "nm101", nm101, 0);
  rb_define_method(cNM1, "NM102", nm102, 0);
  rb_define_method(cNM1, "nm102", nm102, 0);
  rb_define_method(cNM1, "NM103", nm103, 0);
  rb_define_method(cNM1, "nm103", nm103, 0);
  rb_define_method(cNM1, "NM104", nm104, 0);
  rb_define_method(cNM1, "nm104", nm104, 0);
  rb_define_method(cNM1, "NM105", nm105, 0);
  rb_define_method(cNM1, "nm105", nm105, 0);
  rb_define_method(cNM1, "NM106", nm106, 0);
  rb_define_method(cNM1, "nm106", nm106, 0);
  rb_define_method(cNM1, "NM107", nm107, 0);
  rb_define_method(cNM1, "nm107", nm107, 0);
  rb_define_method(cNM1, "NM108", nm108, 0);
  rb_define_method(cNM1, "nm108", nm108, 0);
  rb_define_method(cNM1, "NM109", nm109, 0);
  rb_define_method(cNM1, "nm109", nm109, 0);
  rb_define_method(cNM1, "NM110", nm110, 0);
  rb_define_method(cNM1, "nm110", nm110, 0);
  rb_define_method(cNM1, "NM111", nm111, 0);
  rb_define_method(cNM1, "nm111", nm111, 0);
  rb_define_method(cAMT, "AMT01", amt01, 0);
  rb_define_method(cAMT, "amt01", amt01, 0);
  rb_define_method(cAMT, "AMT02", amt02, 0);
  rb_define_method(cAMT, "amt02", amt02, 0);
  rb_define_method(cAMT, "AMT03", amt03, 0);
  rb_define_method(cAMT, "amt03", amt03, 0);
}
