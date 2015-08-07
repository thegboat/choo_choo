//
//  edi_835_parser.h
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#ifndef edi_835_parser_h
#define edi_835_parser_h

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edi_835_constants.h"

typedef struct segment_struct segment_t;
typedef struct property_struct property_t;
typedef struct parser_struct parser_t;
typedef struct loop_struct loop_t;

struct segment_struct
{
  char name[MAX_NAME_SIZE+1];
  segment_t *head;
  segment_t *tail;
  property_t *firstProperty;
  property_t *lastProperty;
  segment_t *firstSegment;
  segment_t *lastSegment;
  short elements;
};

struct property_struct
{
  char key[MAX_KEY_SIZE+1];
  char *value;
  property_t *head;
  property_t *tail;
};

struct loop_struct
{
  char name[MAX_NAME_SIZE+1];
  segment_t *firstSegment;
  segment_t *lastSegment; 
};

struct parser_struct
{
  int errors[MAX_ERROR_SIZE];
  char *str;
  segment_t *curClp;
  segment_t *curSvc;
  loop_t *loop;
  loop_t *interchange;
  loop_t *functional;
  loop_t *transaction;
  loop_t *payer;
  loop_t *payee;
  loop_t *header;
  loop_t *claim;
  loop_t *service;
  bool failure;
  bool finished;
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
void setSegmentName(segment_t *segment, char *src);
void addProperty(segment_t *segment, property_t *property);
void buildKey(char *key, char *seg_name, short seg_cnt, short elem_cnt);
void attachSegment(parser_t *parser, segment_t *segment);
void addChildSegment(segment_t *parent, segment_t *child);

/* loop */
void loopInitializer(loop_t *loop, const char *name);
void addSegment(loop_t *loop, segment_t * child);

/* parser */

void parse835(parser_t *parser, char *ediFile);
void nextSegment(parser_t *parser);
void parse835Segment(parser_t *parser);
void parse835Element(char *str, segment_t *segment, short seg_cnt);
void moveLoopIfNecessary(parser_t *parser);
void parseFail(parser_t *parser);
void parserFree(parser_t *parser);
void loopFree(loop_t *loop);
void segmentFree(segment_t *segment);
void propertyFree(property_t *property);

void resetDetail(parser_t *parser);
void resetClaim(parser_t *parser);

#endif
