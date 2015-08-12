//
//  edi_835_parser.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_835_parser.h"


void parse835(parser835_t *parser, char *ediFile){
  parser835Initialization(parser);
  char *saveptr;
  parser->str = strtok_r(ediFile, SEGMENT_SEPARATOR, &saveptr);
  while(NULL != parser->super->str && !parser->super.finished && !parser->super->failure){
    parseSegment(&parser->super);
    attach835Segment(parser, segment);
    parser->super.str = strtok_r(NULL, SEGMENT_SEPARATOR, &saveptr);
  }
  parser835Cleanup(parser);
  validate835Parser(parser);
}

void attach835Segment(parser835_t *parser, segment_t *segment){
  if(isISA(segment->name)){
    isa835Handler(parser, segment);
  }else if(NULL == parser->loop || NULL == parser->interchange){
    parse835Fail(parser, ISA_SEGMENT_NOT_DETECTED_FIRST);
  }else if(isIEA(segment->name)){
    iea835Handler(parser, segment);
  }else if(isGS(segment->name)){
    gs835Handler(parser, segment);
  }else if(NULL == parser->functional){
    parse835Fail(parser, MISSING_GS_SEGMENT);
  }else if(parser->functional->elements != 8){
    parse835Fail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_GS);
  }else if(isGE(segment->name)){
    ge835Handler(parser, segment);
  }else if(isST(segment->name)){
    st835Handler(parser, segment);
  }else if(parser->transaction->elements != 2){
    parse835Fail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_ST);
  }else if(NULL == parser->transaction){
    parse835Fail(parser, MISSING_ST_SEGMENT);
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
  if(NULL != segment) segment->depth = parser->loop->depth;
}

void default835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->loop, segment);
}

void isa835Handler(parser835_t *parser, segment_t *segment){
  if(NULL == parser->interchange){
    parser->interchange = segment;
    parser->loop = segment;
    parser->super.depth = 1;
  }else{
    parse835Fail(parser, MORE_THAN_ONE_ISA_SEGMENT_FOUND);
  }

  if(parser->interchange->elements != 16){
    parse835Fail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_ISA);
  }else{
    if(strlen(parser->interchange->lastProperty->value) != 1){
      parse835Fail(parser, INVALID_COMPONENT_SEPARATOR);
    }else{
      parser->componentSeparator[0] = parser->interchange->lastProperty->value[0];
      parser->componentSeparator[1] = '\0';
    }
  }
}

void gs835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->interchange || (parser->loop == parser->functional && NULL != parser->trailer && isGE(parser->trailer->name))){
    addChildSegment(parser->interchange, segment);
    parser->functional = segment;
    parser->loop = segment;
    parser->super.depth = 2;
  }else{
   parse835Fail(parser, INVALID_GS_SEGMENT);
  }
}

void st835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->functional || (parser->loop == parser->transaction && NULL != parser->trailer && isSE(parser->trailer->name))){
    addChildSegment(parser->functional, segment);
    parser->transaction = segment;
    parser->loop = segment;
    parser->super.depth = 3;
  }else{
   parse835Fail(parser, INVALID_ST_SEGMENT);
  }
}

void n1835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction){
    addChildSegment(parser->functional, segment);
    parser->payer = segment;
    parser->loop = segment;
    parser->super.depth = 4;
  }else if(parser->loop == parser->payer){
    addChildSegment(parser->payer, segment);
    parser->payee = segment;
    parser->loop = segment;
    parser->super.depth = 5;
  }else{
    parse835Fail(parser, INVALID_N1_SEGMENT);
  }
}

void lx835Handler(parser835_t *parser, segment_t *segment){
  if(NULL == parser->payer || NULL == parser->payee){
    parse835Fail(parser, MISSING_PAYER_LOOP);
  }else if(parser->loop == parser->payee){
    addChildSegment(parser->payee, segment);
    parser->header = segment;
    parser->loop = segment;
    parser->super.depth = 6;
  }
  else{
   parse835Fail(parser, INVALID_LX_SEGMENT);
  }
}

void clp835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->service || parser->loop == parser->claim || parser->loop == parser->header){
    parser->service = NULL;
    addChildSegment(parser->header, segment);
    parser->claim = segment;
    parser->loop = segment;
    parser->super.depth = 7;
  }else{
    parse835Fail(parser, INVALID_CLP_SEGMENT);
  }
}

void svc835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->claim || parser->loop == parser->service){
    addChildSegment(parser->claim, segment);
    parser->service = segment;
    parser->loop = segment;
    parser->super.depth = 8;
  }else{
    parse835Fail(parser, INVALID_SVC_SEGMENT);
  }
}

void plb835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->header, segment);
  parser->claim = segment;
  parser->loop = segment;
  parser->super.depth = 6;
}

void se835Handler(parser835_t *parser, segment_t *segment){
  addChildSegment(parser->transaction, segment);
  parser->loop = parser->transaction;
  parser->trailer = segment;
  parser->super.depth = 3
}

void ge835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction && isSE(parser->transaction->lastSegment->name)){
    addChildSegment(parser->functional, segment);
    parser->loop = parser->functional;
    parser->trailer = segment;
    parser->super.depth = 2
  }else{
    parse835Fail(parser, INVALID_GE_SEGMENT);
  }
}

void iea835Handler(parser835_t *parser, segment_t *segment){
  if(parser->loop == parser->functional && isGE(parser->functional->lastSegment->name)){
    addChildSegment(parser->interchange, segment);
    parser->loop = parser->interchange;
    parser->trailer = segment;
    parser->super.depth = 1
  }else{
    parse835Fail(parser, INVALID_IEA_SEGMENT);
  }
}

void validate835Parser(parser835_t *parser){
  if(!parser->finished){
    if(!isSE(parser->transaction->name)){
      parse835Fail(parser, MISSING_SE_SEGMENT);
    }else if(parser->transaction->elements != 2){
      parse835Fail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_SE);
    }

    if(!isGE(parser->functional->name)){
      parse835Fail(parser, MISSING_GE_SEGMENT);
    }else if(parser->functional->elements != 2){
      parse835Fail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_GE);
    }

    if(!isIEA(parser->interchange->name)){
      parse835Fail(parser, MISSING_IEA_SEGMENT);
    }else if(parser->interchange->elements != 2){
      parse835Fail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_IEA);
    }
    parser->finished = true;
  }
}

void parse835Fail(parser835_t *parser, short error){
  parser->failure = true;
  parser->finished = true;
  
  if(parser->errorCount < MAX_ERROR_SIZE){
    parser->errors[parser->errorCount] = error;
    parser->errorCount++;
  }
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
  parser->root = NULL;
  parser->super.failure = false;
  parser->super.finished = false;
  parser->super.errorCount = 0;
  parser->super.depth = 0;
  parser->super.segmentCount = 0;
  parser->super.propertyCount = 0;
  parser->super.componentSeparator[0] = '\0';
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
    free(parser);
  }
}


