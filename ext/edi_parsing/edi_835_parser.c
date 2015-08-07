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

void attachSegment(parser_t *parser, segment_t *segment){
  if(isISA(segment->name)){
    isaHandler(parser, segment);
  }else if(NULL == parser->loop || NULL == parser->interchange){
    parseFail(parser);
  }else if(isIEA(segment->name)){
    iea(parser, segment);
    parser->finished = true;
  }else if(isGS(segment->name)){
    gsHandler(parser, segment);
  }else if(NULL == parser->functional){
    parseFail(parser);
  }else if(isGE(segment->name)){
    geHandler(parser, segment);
  }else if(isST(segment->name)){
    stHandler(parser, segment);
  }else if(NULL == parser->transaction){
    parseFail(parser);
  }else if(isSE(segment->name)){
    seHandler(parser, segment);
  }else if(isN1(segment->name)){
    n1Handler(parser, segment);
  }else if(NULL == parser->payer || NULL == parser->payee){
    parseFail(parser);
  }else if(isLX(segment->name)){
    lxHandler(parser, segment);
  }else if(isCLP(segment->name)){
    clpHandler(parser, segment);
  }else if(isSVC(segment->name)){
    svcHandler(parser, segment);
  }else if(isPLB(segment->name)){
    plbHandler(parser, segment);
  }
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
  if(parser->loop == parser->interchange){
    addChildSegment(parser->interchange, segment);
    parser->functional = segment
    parser->loop = segment;
  }else if(NULL != parser->functional){
   parseFail(parser);
  else{
   parseFail(parser);
  }
}

void stHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->functional)
    addChildSegment(parser->functional, segment);
    parser->transaction = segment;
    parser->loop = segment;
  else{
   parseFail(parser);
  }
}

void n1Handler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->transaction){
    addChildSegment(parser->functional, segment);
    parser->payer = segment
    parser->loop = segment;
  }else if(parser->loop == parser->payer){
    addChildSegment(parser->payer, segment);
    parser->payee = segment
    parser->loop = segment;
  }else{
    parseFail(parser);
  }
}

void lxHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->payee)
    addChildSegment(parser->payee, segment);
    parser->header = segment;
    parser->loop = segment;
  else{
   parseFail(parser);
  }
}

void clpHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->service || parser->loop == parser->claim || parser->loop == parser->header){
    parser->service = NULL;
    addChildSegment(parser->header, segment);
    parser->claim = segment;
    parser->loop = segment;
  }else{
    parseFail(parser);
  }
}

void svcHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->claim || parser->loop == parser->service){
    addChildSegment(parser->claim, segment);
    parser->service = segment;
    parser->loop = segment;
  }else{
    parseFail(parser);
  }
}

void plbHandler(parser_t *parser, segment_t *segment){
  addChildSegment(parser->header, segment);
  parser->claim = segment;
  parser->loop = segment;
}

void seHandler(parser_t *parser, segment_t *segment){
  addChildSegment(parser->functional, segment);
  parser->transaction = segment;
  parser->loop = parser->functional;
}

void geHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->functional && isSE(parser->transaction->name)){
    addChildSegment(parser->interchange, segment);
    parser->functional = segment;
    parser->loop = parser->interchange;
  }else{
    parseFail(parser);
  }
}

void ieaHandler(parser_t *parser, segment_t *segment){
  if(parser->loop == parser->interchange && isGE(parser->functional-name)){
    parser->interchange->tail = segment;
    parser->interchange = segment;
    parser->loop = segment;
  }else{
    parseFail(parser);
  }
}

void parseFail(parser_t *parser){
  parser->failure = true;
  parser->finished = true;
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


