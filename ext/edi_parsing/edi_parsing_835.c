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
static void validate835Parser(parser835_t *parser);
static void parser835Free(parser835_t *parser);
static void parser835Initialization(parser835_t *parser);
static bool isa835Handler(parser835_t *parser, segment_t *segment);
static bool gs835Handler(parser835_t *parser, segment_t *segment);
static bool st835Handler(parser835_t *parser, segment_t *segment);
static bool trn835Handler(parser835_t *parser, segment_t *segment);
static bool n1835Handler(parser835_t *parser, segment_t *segment);
static bool lx835Handler(parser835_t *parser, segment_t *segment);
static bool clp835Handler(parser835_t *parser, segment_t *segment);
static bool svc835Handler(parser835_t *parser, segment_t *segment);
static bool plb835Handler(parser835_t *parser, segment_t *segment);
static bool se835Handler(parser835_t *parser, segment_t *segment);
static bool ge835Handler(parser835_t *parser, segment_t *segment);
static bool iea835Handler(parser835_t *parser, segment_t *segment);
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
  if(isISA(segment->name)){
    parser->super->failure = isa835Handler(parser, segment);
  }else if(NULL == parser->loop || NULL == parser->interchange){
    parserFail(parser->super, ISA_SEGMENT_NOT_DETECTED_FIRST);
  }else if(isIEA(segment->name)){
    parser->super->failure = iea835Handler(parser, segment);
  }else if(isGS(segment->name)){
    parser->super->failure = gs835Handler(parser, segment);
  }else if(NULL == parser->functional){
    parserFail(parser->super, MISSING_GS_SEGMENT);
  }else if(isGE(segment->name)){
    parser->super->failure = ge835Handler(parser, segment);
  }else if(isST(segment->name)){
    parser->super->failure = st835Handler(parser, segment);
  }else if(NULL == parser->transaction){
    parserFail(parser->super, MISSING_ST_SEGMENT);
  }else if(isTRN(segment->name)){
    parser->super->failure = trn835Handler(parser, segment);
  }else if(isSE(segment->name)){
    parser->super->failure = se835Handler(parser, segment);
  }else if(isN1(segment->name)){
    parser->super->failure = n1835Handler(parser, segment);
  }else if(isLX(segment->name)){
    parser->super->failure = lx835Handler(parser, segment);
  }else if(isCLP(segment->name)){
    parser->super->failure = clp835Handler(parser, segment);
  }else if(isSVC(segment->name)){
    parser->super->failure = svc835Handler(parser, segment);
  }else if(isPLB(segment->name)){
    parser->super->failure = plb835Handler(parser, segment);
  }else{
    default835Handler(parser, segment);
  }
}

static void default835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->loop, segment);
}

static bool isa835Handler(parser835_t *parser, segment_t *segment){
  if(NULL == parser->interchange){
    parser->interchange = segment;
    parser->loop = segment;
  }else{
    parserFail(parser->super, MORE_THAN_ONE_ISA_SEGMENT_FOUND);
  }

  if(parser->interchange->elements != 16){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_ISA);
  }else{
    if(strlen(parser->interchange->lastProperty->value) != 1){
      parserFail(parser->super, INVALID_COMPONENT_SEPARATOR);
    }else{
      parser->super->componentSeparator[0] = parser->interchange->lastProperty->value[0];
      parser->super->componentSeparator[1] = '\0';
    }
  }
}

static bool gs835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->interchange || (parser->loop == parser->functional && NULL != parser->trailer && isGE(parser->trailer->name))){
    addChildSegment(parser->interchange, segment);
    parser->functional = segment;
    parser->loop = segment;
  }else{
   parserFail(parser->super, INVALID_GS_SEGMENT);
  }

  if(segment->elements != 8){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_GS);
  }
}

static bool st835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->functional || (parser->loop == parser->transaction && NULL != parser->trailer && isSE(parser->trailer->name))){
    addChildSegment(parser->functional, segment);
    parser->transaction = segment;
    parser->loop = segment;
  }else{
   parserFail(parser->super, INVALID_ST_SEGMENT);
  }

  if(!elementCountIn(segment,2,3)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_ST);
  }
}

static bool bpr835Handler(parser835_t *parser, segment_t *segment){
  if(isST(parser->loop)){
    addChildSegment(parser->loop, segment);
  }else{
    parserFail(parser->super, INVALID_BPR_SEGMENT);
  }

  if(!elementCountIn(segment,16,21)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_BPR);
  }
}

static bool trn835Handler(parser835_t *parser, segment_t *segment){
  if(isST(parser->loop)){
    addChildSegment(parser->loop, segment);
  }else{
    parserFail(parser->super, INVALID_TRN_SEGMENT);
  }

  if(!elementCountIn(segment,3,4)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_TRN);
  }
}

static bool cur835Handler(parser835_t *parser, segment_t *segment){
  if(isST(parser->loop)){
    addChildSegment(parser->loop, segment);
  }else{
    parserFail(parser->super, INVALID_CUR_SEGMENT);
  }

  if(!elementCountIn(segment,2,21)){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_CUR);
  }
}

static bool n1835Handler(parser835_t *parser, segment_t *segment){
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
}

static bool lx835Handler(parser835_t *parser, segment_t *segment){
  if(NULL == parser->payer || NULL == parser->payee){
    parserFail(parser->super, MISSING_PAYER_LOOP);
  }else if(parser->loop == parser->payee){
    addChildSegment(parser->loop, segment);
    parser->header = segment;
    parser->loop = segment;
  }else{
   parserFail(parser->super, INVALID_LX_SEGMENT);
  }
}

static bool clp835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->service || parser->loop == parser->claim || parser->loop == parser->header){
    parser->service = NULL;
    addChildSegment(parser->header, segment);
    parser->claim = segment;
    parser->loop = segment;
  }else{
    parserFail(parser->super, INVALID_CLP_SEGMENT);
  }
}

static bool svc835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->claim || parser->loop == parser->service){
    addChildSegment(parser->claim, segment);
    parser->service = segment;
    parser->loop = segment;
  }else{
    parserFail(parser->super, INVALID_SVC_SEGMENT);
  }
}

static bool plb835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->header, segment);
  parser->claim = segment;
  parser->loop = segment;
}

static bool se835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->transaction, segment);
  parser->loop = parser->transaction;
  parser->trailer = segment;
}

static bool ge835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction && isSE(parser->transaction->lastSegment->name)){
    addChildSegment(parser->functional, segment);
    parser->loop = parser->functional;
    parser->trailer = segment;
  }else{
    parserFail(parser->super, INVALID_GE_SEGMENT);
  }
}

static bool iea835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->functional && isGE(parser->functional->lastSegment->name)){
    addChildSegment(parser->interchange, segment);
    parser->loop = parser->interchange;
    parser->trailer = segment;
  }else{
    parserFail(parser->super, INVALID_IEA_SEGMENT);
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

static void parser835Cleanup(parser835_t *parser){
  parser->interchange = rewindLoop(parser->interchange);
  parser->super->root = parser->interchange;
  if(!parser->super->failure){
    build835Indexes(parser);
  }
  parser->super->finished = true;
}

static void parser835Free(parser835_t *parser){
  if(NULL != parser){
    free(parser);
  }
}



