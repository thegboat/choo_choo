//
//  choo_choo_835.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//

#include "choo_choo.h"

static inline void attach835Segment(parser835_t *parser, segment_t *segment);
static inline void default835Handler(parser835_t *parser, segment_t *segment);
static inline void isa835Handler(parser835_t *parser, segment_t *segment);
static inline void iea835Handler(parser835_t *parser, segment_t *segment);
static inline void ts3835Handler(parser835_t *parser, segment_t *segment);
static inline void ts2835Handler(parser835_t *parser, segment_t *segment);
static inline void clp835Handler(parser835_t *parser, segment_t *segment);
static inline void nm1835Handler(parser835_t *parser, segment_t *segment);
static inline void mia835Handler(parser835_t *parser, segment_t *segment);
static inline void moa835Handler(parser835_t *parser, segment_t *segment);
static inline void amt835Handler(parser835_t *parser, segment_t *segment);
static inline void cas835Handler(parser835_t *parser, segment_t *segment);
static inline void qty835Handler(parser835_t *parser, segment_t *segment);
static inline void svc835Handler(parser835_t *parser, segment_t *segment);
static inline void plb835Handler(parser835_t *parser, segment_t *segment);
static inline void rdm835Handler(parser835_t *parser, segment_t *segment);
static inline void bpr835Handler(parser835_t *parser, segment_t *segment);
static inline void trn835Handler(parser835_t *parser, segment_t *segment);
static inline void cur835Handler(parser835_t *parser, segment_t *segment);
static inline void ref835Handler(parser835_t *parser, segment_t *segment);
static inline void dtm835Handler(parser835_t *parser, segment_t *segment);
static inline void per835Handler(parser835_t *parser, segment_t *segment);
static inline void ge835Handler(parser835_t *parser, segment_t *segment);
static inline void st835Handler(parser835_t *parser, segment_t *segment);
static inline void se835Handler(parser835_t *parser, segment_t *segment);
static inline void n1835Handler(parser835_t *parser, segment_t *segment);
static inline void n3835Handler(parser835_t *parser, segment_t *segment);
static inline void n4835Handler(parser835_t *parser, segment_t *segment);
static inline void lx835Handler(parser835_t *parser, segment_t *segment);
static inline void lq835Handler(parser835_t *parser, segment_t *segment);
static inline void gs835Handler(parser835_t *parser, segment_t *segment);
static inline void validate835Parser(parser835_t *parser);
static inline void parser835Initialization(parser835_t *parser);
static inline void parser835Cleanup(parser835_t *parser);


void parse835(parser_t *s_parser, const char *ediFile){
  char *copy = strdup(ediFile);
  char *rest = copy;
  parser835_t parser;
  parser.super = s_parser;
  parser835Initialization(&parser);
  segment_t *segment;
  while((parser.super->str = strsep(&rest, (char*)&SEGMENT_SEPARATOR)) && !parser.super->finished && !parser.super->failure){
    segment = parseSegment(parser.super);
    attach835Segment(&parser, segment);
  }
  parser835Cleanup(&parser);
  xfree(copy);
}

static inline void attach835Segment(parser835_t *parser, segment_t *segment){
  if(isISA(segment)){
    isa835Handler(parser, segment);
  }else if(NULL == parser->loop){
    parserFail(parser->super, ISA_SEGMENT_NOT_DETECTED_FIRST);
  }else if(isQTY(segment)){
    qty835Handler(parser, segment);
  }else if(isCAS(segment)){
    cas835Handler(parser, segment);
  }else if(isAMT(segment)){
    amt835Handler(parser, segment);
  }else if(isDTM(segment)){
    dtm835Handler(parser, segment);
  }else if(isREF(segment)){
    ref835Handler(parser, segment);
  }else if(isSVC(segment)){
    svc835Handler(parser, segment);
  }else if(isNM1(segment)){
    nm1835Handler(parser, segment);
  }else if(isMIA(segment)){
    mia835Handler(parser, segment);
  }else if(isMOA(segment)){
    moa835Handler(parser, segment);
  }else if(isLQ(segment)){
    lq835Handler(parser, segment);
  }else if(isCLP(segment)){
    clp835Handler(parser, segment);
  }else if(isPLB(segment)){
    plb835Handler(parser, segment);
  }else if(isPER(segment)){
    per835Handler(parser, segment);
  }else if(isN4(segment)){
    n4835Handler(parser, segment);
  }else if(isN3(segment)){
    n3835Handler(parser, segment);
  }else if(isRDM(segment)){
    rdm835Handler(parser, segment);
  }else if(isN1(segment)){
    n1835Handler(parser, segment);
  }else if(isTS3(segment)){
    ts3835Handler(parser, segment);
  }else if(isTS2(segment)){
    ts2835Handler(parser, segment);
  }else if(isLX(segment)){
    lx835Handler(parser, segment);
  }else if(isBPR(segment)){
    bpr835Handler(parser, segment);
  }else if(isTRN(segment)){
    trn835Handler(parser, segment);
  }else if(isCUR(segment)){
    cur835Handler(parser, segment);
  }else if(isST(segment)){
    st835Handler(parser, segment);
  }else if(isSE(segment)){
    se835Handler(parser, segment);
  }else if(isGS(segment)){
    gs835Handler(parser, segment);
  }else if(isGE(segment)){
    ge835Handler(parser, segment);
  }else if(isIEA(segment)){
    iea835Handler(parser, segment);
  }else{
    if(NULL == parser->loop){
      parserFail(parser->super, ISA_SEGMENT_NOT_DETECTED_FIRST);
    }else{
      parserFail(parser->super, UNKNOWN_ERROR);
    }
  }
}

