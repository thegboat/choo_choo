//
//  edi_parsing_parser.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#include "edi_parsing.h"

void *ediParsingMalloc(size_t size){
  void *any;
  any = calloc(1, size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}

segment_t *parseSegment(parser_t *parser){
  segment_t *segment = (segment_t *)ediParsingMalloc(sizeof(segment_t));
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
      parser->propertyCount += parseElement(segment, tok, parser->componentSeparator, cnt);
    }else{
      buildProperty(segment, tok, cnt, 0);
      parser->propertyCount++;
    }
    tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  }
  segment->elements = cnt;
  parser->segmentCount++;
  return segment;
}

int parseElement(segment_t *segment, char *str, const char componentSeparator[2], short seg_cnt){
  char *tok;
  char *saveptr;
  short cnt = 0;
  tok = strtok_r(str, componentSeparator, &saveptr);
  while (tok != NULL)
  {
    cnt++;
    buildProperty(segment, tok, seg_cnt, cnt);
    tok = strtok_r(NULL, componentSeparator, &saveptr);
  }
  return cnt;
}

void parserInitialization(parser_t *parser, char *document){
  size_t size = sizeof(char)*(strlen(document)+1);
  parser->document = (char *)ediParsingMalloc(size);
  memcpy(parser->document, document, size);
  parser->nameIndex = NULL;
  parser->primaryIndex = NULL;
  parser->failure = false;
  parser->finished = false;
  parser->errorCount = 0;
  parser->segmentCount = 0;
  parser->propertyCount = 0;
  parser->references = 1;
  parser->componentSeparator[0] = '\0';
  memset(&parser->errors, 0, sizeof(short)*10);
}

void parserFree(parser_t *parser){
  if(NULL != parser->primaryIndex){
    for(int i=0; i<parser->segmentCount;i++){
      segmentFree(parser->primaryIndex[i]);
    }
    xfree(parser->primaryIndex);
  }
  if(NULL != parser->nameIndex) xfree(parser->nameIndex);
  if(NULL != parser->document) xfree(parser->document);
  xfree(parser);
}

void parserFail(parser_t *parser, short error){
  parser->failure = true;
  parser->finished = true;
  
  if(parser->errorCount < MAX_ERROR_SIZE){
    parser->errors[parser->errorCount] = error;
    parser->errorCount++;
  }
}