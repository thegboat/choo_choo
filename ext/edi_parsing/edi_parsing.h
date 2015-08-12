//
//  edi_835_parser.h
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/11/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#ifndef edi_parsing_h
#define edi_parsing_h

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <search.h>
#include <ruby.h>
#include "edi_parsing_constants.h"

typedef struct segment_struct segment_t;
typedef struct property_struct property_t;
typedef struct parser_struct parser_t;

struct parser_struct
{
  short errors[MAX_ERROR_SIZE];
  short errorCount;
  char *str;
  char componentSeparator[2];
  int depth;
  int segmentCount;
  int propertyCount;
  bool failure;
  bool finished;
};

struct segment_struct
{
  char name[MAX_NAME_SIZE+1];
  segment_t *head;
  segment_t *tail;
  segment_t *parent;
  property_t *firstProperty;
  property_t *lastProperty;
  segment_t *firstSegment;
  segment_t *lastSegment;
  int elements;
  int depth;
  int pkey;
};

struct property_struct
{
  char key[MAX_KEY_SIZE+1];
  char *value;
  property_t *head;
  property_t *tail;
  int pkey;
};

/* inspection */
bool identify(char *src, const char* seg);
bool isISA(char *src);
bool isIEA(char *src);
bool isTS3(char *src);
bool isTS2(char *src);
bool isCLP(char *src);
bool isCAS(char *src);
bool isNM1(char *src);
bool isMIA(char *src);
bool isMOA(char *src);
bool isAMT(char *src);
bool isQTY(char *src);
bool isSVC(char *src);
bool isPLB(char *src);
bool isRDM(char *src);
bool isBPR(char *src);
bool isTRN(char *src);
bool isCUR(char *src);
bool isREF(char *src);
bool isDTM(char *src);
bool isPER(char *src);
bool isGS(char *src); 
bool isGE(char *src); 
bool isST(char *src); 
bool isSE(char *src); 
bool isN1(char *src);
bool isN4(char *src);
bool isN3(char *src);
bool isLX(char *src);
bool isLQ(char *src);
bool isPR(char *src);
bool isPE(char *src);

/* segment */

void buildProperty(segment_t *segment, char *data, short seg_cnt, short elem_cnt);
void segmentInitializer(segment_t *segment, char *src);
void addProperty(segment_t *segment, property_t *property);
void buildKey(char *key, char *seg_name, short seg_cnt, short elem_cnt);
void addChildSegment(segment_t *parent, segment_t *child);
void segmentFree(segment_t *segment);
void propertyFree(property_t *property);
segment_t *rewindLoop(segment_t *loop);
void loopFree(segment_t *segment_t);
void *ediParsingCalloc(size_t nitems, size_t size);
void *ediParsingMalloc(size_t size);
void parseElement(segment_t *segment, char *str, const char componentSeparator[2], short seg_cnt);
void parseSegment(parser_t *parser);
VALUE segment_to_hash(segment_t *segment);

/* interface */

VALUE interchange_loop_alloc(VALUE self);
void interchange_loop_free(VALUE self);
VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str);
VALUE choo_choo_parse_835(VALUE segment, VALUE isa_str);
VALUE interchange_loop_to_hash(VALUE self);
VALUE segment_to_hash(segment_t *segment);
void Init_edi_parsing(void);
void Init_edi_835_parsing(void);


#endif