static inline void default835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->loop, segment);
}

static inline void isa835Handler(parser835_t *parser, segment_t *segment){
  if(NULL != parser->loop || parser->loop != parser->interchange){
    parserFail(parser->super, INVALID_ISA_SEGMENT);
  }else if(!elementCountIn(segment, 16,16)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT);
  }else{   
    parser->super->root = segment;
    parser->interchange = segment;
    parser->loop = segment;
  }
}

static inline void iea835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop != parser->functional && !isGE(parser->trailer)){
    parserFail(parser->super, INVALID_IEA_SEGMENT);
  }else if(!elementCountIn(segment,2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT);
  }else{
    addChildSegment(parser->interchange, segment);
    parser->loop = parser->interchange;
    parser->trailer = segment;
    parser->super->finished = true;
  }
}

static inline void ts3835Handler(parser835_t *parser, segment_t *segment){
  if(!isLX(parser->loop)){
    parserFail(parser->super, INVALID_TS3_SEGMENT);
  }else if(!elementCountIn(segment,1,19)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_TS3_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void ts2835Handler(parser835_t *parser, segment_t *segment){
  if(!isLX(parser->loop)){
    parserFail(parser->super, INVALID_TS2_SEGMENT);
  }else if(!elementCountIn(segment,1,24)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_TS2_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void clp835Handler(parser835_t *parser, segment_t *segment){
  if(NULL == parser->header || (!isLX(parser->loop) && !isCLP(parser->loop) && !isSVC(parser->loop))){
    parserFail(parser->super, INVALID_CLP_SEGMENT);
  }else if(!elementCountIn(segment,3,14)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT);
  }else{
    parser->service = NULL;
    parser->loop = segment;
    addChildSegment(parser->header, segment);
    parser->claim = segment;
  }
}

static inline void nm1835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop)){
    parserFail(parser->super, INVALID_NM1_SEGMENT);
  }else if(!elementCountIn(segment,2,11)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void mia835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop)){
    parserFail(parser->super, INVALID_MIA_SEGMENT);
  }else if(!elementCountIn(segment,1,24)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_MIA_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void moa835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop)){
    parserFail(parser->super, INVALID_MOA_SEGMENT);
  }else if(!elementCountIn(segment,1,9)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_MOA_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void amt835Handler(parser835_t *parser, segment_t *segment){
  if(!isSVC(parser->loop) && !isCLP(parser->loop)){
    parserFail(parser->super, INVALID_AMT_SEGMENT);
  }else if(!elementCountIn(segment,2,3)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void cas835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_CAS_SEGMENT);
  }else if(!elementCountIn(segment,3,19)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void qty835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_QTY_SEGMENT);
  }else if(!elementCountIn(segment,2,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_QTY_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void svc835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_SVC_SEGMENT);
  }else if(!elementCountIn(segment,3,7)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT);
  }else{
    addChildSegment(parser->claim, segment);
    parser->service = segment;
    parser->loop = segment;
  }
}

static inline void plb835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop) && !isSVC(parser->loop) && !isST(parser->loop) && parser->loop != parser->payee){
    parserFail(parser->super, INVALID_PLB_SEGMENT);
  }else if(!elementCountIn(segment,4,14)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_PLB_SEGMENT);
  }else{
    parser->loop = parser->transaction;
    addChildSegment(parser->loop, segment);
  }
}

