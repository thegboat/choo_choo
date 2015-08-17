//
//  edi_parsing_inspection.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"

bool identify(char *src, const char *seg){
  if(NULL == src || strlen(src) < strlen(seg)){
    return false;
  }else{
    return 0 == strncmp(src, seg, strlen(seg));
  }
}

bool isPR(char *src){
  return identify(src, PR_LOOP);
}

bool isPE(char *src){
  return identify(src, PE_LOOP);
}

bool isISA(char *src){
  return identify(src, ISA_SEGMENT);
}

bool isIEA(char *src){
  return identify(src, IEA_SEGMENT);
}

bool isTS3(char *src){
  return identify(src, TS3_SEGMENT);
}

bool isTS2(char *src){
  return identify(src, TS2_SEGMENT);
}

bool isCLP(char *src){
  return identify(src, CLP_SEGMENT);
}

bool isCAS(char *src){
  return identify(src, CAS_SEGMENT);
}

bool isNM1(char *src){
  return identify(src, NM1_SEGMENT);
}

bool isMIA(char *src){
  return identify(src, MIA_SEGMENT);
}

bool isMOA(char *src){
  return identify(src, MOA_SEGMENT);
}

bool isAMT(char *src){
  return identify(src, AMT_SEGMENT);
}

bool isQTY(char *src){
  return identify(src, QTY_SEGMENT);
}

bool isSVC(char *src){
  return identify(src, SVC_SEGMENT);
}

bool isPLB(char *src){
  return identify(src, PLB_SEGMENT);
}

bool isRDM(char *src){
  return identify(src, RDM_SEGMENT);
}

bool isBPR(char *src){
  return identify(src, BPR_SEGMENT);
}

bool isTRN(char *src){
  return identify(src, TRN_SEGMENT);
}

bool isCUR(char *src){
  return identify(src, CUR_SEGMENT);
}

bool isREF(char *src){
  return identify(src, REF_SEGMENT);
}

bool isDTM(char *src){
  return identify(src, DTM_SEGMENT);
}

bool isPER(char *src){
  return identify(src, PER_SEGMENT);
}

bool isGS(char *src){
  return identify(src, GS_SEGMENT);
}
 
bool isGE(char *src){
  return identify(src, GE_SEGMENT);
}
 
bool isST(char *src){
  return identify(src, ST_SEGMENT);
}
 
bool isSE(char *src){
  return identify(src, SE_SEGMENT);
}
 
bool isN1(char *src){
  return identify(src, N1_SEGMENT);
}

bool isN4(char *src){
  return identify(src, N4_SEGMENT);
}

bool isN3(char *src){
  return identify(src, N3_SEGMENT);
}

bool isLX(char *src){
  return identify(src, LX_SEGMENT);
}

bool isLQ(char *src){
  return identify(src, LQ_SEGMENT);
}
