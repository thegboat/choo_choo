//
//  edi_835_parser.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_835_parser.h"

void parse835(parser_t *parser, char *ediFile){
  parserInitialization(parser);
  char *saveptr;
  parser->str = strtok_r(ediFile, SEGMENT_SEPARATOR, &saveptr);
  while(NULL != parser->str && !parser->finished && !parser->failure){
    parse835Segment(parser);
    parser->str = strtok_r(NULL, SEGMENT_SEPARATOR, &saveptr);
    parser->segmentCount++;
  }
  parserCleanup(parser);
  validateParser(parser);
}

void parse835Segment(parser_t *parser){
  segment_t *segment = calloc(1,sizeof(segment_t));
  char *tok;
  char *saveptr;
  short cnt = 0;
  tok = strtok_r(parser->str, ELEMENT_SEPARATOR, &saveptr);
  segmentInitializer(segment, tok);
  tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  while (tok != NULL)
  {
    cnt++;
    if(strlen(parser->componentSeparator) == 1 && NULL != strstr(tok, parser->componentSeparator)){
      parse835Element(parser, tok, segment, cnt);
    }else{
      buildProperty(segment, tok, cnt, 0);
      indexProperty(parser, segment->lastProperty);
    }
    tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  }
  segment->elements = cnt;
  attachSegment(parser, segment);
  indexSegment(parser, segment);
}

void parse835Element(parser_t *parser, char *str, segment_t *segment, short seg_cnt){
  char *tok;
  char *saveptr;
  short cnt = 0;
  tok = strtok_r(str, parser->componentSeparator, &saveptr);
  while (tok != NULL)
  {
    cnt++;
    buildProperty(segment, tok, seg_cnt, cnt);
    indexProperty(parser, segment->lastProperty);
    tok = strtok_r(NULL, parser->componentSeparator, &saveptr);
  }
}

void attachSegment(parser_t *parser, segment_t *segment){
  if(isISA(segment->name)){
    isaHandler(parser, segment);
  }else if(NULL == parser->loop || NULL == parser->interchange){
    parseFail(parser, ISA_SEGMENT_NOT_DETECTED_FIRST);
  }else if(isIEA(segment->name)){
    ieaHandler(parser, segment);
  }else if(isGS(segment->name)){
    gsHandler(parser, segment);
  }else if(NULL == parser->functional){
    parseFail(parser, MISSING_GS_SEGMENT);
  }else if(parser->functional->elements != 8){
    parseFail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_GS);
  }else if(isGE(segment->name)){
    geHandler(parser, segment);
  }else if(isST(segment->name)){
    stHandler(parser, segment);
  }else if(parser->transaction->elements != 2){
    parseFail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_ST);
  }else if(NULL == parser->transaction){
    parseFail(parser, MISSING_ST_SEGMENT);
  }else if(isSE(segment->name)){
    seHandler(parser, segment);
  }else if(isN1(segment->name)){
    n1Handler(parser, segment);
  }else if(isLX(segment->name)){
    lxHandler(parser, segment);
  }else if(isCLP(segment->name)){
    clpHandler(parser, segment);
  }else if(isSVC(segment->name)){
    svcHandler(parser, segment);
  }else if(isPLB(segment->name)){
    plbHandler(parser, segment);
  }else{
    defaultHandler(parser, segment);
  }
}

void defaultHandler(parser_t *parser, segment_t *segment){
  addChildSegment(parser->loop, segment);
}

void isaHandler(parser_t *parser, segment_t *segment){
  if(NULL == parser->interchange){
    parser->interchange = segment;
    parser->loop = segment;
  }else{
    parseFail(parser, MORE_THAN_ONE_ISA_SEGMENT_FOUND);
  }

  if(parser->interchange->elements != 16){
    parseFail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_ISA);
  }else{
    if(strlen(parser->interchange->lastProperty->value) != 1){
      parseFail(parser, INVALID_COMPONENT_SEPARATOR);
    }else{
      parser->componentSeparator[0] = parser->interchange->lastProperty->value[0];
      parser->componentSeparator[1] = '\0';
    }
  }
}

void gsHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->interchange || (parser->loop == parser->functional && NULL != parser->trailer && isGE(parser->trailer->name))){
    addChildSegment(parser->interchange, segment);
    parser->functional = segment;
    parser->loop = segment;
  }else{
   parseFail(parser, INVALID_GS_SEGMENT);
  }
}

void stHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->functional || (parser->loop == parser->transaction && NULL != parser->trailer && isSE(parser->trailer->name))){
    addChildSegment(parser->functional, segment);
    parser->transaction = segment;
    parser->loop = segment;
  }else{
   parseFail(parser, INVALID_ST_SEGMENT);
  }
}

void n1Handler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction){
    addChildSegment(parser->functional, segment);
    parser->payer = segment;
    parser->loop = segment;
  }else if(parser->loop == parser->payer){
    addChildSegment(parser->payer, segment);
    parser->payee = segment;
    parser->loop = segment;
  }else{
    parseFail(parser, INVALID_N1_SEGMENT);
  }
}

void lxHandler(parser_t *parser, segment_t *segment){
  if(NULL == parser->payer || NULL == parser->payee){
    parseFail(parser, MISSING_PAYER_LOOP);
  }else if(parser->loop == parser->payee){
    addChildSegment(parser->payee, segment);
    parser->header = segment;
    parser->loop = segment;
  }
  else{
   parseFail(parser, INVALID_LX_SEGMENT);
  }
}

void clpHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->service || parser->loop == parser->claim || parser->loop == parser->header){
    parser->service = NULL;
    addChildSegment(parser->header, segment);
    parser->claim = segment;
    parser->loop = segment;
  }else{
    parseFail(parser, INVALID_CLP_SEGMENT);
  }
}

void svcHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->claim || parser->loop == parser->service){
    addChildSegment(parser->claim, segment);
    parser->service = segment;
    parser->loop = segment;
  }else{
    parseFail(parser, INVALID_SVC_SEGMENT);
  }
}

void plbHandler(parser_t *parser, segment_t *segment){
  addChildSegment(parser->header, segment);
  parser->claim = segment;
  parser->loop = segment;
}

void seHandler(parser_t *parser, segment_t *segment){
  addChildSegment(parser->transaction, segment);
  parser->loop = parser->transaction;
  parser->trailer = segment;
}

void geHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction && isSE(parser->transaction->lastSegment->name)){
    addChildSegment(parser->functional, segment);
    parser->loop = parser->functional;
    parser->trailer = segment;
  }else{
    parseFail(parser, INVALID_GE_SEGMENT);
  }
}

void ieaHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->functional && isGE(parser->functional->lastSegment->name)){
    addChildSegment(parser->interchange, segment);
    parser->loop = parser->interchange;
    parser->trailer = segment;
  }else{
    parseFail(parser, INVALID_IEA_SEGMENT);
  }
}

void validateParser(parser_t *parser){
  if(!parser->finished){
    if(!isSE(parser->transaction->name)){
      parseFail(parser, MISSING_SE_SEGMENT);
    }else if(parser->transaction->elements != 2){
      parseFail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_SE);
    }

    if(!isGE(parser->functional->name)){
      parseFail(parser, MISSING_GE_SEGMENT);
    }else if(parser->functional->elements != 2){
      parseFail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_GE);
    }

    if(!isIEA(parser->interchange->name)){
      parseFail(parser, MISSING_IEA_SEGMENT);
    }else if(parser->interchange->elements != 2){
      parseFail(parser, WRONG_NUMBER_OF_ELEMENTS_FOR_IEA);
    }
    parser->finished = true;
  }
}

void indexProperty(parser_t *parser, property_t *property){
  if(PROPERTY_INDEX_RESIZE % parser->propertySeq == 0){
    parser->propertyPkey = realloc(parser->propertyPkey, sizeof(property_t**)*(parser->propertySeq+ PROPERTY_INDEX_RESIZE));
  }
  parser->propertyPkey[parser->propertySeq] = property;
  property->pkey = parser->propertySeq;
  parser->propertySeq++;
}

void indexSegment(parser_t *parser, segment_t *segment){
  if(SEGMENT_INDEX_RESIZE % parser->segmentSeq == 0){
    parser->segmentPkey = realloc(parser->segmentPkey, sizeof(segment_t**)*(parser->segmentSeq+ SEGMENT_INDEX_RESIZE));
  }
  parser->segmentPkey[parser->segmentSeq] = segment;
  segment->pkey = parser->segmentSeq;
  parser->segmentSeq++;
}

void parseFail(parser_t *parser, short error){
  parser->failure = true;
  parser->finished = true;
  
  if(parser->errorCount < MAX_ERROR_SIZE){
    parser->errors[parser->errorCount] = error;
    parser->errorCount++;
  }
}

void parserInitialization(parser_t *parser){
  parser->failure = false;
  parser->finished = false;
  parser->interchange = NULL;
  parser->loop = NULL;
  parser->functional = NULL;
  parser->transaction = NULL;
  parser->payer = NULL;
  parser->payee = NULL;
  parser->header = NULL;
  parser->claim = NULL;
  parser->errorCount = 0;
  parser->segmentCount = 0;
  parser->componentSeparator[0] = '\0';
  parser->segmentSeq = 0;
  parser->propertySeq = 0;
  parser->segmentPkey = malloc(sizeof(segment_t **)*SEGMENT_INDEX_RESIZE);
  parser->propertyPkey = malloc(sizeof(property_t **)*PROPERTY_INDEX_RESIZE);
}

void rewindParser(parser_t *parser){
  parser->interchange = rewindLoop(parser->interchange);
  parser->functional = rewindLoop(parser->functional);
  parser->transaction = rewindLoop(parser->transaction);
  parser->payer = rewindLoop(parser->payer);
  parser->payee = rewindLoop(parser->payee);
  parser->header = rewindLoop(parser->header);
  parser->claim = rewindLoop(parser->claim);
  parser->loop = parser->interchange;
}

void parserCleanup(parser_t *parser){
  if(SEGMENT_INDEX_RESIZE % parser->segmentSeq != 0){
    parser->segmentPkey = realloc(parser->segmentPkey, sizeof(segment_t**)*parser->segmentSeq);
  }

  if(PROPERTY_INDEX_RESIZE % parser->propertySeq != 0){
    parser->propertyPkey = realloc(parser->propertyPkey, sizeof(property_t**)*parser->propertySeq);
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

void parserFree(parser_t *parser){
  if(NULL != parser){
    rewindParser(parser);
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

void loopFree(segment_t *loop){
  if(NULL != loop){
    segment_t *segment;
    segment_t *tmp;
    segment = loop->firstSegment;
    while(NULL != segment){
      tmp = segment->tail;
      if(segment != loop) segmentFree(segment);
      segment = tmp;
    }
  }
}

void segmentFree(segment_t *segment){
  if(NULL != segment){
    property_t *property;
    property_t *tmp;
    property = segment->firstProperty;
    while(NULL != property){
      tmp = property->tail;
      propertyFree(property);
      property = tmp;
    }
    free(segment);
  }
}

void propertyFree(property_t *property){
  free(property->value);
  free(property);
}


