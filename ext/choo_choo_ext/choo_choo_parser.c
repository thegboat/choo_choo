//
//  choo_choo_parser.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//
#include "choo_choo.h"

void *choo_chooMalloc(size_t nitems, size_t size){
  void *any = ruby_xcalloc(nitems, size);
  if(any == NULL){
    rb_raise(rb_eRuntimeError, "Memory could not be allocated");
  }
  return any;
}

void choo_chooDealloc(void *any){
  if(any) {
    xfree(any);
    any = NULL;
  }
}

segment_t *parseSegment(parser_t *parser){
  char *ptr, *rest = parser->str;
  segment_t *segment = choo_chooMalloc(1,sizeof(segment_t));
  short element = 0;
  char *tok = strsep(&rest, (char*)&ELEMENT_SEPARATOR);
  segmentInitializer(segment, tok);
  while ((tok = strsep(&rest, (char*)&ELEMENT_SEPARATOR)))
  {
    element++;
    if(strlen(parser->componentSeparator) == 1 && NULL != strstr(tok, parser->componentSeparator)){
      parseElement(segment, tok, parser->componentSeparator, element);
    }else{
      cacheProperty(segment, tok, element, 0);
    }
  }
  segment->elements = element;
  if(parser->segmentCount == 0 && isISA(segment)){
    ptr = propertyLookup(segment, 16, 0);
    if(!ptr || strlen(ptr) != 1){
      parserFail(parser, INVALID_COMPONENT_SEPARATOR);
    }else{
      strcpy(parser->componentSeparator, ptr);
      ptr = propertyLookup(segment, 11, 0);
      if(!ptr || strlen(ptr) != 1){
        parserFail(parser, INVALID_REPITITON_SEPARATOR);
      }else{
        strcpy(parser->repititionSeparator, ptr);
      }
    }
  }
  parser->segmentCount++;
  return segment;
}

int parseElement(segment_t *segment, char *str, const char componentSeparator[2], short element){
  char *tok, *rest = str;
  short component = 0;
  while((tok = strsep(&rest, componentSeparator)))
  {
    component++;
    cacheProperty(segment, tok, element, component);
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
    choo_chooDealloc(parser->primaryIndex);
  }
  choo_chooDealloc(parser->nameIndex);
  choo_chooDealloc(parser->byName);
  choo_chooDealloc(parser);
}

void parserFail(parser_t *parser, short error){
  parser->failure = true;
  parser->finished = true;
  
  if(parser->errorCount < MAX_ERROR_SIZE){
    parser->errors[parser->errorCount] = error;
    parser->errorCount++;
  }
}