//
//  edi_parsing_835.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"


static void attach835Segment(parser835_t *parser, segment_t *segment);
static void default835Handler(parser835_t *parser, segment_t *segment);
static void isa835Handler(parser835_t *parser, segment_t *segment);
static void iea835Handler(parser835_t *parser, segment_t *segment);
static void ts3835Handler(parser835_t *parser, segment_t *segment);
static void ts2835Handler(parser835_t *parser, segment_t *segment);
static void clp835Handler(parser835_t *parser, segment_t *segment);
static void nm1835Handler(parser835_t *parser, segment_t *segment);
static void mia835Handler(parser835_t *parser, segment_t *segment);
static void moa835Handler(parser835_t *parser, segment_t *segment);
static void amt835Handler(parser835_t *parser, segment_t *segment);
static void cas835Handler(parser835_t *parser, segment_t *segment);
static void qty835Handler(parser835_t *parser, segment_t *segment);
static void svc835Handler(parser835_t *parser, segment_t *segment);
static void plb835Handler(parser835_t *parser, segment_t *segment);
static void rdm835Handler(parser835_t *parser, segment_t *segment);
static void bpr835Handler(parser835_t *parser, segment_t *segment);
static void trn835Handler(parser835_t *parser, segment_t *segment);
static void cur835Handler(parser835_t *parser, segment_t *segment);
static void ref835Handler(parser835_t *parser, segment_t *segment);
static void dtm835Handler(parser835_t *parser, segment_t *segment);
static void per835Handler(parser835_t *parser, segment_t *segment);
static void ge835Handler(parser835_t *parser, segment_t *segment);
static void st835Handler(parser835_t *parser, segment_t *segment);
static void se835Handler(parser835_t *parser, segment_t *segment);
static void n1835Handler(parser835_t *parser, segment_t *segment);
static void n3835Handler(parser835_t *parser, segment_t *segment);
static void n4835Handler(parser835_t *parser, segment_t *segment);
static void lx835Handler(parser835_t *parser, segment_t *segment);
static void lq835Handler(parser835_t *parser, segment_t *segment);
static void gs835Handler(parser835_t *parser, segment_t *segment);
static void validate835Parser(parser835_t *parser);
static void parser835Free(parser835_t *parser);
static void parser835Initialization(parser835_t *parser);
static void parser835Cleanup(parser835_t *parser);
static void build835Indexes(parser835_t *parser);

void parse835(anchor_t *anchor, char *ediFile){
  parser_t *super = anchor->parser;
  parser835_t *parser = (parser835_t *)ediParsingMalloc(sizeof(parser835_t));
  parser->super = super;
  parser835Initialization(parser);
  segment_t *segment;
  char *saveptr;
  super->str = strtok_r(ediFile, SEGMENT_SEPARATOR, &saveptr);
  while(NULL != super->str && !super->finished && !super->failure){
    segment = parseSegment(super);
    attach835Segment(parser, segment);
    super->str = strtok_r(NULL, SEGMENT_SEPARATOR, &saveptr);
  }
  parser835Cleanup(parser);
  anchor->segment = parser->super->root;
  parser835Free(parser);
}

static void attach835Segment(parser835_t *parser, segment_t *segment){
  if(isISA(segment)){
    isa835Handler(parser, segment);
  }else if(isIEA(segment)){
    iea835Handler(parser, segment);
  }else if(isTS3(segment)){
    ts3835Handler(parser, segment);
  }else if(isTS2(segment)){
    ts2835Handler(parser, segment);
  }else if(isCLP(segment)){
    clp835Handler(parser, segment);
  }else if(isCAS(segment)){
    cas835Handler(parser, segment);
  }else if(isNM1(segment)){
    nm1835Handler(parser, segment);
  }else if(isMIA(segment)){
    mia835Handler(parser, segment);
  }else if(isMOA(segment)){
    moa835Handler(parser, segment);
  }else if(isAMT(segment)){
    amt835Handler(parser, segment);
  }else if(isQTY(segment)){
    qty835Handler(parser, segment);
  }else if(isSVC(segment)){
    svc835Handler(parser, segment);
  }else if(isPLB(segment)){
    plb835Handler(parser, segment);
  }else if(isRDM(segment)){
    rdm835Handler(parser, segment);
  }else if(isBPR(segment)){
    bpr835Handler(parser, segment);
  }else if(isTRN(segment)){
    trn835Handler(parser, segment);
  }else if(isCUR(segment)){
    cur835Handler(parser, segment);
  }else if(isREF(segment)){
    ref835Handler(parser, segment);
  }else if(isDTM(segment)){
    dtm835Handler(parser, segment);
  }else if(isPER(segment)){
    per835Handler(parser, segment);
  }else if(isGS(segment)){
    gs835Handler(parser, segment);
  }else if(isGE(segment)){
    ge835Handler(parser, segment);
  }else if(isST(segment)){
    st835Handler(parser, segment);
  }else if(isSE(segment)){
    se835Handler(parser, segment);
  }else if(isN1(segment)){
    n1835Handler(parser, segment);
  }else if(isN4(segment)){
    n4835Handler(parser, segment);
  }else if(isN3(segment)){
    n3835Handler(parser, segment);
  }else if(isLX(segment)){
    lx835Handler(parser, segment);
  }else if(isLQ(segment)){
    lq835Handler(parser, segment);
  }else{
    parserFail(parser->super, UNKNOWN_ERROR);
  }
}

