//
//  edi_835_parser.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_835_parser.h"

void parse835(parser_t *parser, char *ediFile){
  parser->finished = false;
  parser->failure = false;
  char *saveptr;
  parser->str = strtok_r(ediFile, SEGMENT_SEPARATOR, &saveptr);
  while(NULL != parser->str && !parser->finished && !parser->failure){
    moveLoopIfNecessary(parser);
    parse835Segment(parser);
    parser->str = strtok_r(NULL, SEGMENT_SEPARATOR, &saveptr);
  }
}

void parse835Segment(parser_t *parser){
  if(!parser->finished && !parser->failure){
    segment_t *segment = calloc(1,sizeof(segment_t));
    char *tok;
    char *saveptr;
    short cnt = 0;
    tok = strtok_r(parser->str, ELEMENT_SEPARATOR, &saveptr);
    setSegmentName(segment, tok);
    attachSegment(parser, segment);
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
  }
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

void moveLoopIfNecessary(parser_t *parser){
  if(isISA(parser->str)){
    if(!isISA(parser->loop->name)){
      parser->interchange = calloc(1,sizeof(loop_t));
      loopInitializer(parser->interchange, ISA_SEGMENT);
      parser->loop = parser->interchange;
    }else{
      //more than one isa
      parseFail(parser);
    }
  }else if(isGS(parser->str)){
    if(isISA(parser->loop->name) && !isGS(parser->functional->name)){
      parser->functional = calloc(1,sizeof(loop_t));
      loopInitializer(parser->functional, GS_SEGMENT);
      parser->loop = parser->functional;
    }else{
      parseFail(parser);
    }
  }else if(isST(parser->str)){
    if(isGS(parser->loop->name) && !isST(parser->transaction->name)){
      parser->transaction = calloc(1,sizeof(loop_t));
      loopInitializer(parser->transaction, ST_SEGMENT);
      parser->loop = parser->transaction;
    }else{
      parseFail(parser);
    }
  }else if(isN1(parser->str)){
    if(isST(parser->loop->name) && !isPR(parser->payer->name)){
      parser->payer = calloc(1,sizeof(loop_t));
      loopInitializer(parser->payer, PR_LOOP);
      parser->loop = parser->payer;
    }else if(isPR(parser->loop->name) && !isPE(parser->payee->name)){
      parser->payee = calloc(1,sizeof(loop_t));
      loopInitializer(parser->payee, PE_LOOP);
      parser->loop = parser->payee;
    }else{
      parseFail(parser);
    }
  }else if(isLX(parser->str)){
    if(isPE(parser->loop->name) && !isLX(parser->header->name)){
      parser->header = calloc(1,sizeof(loop_t));
      loopInitializer(parser->header, LX_SEGMENT);
      parser->loop = parser->header;
    }else{
      parseFail(parser);
    }
  }else if(isCLP(parser->str)){
    resetClaim(parser);
    if(isLX(parser->loop->name) && !isCLP(parser->claim->name)){
      parser->claim = calloc(1,sizeof(loop_t));
      loopInitializer(parser->claim, CLP_SEGMENT);
      parser->loop = parser->claim;
    }else if(isCLP(parser->claim->name)){
      parser->loop = parser->claim;
    }
  }else if(isSVC(parser->str)){
    resetDetail(parser);
    if(isCLP(parser->loop->name) && !isSVC(parser->service->name)){
      parser->service = calloc(1,sizeof(loop_t));
      loopInitializer(parser->service, SVC_SEGMENT);
      parser->loop = parser->service;
    }else if(isSVC(parser->service->name)){
      parser->loop = parser->service;
    }
  }else if(isPLB(parser->str)){
    if(isST(parser->transaction->name)){
      parser->loop = parser->transaction;
      resetClaim(parser);
    }else{
      parseFail(parser);
    }
  }else if(isGE(parser->str)){
    if(isST(parser->loop->name) && isGS(parser->functional->name)){
      parser->loop = parser->functional;
      resetClaim(parser);
    }else{
      parseFail(parser);
    }
  }else if(isIEA(parser->str)){
    if(isGS(parser->loop->name) && isISA(parser->interchange->name)){
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


