//
//  choo_choo_inspection.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//

#include "choo_choo.h"

bool identify(segment_t *segment, const char *seg){
  if(NULL == segment || strlen(segment->name) < strlen(seg)){
    return false;
  }else{
    return 0 == strcmp(segment->name, seg);
  }
}

bool isPR(segment_t *segment){
  return identify(segment, PR_LOOP);
}

bool isPE(segment_t *segment){
  return identify(segment, PE_LOOP);
}

bool isISA(segment_t *segment){
  return identify(segment, ISA_SEGMENT);
}

bool isIEA(segment_t *segment){
  return identify(segment, IEA_SEGMENT);
}

bool isTS3(segment_t *segment){
  return identify(segment, TS3_SEGMENT);
}

bool isTS2(segment_t *segment){
  return identify(segment, TS2_SEGMENT);
}

bool isCLP(segment_t *segment){
  return identify(segment, CLP_SEGMENT);
}

bool isCAS(segment_t *segment){
  return identify(segment, CAS_SEGMENT);
}

bool isNM1(segment_t *segment){
  return identify(segment, NM1_SEGMENT);
}

bool isMIA(segment_t *segment){
  return identify(segment, MIA_SEGMENT);
}

bool isMOA(segment_t *segment){
  return identify(segment, MOA_SEGMENT);
}

bool isAMT(segment_t *segment){
  return identify(segment, AMT_SEGMENT);
}

bool isQTY(segment_t *segment){
  return identify(segment, QTY_SEGMENT);
}

bool isSVC(segment_t *segment){
  return identify(segment, SVC_SEGMENT);
}

bool isPLB(segment_t *segment){
  return identify(segment, PLB_SEGMENT);
}

bool isRDM(segment_t *segment){
  return identify(segment, RDM_SEGMENT);
}

bool isBPR(segment_t *segment){
  return identify(segment, BPR_SEGMENT);
}

bool isTRN(segment_t *segment){
  return identify(segment, TRN_SEGMENT);
}

bool isCUR(segment_t *segment){
  return identify(segment, CUR_SEGMENT);
}

bool isREF(segment_t *segment){
  return identify(segment, REF_SEGMENT);
}

bool isDTM(segment_t *segment){
  return identify(segment, DTM_SEGMENT);
}

bool isPER(segment_t *segment){
  return identify(segment, PER_SEGMENT);
}

bool isGS(segment_t *segment){
  return identify(segment, GS_SEGMENT);
}
 
bool isGE(segment_t *segment){
  return identify(segment, GE_SEGMENT);
}
 
bool isST(segment_t *segment){
  return identify(segment, ST_SEGMENT);
}
 
bool isSE(segment_t *segment){
  return identify(segment, SE_SEGMENT);
}
 
bool isN1(segment_t *segment){
  return identify(segment, N1_SEGMENT);
}

bool isN4(segment_t *segment){
  return identify(segment, N4_SEGMENT);
}

bool isN3(segment_t *segment){
  return identify(segment, N3_SEGMENT);
}

bool isLX(segment_t *segment){
  return identify(segment, LX_SEGMENT);
}

bool isLQ(segment_t *segment){
  return identify(segment, LQ_SEGMENT);
}