static void default835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->loop, segment);
}

static void isa835Handler(parser835_t *parser, segment_t *segment){
  if(NULL != parser->interchange){
    parserFail(parser->super, ISA_SEGMENT_NOT_DETECTED_FIRST);
  }else if(NULL != parser->loop || parser->loop != parser->interchange){
    parserFail(parser->super, INVALID_ISA_SEGMENT);
  }else if(!elementCountIn(segment, 16,16)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT);
  }else if(strlen(segment->lastProperty->value) != 1){
    parserFail(parser->super, INVALID_COMPONENT_SEPARATOR);
  }else{
    parser->interchange = segment;
    parser->loop = segment;
    parser->super->componentSeparator[0] = parser->interchange->lastProperty->value[0];
    parser->super->componentSeparator[1] = '\0';
  }
}

static void iea835Handler(parser835_t *parser, segment_t *segment){
  if(!elementCountIn(segment,2,2)){
    if(parser->loop == parser->functional && isGE(parser->trailer)){
      addChildSegment(parser->interchange, segment);
      parser->loop = parser->interchange;
      parser->trailer = segment;
    }else{
      parserFail(parser->super, INVALID_IEA_SEGMENT);
    }
  }else{
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT);
  }
}

static void ts3835Handler(parser835_t *parser, segment_t *segment){
  if(!isLX(parser->loop)){
    parserFail(parser->super, INVALID_TS3_SEGMENT);
  }else if(!elementCountIn(segment,1,19)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_TS3_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void ts2835Handler(parser835_t *parser, segment_t *segment){
  if(!isLX(parser->loop)){
    parserFail(parser->super, INVALID_TS2_SEGMENT);
  }else if(!elementCountIn(segment,1,24)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_TS2_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void clp835Handler(parser835_t *parser, segment_t *segment){
  if(!isLX(parser->loop) && !isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_CLP_SEGMENT);
  }else if(!elementCountIn(segment,3,14)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT);
  }else{
    parser->service = NULL;
    addChildSegment(parser->header, segment);
    parser->claim = segment;
    parser->loop = segment;
  }
}

static void nm1835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop)){
    parserFail(parser->super, INVALID_NM1_SEGMENT);
  }else if(!elementCountIn(segment,5,11)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void mia835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop)){
    parserFail(parser->super, INVALID_MIA_SEGMENT);
  }else if(!elementCountIn(segment,1,24)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_MIA_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void moa835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop)){
    parserFail(parser->super, INVALID_MOA_SEGMENT);
  }else if(!elementCountIn(segment,1,9)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_MOA_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void amt835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop != parser->service && parser->loop == parser->claim){
    parserFail(parser->super, INVALID_AMT_SEGMENT);
  }else if(!elementCountIn(segment,2,3)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void cas835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_CAS_SEGMENT);
  }else if(!elementCountIn(segment,3,19)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void qty835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop) && !isSVC(parser->loop)){
    parserFail(parser->super, INVALID_QTY_SEGMENT);
  }else if(!elementCountIn(segment,2,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_QTY_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void svc835Handler(parser835_t *parser, segment_t *segment){
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

static void plb835Handler(parser835_t *parser, segment_t *segment){
  if(!isCLP(parser->loop) && !isSVC(parser->loop) && !isST(parser->loop) && parser->loop != parser->payee){
    parserFail(parser->super, INVALID_PLB_SEGMENT);
  }else if(!elementCountIn(segment,4,14)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_PLB_SEGMENT);
  }else{
    parser->loop = parser->transaction;
    addChildSegment(parser->loop, segment);
  }
}

static void rdm835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop != parser->payee || NULL == parser->payee){
    parserFail(parser->super, INVALID_RDM_SEGMENT);
  }else if(!elementCountIn(segment,1,3)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_RDM_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void bpr835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop)){
    parserFail(parser->super, INVALID_BPR_SEGMENT);
  }else if(!elementCountIn(segment,16,21)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void trn835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop)){
    parserFail(parser->super, INVALID_TRN_SEGMENT);
  }else if(!elementCountIn(segment,3,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void cur835Handler(parser835_t *parser, segment_t *segment){
  if(!isST(parser->loop)){
    parserFail(parser->super, INVALID_CUR_SEGMENT);
  }else if(!elementCountIn(segment,2,21)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_CUR_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void ref835Handler(parser835_t *parser, segment_t *segment){
  if(!elementCountIn(segment,1,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void dtm835Handler(parser835_t *parser, segment_t *segment){
  if(!elementCountIn(segment,1,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
  }
}

static void per835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop != parser->payer){
    parserFail(parser->super, INVALID_PER_SEGMENT);
  }else if(!elementCountIn(segment,1,9)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static void gs835Handler(parser835_t *parser, segment_t *segment){
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

static void ge835Handler(parser835_t *parser, segment_t *segment){
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

static void st835Handler(parser835_t *parser, segment_t *segment){
  if(!isGS(parser->loop) && !isSE(parser->trailer)){
    parserFail(parser->super, INVALID_SE_SEGMENT);
  }else if(!elementCountIn(segment, 2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
    parser->transaction = segment;
    parser->loop = segment;
  }
}

static void se835Handler(parser835_t *parser, segment_t *segment){
  if(NULL != parser->trailer || !isSE(parser->trailer)){
    parserFail(parser->super, INVALID_SE_SEGMENT);
  }else if(!elementCountIn(segment,2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT);
  }else{
    parser->loop = parser->transaction;
    addChildSegment(parser->loop, segment);
    parser->trailer = segment;
  }
}

static void n1835Handler(parser835_t *parser, segment_t *segment){
  if(elementCountIn(segment,2,6)){
    if(isST(parser->loop)){
      addChildSegment(parser->loop, segment);
      parser->payer = segment;
      parser->loop = segment;
    }else if(parser->loop == parser->payer){
      addChildSegment(parser->loop, segment);
      parser->payee = segment;
      parser->loop = segment;
    }else{
      parserFail(parser->super, INVALID_N1_SEGMENT);
    }
  }else{
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT);
  }
}

static void n3835Handler(parser835_t *parser, segment_t *segment){
  if(!isN1(parser->loop)){
    parserFail(parser->super, INVALID_N3_SEGMENT);
  }else if(!elementCountIn(segment,1,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static void n4835Handler(parser835_t *parser, segment_t *segment){
  if(!isN1(parser->loop)){
    parserFail(parser->super, INVALID_N4_SEGMENT);
  }else if(!elementCountIn(segment,1,3)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static void lx835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop != parser->payee || NULL == parser->payee){
    parserFail(parser->super, INVALID_LX_SEGMENT);
  }else if(!elementCountIn(segment,1,1)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT);
  }else{
    addChildSegment(parser->loop, segment);
    parser->header = segment;
    parser->loop = segment;
  }
}

static void lq835Handler(parser835_t *parser, segment_t *segment){
  if(!isSVC(parser->loop)){
    parserFail(parser->super, INVALID_LQ_SEGMENT);
  }else if(!elementCountIn(segment,2,2)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT);
  }else {
    addChildSegment(parser->loop, segment);
  }
}

static void parser835Initialization(parser835_t *parser){
  parser->interchange = NULL;
  parser->loop = NULL;
  parser->functional = NULL;
  parser->transaction = NULL;
  parser->payer = NULL;
  parser->payee = NULL;
  parser->header = NULL;
  parser->claim = NULL;
}

static void validate835Parser(parser835_t *parser){
  if(missingSegment(parser, ISA_SEGMENT)){
    parserFail(parser->super, MISSING_ISA_SEGMENT);
  }else if(missingSegment(parser, GS_SEGMENT)){
    parserFail(parser->super, MISSING_GS_SEGMENT);
  }else if(missingSegment(parser, ST_SEGMENT)){
    parserFail(parser->super, MISSING_ST_SEGMENT);
  }else if(missingSegment(parser, N1_SEGMENT)){
    parserFail(parser->super, MISSING_N1_SEGMENT);
  }else if(missingSegment(parser, SE_SEGMENT)){
    parserFail(parser->super, MISSING_SE_SEGMENT);
  }else if(missingSegment(parser, GE_SEGMENT)){
    parserFail(parser->super, MISSING_GE_SEGMENT);
  }else if(missingSegment(parser, IEA_SEGMENT)){
    parserFail(parser->super, MISSING_IEA_SEGMENT);
  }
}

static void parser835Cleanup(parser835_t *parser){
  parser->interchange = rewindLoop(parser->interchange);
  parser->super->root = parser->interchange;
  if(!parser->super->failure){
    build835Indexes(parser);
  }
  validate835Parser(parser);
  parser->super->finished = true;
}

static void parser835Free(parser835_t *parser){
  if(NULL != parser){
    free(parser);
  }
}



