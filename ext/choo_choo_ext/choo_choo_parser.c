//
//  choo_choo_parser.c
//  choo_choo
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//
#include "choo_choo.h"


static inline int parseElement(parser_t *parser, char *str, short element);
static void cacheProperty(parser_t *parser, const char *tok, short element, short component);

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
  parser->current =  choo_chooMalloc(1,sizeof(segment_t));
  short element = 0;
  char *tok = strsep(&rest, (char*)&ELEMENT_SEPARATOR);
  segmentInitializer(parser->current, tok);
  while ((tok = strsep(&rest, (char*)&ELEMENT_SEPARATOR)))
  {
    element++;
    if(strlen(parser->componentSeparator) == 1 && NULL != strstr(tok, parser->componentSeparator)){
      parseElement(parser, tok, element);
    }else{
      cacheProperty(parser, tok, element, 0);
    }
  }
  parser->current->elements = element;
  if(parser->segmentCount == 0 && isISA(parser->current)){
    ptr = propertyLookup(parser->current, 16, 0);
    if(!ptr || strlen(ptr) != 1){
      parserFail(parser, INVALID_COMPONENT_SEPARATOR);
    }else{
      strcpy(parser->componentSeparator, ptr);
      ptr = propertyLookup(parser->current, 11, 0);
      if(!ptr || strlen(ptr) != 1){
        parserFail(parser, INVALID_REPITITON_SEPARATOR);
      }else{
        strcpy(parser->repititionSeparator, ptr);
      }
    }
  }
  parser->segmentCount++;
  return parser->current;
}

static inline int parseElement(parser_t *parser, char *str, short element){
  char *tok, *rest = str;
  short component = 0;
  while((tok = strsep(&rest, parser->componentSeparator)))
  {
    component++;
    cacheProperty(parser, tok, element, component);
  }
  return component;
}

static void cacheProperty(parser_t *parser, const char *tok, short element, short component){
  unsigned long value, key = getPropertyKey(element, component);
  char *data;

  if(strlen(tok)){
    if(st_lookup(parser->stringTable, (st_data_t)tok, &value)){
      data = (char*)value;
    }else{
      data = strdup(tok);
    }
  }else{
    data = "";
  }
  st_add_direct(parser->current->propertyCache, (st_data_t)key, (unsigned long)data);
}

void parserInitialization(parser_t *parser){
  parser->byName = NULL;
  parser->nameIndex = NULL;
  parser->primaryIndex = NULL;
  parser->current = NULL;
  parser->failure = false;
  parser->finished = false;
  parser->errorCount = 0;
  parser->segmentCount = 0;
  parser->nameCount = 0;
  parser->componentSeparator[0] = '\0';
  parser->repititionSeparator[0] = '\0';
  parser->stringTable = st_init_strtable();
  memset(&parser->errors, 0, sizeof(short)*MAX_ERROR_SIZE);
}

void parserFree(parser_t *parser){
  long i;
  if(parser->primaryIndex){
    for(i=0; i<parser->segmentCount;i++){
      segmentFree(parser->primaryIndex[i]);
    }
    choo_chooDealloc(parser->primaryIndex);
  }
  st_free_table(parser->stringTable);
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