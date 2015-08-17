//
//  edi_parsing_835.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"

void parse835(parser835_t *parser, char *ediFile){
  parser835Initialization(parser);
  segment_t *segment;
  char *saveptr;
  parser->super->str = strtok_r(ediFile, SEGMENT_SEPARATOR, &saveptr);
  while(NULL != parser->super->str && !parser->super->finished && !parser->super->failure){
    segment = parseSegment(parser->super);
    attach835Segment(parser, segment);
    parser->super->str = strtok_r(NULL, SEGMENT_SEPARATOR, &saveptr);
  }
  parser835Cleanup(parser);
  validate835Parser(parser);
}

void attach835Segment(parser835_t *parser, segment_t *segment){
  if(isISA(segment->name)){
    isa835Handler(parser, segment);
  }else if(NULL == parser->loop || NULL == parser->interchange){
    parserFail(parser->super, ISA_SEGMENT_NOT_DETECTED_FIRST);
  }else if(isIEA(segment->name)){
    iea835Handler(parser, segment);
  }else if(isGS(segment->name)){
    gs835Handler(parser, segment);
  }else if(NULL == parser->functional){
    parserFail(parser->super, MISSING_GS_SEGMENT);
  }else if(parser->functional->elements != 8){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_GS);
  }else if(isGE(segment->name)){
    ge835Handler(parser, segment);
  }else if(isST(segment->name)){
    st835Handler(parser, segment);
  }else if(parser->transaction->elements != 2){
    parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_ST);
  }else if(NULL == parser->transaction){
    parserFail(parser->super, MISSING_ST_SEGMENT);
  }else if(isSE(segment->name)){
    se835Handler(parser, segment);
  }else if(isN1(segment->name)){
    n1835Handler(parser, segment);
  }else if(isLX(segment->name)){
    lx835Handler(parser, segment);
  }else if(isCLP(segment->name)){
    clp835Handler(parser, segment);
  }else if(isSVC(segment->name)){
    svc835Handler(parser, segment);
  }else if(isPLB(segment->name)){
    plb835Handler(parser, segment);
  }else{
    default835Handler(parser, segment);
  }
}

void default835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->loop, segment);
}

void isa835Handler(parser835_t *parser, segment_t *segment){
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

void gs835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->interchange || (parser->loop == parser->functional && NULL != parser->trailer && isGE(parser->trailer->name))){
    addChildSegment(parser->interchange, segment);
    parser->functional = segment;
    parser->loop = segment;
  }else{
   parserFail(parser->super, INVALID_GS_SEGMENT);
  }
}

void st835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->functional || (parser->loop == parser->transaction && NULL != parser->trailer && isSE(parser->trailer->name))){
    addChildSegment(parser->functional, segment);
    parser->transaction = segment;
    parser->loop = segment;
  }else{
   parserFail(parser->super, INVALID_ST_SEGMENT);
  }
}

void n1835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction){
    addChildSegment(parser->functional, segment);
    parser->payer = segment;
    parser->loop = segment;
  }else if(parser->loop == parser->payer){
    addChildSegment(parser->payer, segment);
    parser->payee = segment;
    parser->loop = segment;
  }else{
    parserFail(parser->super, INVALID_N1_SEGMENT);
  }
}

void lx835Handler(parser835_t *parser, segment_t *segment){
  if(NULL == parser->payer || NULL == parser->payee){
    parserFail(parser->super, MISSING_PAYER_LOOP);
  }else if(parser->loop == parser->payee){
    addChildSegment(parser->payee, segment);
    parser->header = segment;
    parser->loop = segment;
  }
  else{
   parserFail(parser->super, INVALID_LX_SEGMENT);
  }
}

void clp835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->service || parser->loop == parser->claim || parser->loop == parser->header){
    parser->service = NULL;
    addChildSegment(parser->header, segment);
    parser->claim = segment;
    parser->loop = segment;
  }else{
    parserFail(parser->super, INVALID_CLP_SEGMENT);
  }
}

void svc835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->claim || parser->loop == parser->service){
    addChildSegment(parser->claim, segment);
    parser->service = segment;
    parser->loop = segment;
  }else{
    parserFail(parser->super, INVALID_SVC_SEGMENT);
  }
}

void plb835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->header, segment);
  parser->claim = segment;
  parser->loop = segment;
}

void se835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->transaction, segment);
  parser->loop = parser->transaction;
  parser->trailer = segment;
}

void ge835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction && isSE(parser->transaction->lastSegment->name)){
    addChildSegment(parser->functional, segment);
    parser->loop = parser->functional;
    parser->trailer = segment;
  }else{
    parserFail(parser->super, INVALID_GE_SEGMENT);
  }
}

void iea835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->functional && isGE(parser->functional->lastSegment->name)){
    addChildSegment(parser->interchange, segment);
    parser->loop = parser->interchange;
    parser->trailer = segment;
  }else{
    parserFail(parser->super, INVALID_IEA_SEGMENT);
  }
}

void validate835Parser(parser835_t *parser){
  if(!parser->super->finished && !parser->super->failure){
    if(!isSE(parser->transaction->lastSegment->name)){
      parserFail(parser->super, MISSING_SE_SEGMENT);
    }else if(parser->transaction->lastSegment->elements != 2){
      parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_SE);
    }

    if(!isGE(parser->functional->lastSegment->name)){
      parserFail(parser->super, MISSING_GE_SEGMENT);
    }else if(parser->functional->lastSegment->elements != 2){
      parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_GE);
    }

    if(!isIEA(parser->interchange->lastSegment->name)){
      parserFail(parser->super, MISSING_IEA_SEGMENT);
    }else if(parser->interchange->lastSegment->elements != 2){
      parserFail(parser->super, WRONG_NUMBER_OF_ELEMENTS_FOR_IEA);
    }

    if(!parser->super->failure){
      build835Indexes(parser);
    }
  }
  parser->super->finished = true;
}

void build835Indexes(parser835_t *parser){
  rewind835Parser(parser);
  buildIndexes(parser->super, parser->interchange);
}

void parser835Initialization(parser835_t *parser){
  parser->interchange = NULL;
  parser->loop = NULL;
  parser->functional = NULL;
  parser->transaction = NULL;
  parser->payer = NULL;
  parser->payee = NULL;
  parser->header = NULL;
  parser->claim = NULL;
  parserInitialization(parser->super);
}

void rewind835Parser(parser835_t *parser){
  parser->interchange = rewindLoop(parser->interchange);
  parser->functional = rewindLoop(parser->functional);
  parser->transaction = rewindLoop(parser->transaction);
  parser->payer = rewindLoop(parser->payer);
  parser->payee = rewindLoop(parser->payee);
  parser->header = rewindLoop(parser->header);
  parser->claim = rewindLoop(parser->claim);
  parser->loop = parser->interchange;
}

void parser835Cleanup(parser835_t *parser){

}

void parser835Free(parser835_t *parser){
  if(NULL != parser){
    rewind835Parser(parser);
    loopFree(parser->claim);
    loopFree(parser->header);
    loopFree(parser->payee);
    loopFree(parser->payer);
    loopFree(parser->transaction);
    loopFree(parser->functional);
    loopFree(parser->interchange);
    parserFree(parser->super);
    free(parser);
  }
}


