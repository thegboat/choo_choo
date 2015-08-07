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
  }
}

void parse835Segment(parser_t *parser){
  segment_t *segment = calloc(1,sizeof(segment_t));
  char *tok;
  char *saveptr;
  short cnt = 0;
  tok = strtok_r(parser->str, ELEMENT_SEPARATOR, &saveptr);
  setSegmentName(segment, tok);
  tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  while (tok != NULL)
  {
    cnt++;
    if(NULL != strstr(tok, COMPONENT_SEPARATOR)){
      parse835Element(tok, segment, cnt);
    }else{
      buildProperty(segment, tok, cnt, 0);
    }
    tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  }
  attachSegment(parser, segment);
}

void parse835Element(char *str, segment_t *segment, short seg_cnt){
  char *tok;
  char *saveptr;
  short cnt = 0;
  tok = strtok_r(str, COMPONENT_SEPARATOR, &saveptr);
  while (tok != NULL)
  {
    cnt++;
    buildProperty(segment, tok, seg_cnt, cnt);
    tok = strtok_r(NULL, COMPONENT_SEPARATOR, &saveptr);
  }
  segment->elements = cnt;
}

void isaHandler(parser_t *parser, segment_t *segment){
  if(NULL == parser->interchange){
    parser->interchange = segment;
    parser->loop = segment;
  }else{
    parseFail(parser);
  }
}

void gsHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->interchange)
    if(NULL == parser->functional){
      addChildSegment(parser->interchange, segment);
    }else{
      addSegment(parser->functional, segment);
    }
    parser->functional = segment
    parser->loop = segment;
  else{
   parseFail(parser);
  }
}

void stHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->functional)
    if(NULL == parser->transaction){
      addChildSegment(parser->functional, segment);
    }else{
      addSegment(parser->transaction, segment);
    }
    parser->transaction = segment;
    parser->loop = segment;
  else{
   parseFail(parser);
  }
}

void n1Handler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->functional){
    if(NULL == parser->payer){
      addChildSegment(parser->functional, segment);
    }else{
      addSegment(parser->payer, segment);
    }
    parser->payer = segment
    parser->loop = segment;
  }else if(parser->loop == parser->payer){
    if(NULL == parser->payee){
      addChildSegment(parser->payer, segment);
    }else{
      addSegment(parser->payee, segment);
    }
    parser->payee = segment
    parser->loop = segment;
  }
}

void lxHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->payee)
    if(NULL == parser->header){
      addChildSegment(parser->payee, segment);
    }else{
      addSegment(parser->header, segment);
    }
    parser->header = segment;
    parser->loop = segment;
  else{
   parseFail(parser);
  }
}

void clpHandler(parser_t *parser, segment_t *segment){
  if(NULL == parser->claim){
    addChildSegment(parser->header, segment);
  }else if(parser->loop == parser->claim || parser->service){
    addSegment(parser->claim, segment);
  }else if(parser->service){

  }else{
   parseFail(parser);
  }
  parser->claim = segment;
  parser->loop = segment;
}

void attachSegment(parser_t *parser, segment_t *segment){
  if(isISA(segment->name)){
    isaHandler(parser, segment);
  }else if(NULL == parser->loop || NULL == parser->interchange){
    parseFail(parser);
  }else if(isGS(segment->name)){
    gsHandler(parser, segment);
  }else if(isST(segment->name)){
    stHandler(parser, segment);
  }else if(isN1(segment->name)){
    n1Handler(parser, segment);
  }else if(isLX(segment->name)){
    lxHandler(parser, segment);
  }else if(isCLP(segment->name)){
  }else if(isSVC(segment->name)){
    resetDetail(parser);
    if(isCLP(parser->segment->name) && !isSVC(parser->service->name)){
      parser->service = calloc(1,sizeof(loop_t));
      loopInitializer(parser->service, SVC_SEGMENT);
      parser->loop = parser->service;
    }else if(isSVC(parser->service->name)){
      parser->loop = parser->service;
    }
  }else if(isPLB(segment->name)){
    if(isST(parser->transaction->name)){
      parser->loop = parser->transaction;
      resetClaim(parser);
    }else{
      parseFail(parser);
    }
  }else if(isGE(segment->name)){
    if(isST(parser->segment->name) && isGS(parser->functional->name)){
      parser->loop = parser->functional;
      resetClaim(parser);
    }else{
      parseFail(parser);
    }
  }else if(isIEA(segment->name)){
    if(isGS(parser->segment->name) && isISA(parser->interchange->name)){
      parser->loop = parser->interchange;
      resetClaim(parser);
    }else{
      parseFail(parser);
    }
  }
}

void parseFail(parser_t *parser){
  parser->failure = true;
  parser->finished = true;
}

void resetDetail(parser_t *parser){
  parser->curSvc = NULL;
}


void resetClaim(parser_t *parser){
  parser->curSvc = NULL;
  parser->curClp = NULL;
}

void parserInitialization(parser_t *parser){
  parser->failure = false;
  parser->finished = false;
  parser->interchange = NULL;
  parser->segment = NULL;  
  parser->functional = NULL;
  parser->transaction = NULL;
  parser->payer = NULL;
  parser->payee = NULL;
  parser->header = NULL;
  parser->claim = NULL;
}

void parserFree(parser_t *parser){
  loopFree(parser->interchange);
  loopFree(parser->functional);
  loopFree(parser->transaction);
  loopFree(parser->payer);
  loopFree(parser->payee);
  loopFree(parser->header);
  loopFree(parser->claim);
  loopFree(parser->service);
  free(parser);
}

void loopFree(loop_t *loop){
  segment_t *segment;
  segment_t *tmp;
  segment = loop->firstSegment;
  while(NULL != segment){
    tmp = segment->tail;
    segmentFree(segment);
    segment = tmp;
  }
  free(loop);
}

void segmentFree(segment_t *segment){
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

void propertyFree(property_t *property){
  free(property->value);
  free(property);
}