static inline void rdm835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop != parser->payee || NULL == parser->payee){
    parserFail(parser->super, INVALID_RDM_SEGMENT);
  }else if(!elementCountIn(segment,1,3)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_RDM_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void bpr835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop)){
    parserFail(parser->super, INVALID_BPR_SEGMENT);
  }else if(!elementCountIn(segment,16,21)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void trn835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop)){
    parserFail(parser->super, INVALID_TRN_SEGMENT);
  }else if(!elementCountIn(segment,3,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void cur835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop)){
    parserFail(parser->super, INVALID_CUR_SEGMENT);
  }else if(!elementCountIn(segment,2,21)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_CUR_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void ref835Handler(parser835_t *parser, segment_t *segment){
  if(!isN1(parser->loop) && !isST(parser->loop) && !isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_REF_SEGMENT);
  }else if(!elementCountIn(segment,1,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void dtm835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop) && !isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_DTM_SEGMENT);
  }else if(!elementCountIn(segment,1,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static inline void per835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop != parser->payer && parser->loop != parser->claim){
    parserFail(parser->super, INVALID_PER_SEGMENT);
  }else if(!elementCountIn(segment,1,9)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static inline void gs835Handler(parser835_t *parser, segment_t *segment){
  if(!isISA(parser->loop) && !isGE(parser->trailer)){
    parserFail(parser->super, INVALID_GS_SEGMENT);
  }else if(!elementCountIn(segment, 8,8)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
    parser->functional = segment;
    parser->loop = segment;
  }
}

static inline void ge835Handler(parser835_t *parser, segment_t *segment){
  if(!isSE(parser->trailer)){
    parserFail(parser->super, INVALID_GE_SEGMENT);
  }else if(!elementCountIn(segment,2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT);
  }else{
    parser->loop = parser->functional;
    addChildSegment(parser->loop, segment);
    parser->trailer = segment;
  }
}

static inline void st835Handler(parser835_t *parser, segment_t *segment){
  if(!isGS(parser->loop) && !isSE(parser->trailer)){
    parserFail(parser->super, INVALID_ST_SEGMENT);
  }else if(!elementCountIn(segment, 2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
    parser->transaction = segment;
    parser->loop = segment;
  }
}

static inline void se835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->transaction) || (NULL != parser->trailer && !isSE(parser->trailer) && !isGE(parser->trailer))){
    parserFail(parser->super, INVALID_SE_SEGMENT);
  }else if(!elementCountIn(segment,2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT);
  }else{
    parser->loop = parser->transaction;
    addChildSegment(parser->loop, segment);
    parser->trailer = segment;
  }
}

static inline void n1835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop) && (NULL == parser->payer || parser->loop != parser->payer)){
    parserFail(parser->super, INVALID_N1_SEGMENT);
  }else if(!elementCountIn(segment,2,6)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT);
  }else if(isST(parser->loop)){
    addChildSegment(parser->loop, segment);
    parser->payer = segment;
    parser->loop = segment;
  }else{
    addChildSegment(parser->loop, segment);
    parser->payee = segment;
    parser->loop = segment;
  }
}

static inline void n3835Handler(parser835_t *parser, segment_t *segment){
  if(!isN1(parser->loop)){
    parserFail(parser->super, INVALID_N3_SEGMENT);
  }else if(!elementCountIn(segment,1,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static inline void n4835Handler(parser835_t *parser, segment_t *segment){
  if(!isN1(parser->loop)){
    parserFail(parser->super, INVALID_N4_SEGMENT);
  }else if(!elementCountIn(segment,1,3)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static inline void lx835Handler(parser835_t *parser, segment_t *segment){
  if((parser->loop != parser->payee && parser->loop != parser->service) || NULL == parser->payee){
    parserFail(parser->super, INVALID_LX_SEGMENT);
  }else if(!elementCountIn(segment,1,1)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
    parser->header = segment;
    parser->loop = segment;
  }
}

static inline void lq835Handler(parser835_t *parser, segment_t *segment){
  if(!isSVC(parser->loop)){
    parserFail(parser->super, INVALID_LQ_SEGMENT);
  }else if(!elementCountIn(segment,2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static inline void parser835Initialization(parser835_t *parser){
  parser->interchange = NULL;
  parser->loop = NULL;
  parser->functional = NULL;
  parser->transaction = NULL;
  parser->payer = NULL;
  parser->payee = NULL;
  parser->header = NULL;
  parser->claim = NULL;
}

static inline void validate835Parser(parser835_t *parser){
  if(missingSegment(parser->super, ISA_SEGMENT)){
    parserFail(parser->super, MISSING_ISA_SEGMENT);
  }else if(missingSegment(parser->super, GS_SEGMENT)){
    parserFail(parser->super, MISSING_GS_SEGMENT);
  }else if(missingSegment(parser->super, ST_SEGMENT)){
    parserFail(parser->super, MISSING_ST_SEGMENT);
  }else if(missingSegment(parser->super, N1_SEGMENT)){
    parserFail(parser->super, MISSING_N1_SEGMENT);
  }else if(missingSegment(parser->super, SE_SEGMENT)){
    parserFail(parser->super, MISSING_SE_SEGMENT);
  }else if(missingSegment(parser->super, GE_SEGMENT)){
    parserFail(parser->super, MISSING_GE_SEGMENT);
  }else if(missingSegment(parser->super, IEA_SEGMENT)){
    parserFail(parser->super, MISSING_IEA_SEGMENT);
  }
}

static inline void parser835Cleanup(parser835_t *parser){
  parser->interchange = rewindLoop(parser->interchange);
  parser->super->root = parser->interchange;
  if(!parser->super->failure){
    buildIndexes(parser->super);
    validate835Parser(parser);
  }
  parser->super->finished = true;
}

void init_choo_choo_835(){
  
}



