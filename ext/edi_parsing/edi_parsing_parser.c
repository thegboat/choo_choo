//
//  edi_parsing_parser.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//
#include "edi_parsing.h"

void *ediParsingMalloc(size_t nitems, size_t size){
  void *any = ruby_xcalloc(nitems, size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}

void ediParsingDealloc(void *any){
  if(any) {
    xfree(any);
    any = NULL;
  }
}

segment_t *parseSegment(parser_t *parser){
  unsigned long value;
  segment_t *segment = ediParsingMalloc(1,sizeof(segment_t));
  char *tok;
  char *saveptr;
  short element = 0;
  tok = strtok_r(parser->str, ELEMENT_SEPARATOR, &saveptr);
  segmentInitializer(segment, tok);
  tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  while (tok != NULL)
  {
    element++;
    if(strlen(parser->componentSeparator) == 1 && NULL != strstr(tok, parser->componentSeparator)){
      parseElement(segment, tok, parser->componentSeparator, element);
    }else{
      cacheProperty(segment, tok, element, 0);
    }
    tok = strtok_r(NULL, ELEMENT_SEPARATOR, &saveptr);
  }
  segment->elements = element;
  if(parser->segmentCount == 0 && isISA(segment)){
    if(!st_lookup(segment->propertyCache, getPropertyKey(16,0), &value) || strlen((char *)value) != 1){
      parserFail(parser, INVALID_COMPONENT_SEPARATOR);
    }else{
      strcpy(parser->componentSeparator, (char *)value);
      if(!st_lookup(segment->propertyCache, getPropertyKey(11,0), &value) || strlen((char *)value) != 1){
        parserFail(parser, INVALID_REPITITON_SEPARATOR);
      }else{
        strcpy(parser->repititionSeparator, (char *)value);
      }
    }
  }
  parser->segmentCount++;
  return segment;
}

int parseElement(segment_t *segment, char *str, const char componentSeparator[2], short element){
  char *tok;
  char *saveptr;
  short component = 0;
  tok = strtok_r(str, componentSeparator, &saveptr);
  while (tok != NULL)
  {
    component++;
    cacheProperty(segment, tok, element, component);
    tok = strtok_r(NULL, componentSeparator, &saveptr);
  }
  return component;
}

void parserInitialization(parser_t *parser){
  parser->byName = NULL;
  parser->nameIndex = NULL;
  parser->primaryIndex = NULL;
  parser->failure = false;
  parser->finished = false;
  parser->errorCount = 0;
  parser->segmentCount = 0;
  parser->nameCount = 0;
  parser->componentSeparator[0] = '\0';
  parser->repititionSeparator[0] = '\0';
  memset(&parser->errors, 0, sizeof(short)*10);
}

void parserFree(parser_t *parser){
  long i;
  if(parser->primaryIndex){
    for(i=0; i<parser->segmentCount;i++){
      segmentFree(parser->primaryIndex[i]);
    }
    ediParsingDealloc(parser->primaryIndex);
  }
  ediParsingDealloc(parser->nameIndex);
  ediParsingDealloc(parser->byName);
  ediParsingDealloc(parser);
}

void parserFail(parser_t *parser, short error){
  parser->failure = true;
  parser->finished = true;
  
  if(parser->errorCount < MAX_ERROR_SIZE){
    parser->errors[parser->errorCount] = error;
    parser->errorCount++;
  }
}