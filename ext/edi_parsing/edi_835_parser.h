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
  short elements;
};

struct property_struct
{
  char key[MAX_KEY_SIZE+1];
  char *value;
  property_t *head;
  property_t *tail;
};

struct parser_struct
{
  short errors[MAX_ERROR_SIZE];
  short errorCount;
  char *str;
  segment_t *loop;
  segment_t *interchange;
  segment_t *functional;
  segment_t *transaction;
  segment_t *payer;
  segment_t *payee;
  segment_t *header;
  segment_t *claim;
  segment_t *service;
  segment_t *trailer;
  char componentSeparator[2];
  long segmentCount;
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
void segmentInitializer(segment_t *segment, char *src);
void addProperty(segment_t *segment, property_t *property);
void buildKey(char *key, char *seg_name, short seg_cnt, short elem_cnt);
void attachSegment(parser_t *parser, segment_t *segment);
void addChildSegment(segment_t *parent, segment_t *child);

/* parser */

void parse835(parser_t *parser, char *ediFile);
void parse835Segment(parser_t *parser);
void parse835Element(char *str, const char componentSeparator[2], segment_t *segment, short seg_cnt);

void rewindParser(parser_t *parser);
segment_t *rewindLoop(segment_t *loop);
void parseFail(parser_t *parser, short error);
void defaultHandler(parser_t *parser, segment_t *segment);
void validateParser(parser_t *parser);
void parserFree(parser_t *parser);
void loopFree(segment_t *segment_t);
void segmentFree(segment_t *segment);
void propertyFree(property_t *property);
void parserInitialization(parser_t *parser);
void attachSegment(parser_t *parser, segment_t *segment);
void isaHandler(parser_t *parser, segment_t *segment);
void gsHandler(parser_t *parser, segment_t *segment);
void stHandler(parser_t *parser, segment_t *segment);
void n1Handler(parser_t *parser, segment_t *segment);
void lxHandler(parser_t *parser, segment_t *segment);
void clpHandler(parser_t *parser, segment_t *segment);
void svcHandler(parser_t *parser, segment_t *segment);
void plbHandler(parser_t *parser, segment_t *segment);
void seHandler(parser_t *parser, segment_t *segment);
void geHandler(parser_t *parser, segment_t *segment);
void ieaHandler(parser_t *parser, segment_t *segment);

#endif
