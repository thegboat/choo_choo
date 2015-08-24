//
//  edi_parsing.h
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/11/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <search.h>
#include <ruby.h>
#include "edi_parsing_constants.h"

// data types

typedef struct segment_struct segment_t;
typedef struct property_struct property_t;
typedef struct parser_struct parser_t;
typedef struct index_stat_struct index_stat_t;
typedef struct parser835_struct parser835_t;
typedef struct anchor_struct anchor_t;

struct index_stat_struct
{
  int lower;
  int upper;
};

struct parser_struct
{
  short errors[MAX_ERROR_SIZE];
  short errorCount;
  char documentType[10];
  segment_t *root;
  segment_t **nameIndex;
  segment_t **primaryIndex;
  char *str;
  char componentSeparator[2];
  int segmentCount;
  int propertyCount;
  bool failure;
  bool finished;
};

struct anchor_struct
{
  parser_t *parser;
  segment_t *segment;
};

struct parser835_struct
{
  parser_t *super;
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
  int children;
  int depth;
  int pkey;
  int boundary;
};

struct property_struct
{
  segment_t *owner;
  char key[MAX_KEY_SIZE+1];
  char *value;
  property_t *head;
  property_t *tail;
};

// inspection

bool identify(segment_t *segment, const char *seg);
bool isISA(segment_t *segment);
bool isIEA(segment_t *segment);
bool isTS3(segment_t *segment);
bool isTS2(segment_t *segment);
bool isCLP(segment_t *segment);
bool isCAS(segment_t *segment);
bool isNM1(segment_t *segment);
bool isMIA(segment_t *segment);
bool isMOA(segment_t *segment);
bool isAMT(segment_t *segment);
bool isQTY(segment_t *segment);
bool isSVC(segment_t *segment);
bool isPLB(segment_t *segment);
bool isRDM(segment_t *segment);
bool isBPR(segment_t *segment);
bool isTRN(segment_t *segment);
bool isCUR(segment_t *segment);
bool isREF(segment_t *segment);
bool isDTM(segment_t *segment);
bool isPER(segment_t *segment);
bool isGS(segment_t *segment); 
bool isGE(segment_t *segment); 
bool isST(segment_t *segment); 
bool isSE(segment_t *segment); 
bool isN1(segment_t *segment);
bool isN4(segment_t *segment);
bool isN3(segment_t *segment);
bool isLX(segment_t *segment);
bool isLQ(segment_t *segment);
bool isPR(segment_t *segment);
bool isPE(segment_t *segment);

// segment

void segmentInitializer(segment_t *segment, char *src);
void addProperty(segment_t *segment, property_t *property);
void buildProperty(segment_t *segment, char *data, short seg_cnt, short elem_cnt);
void buildKey(char *key, char *seg_name, short seg_cnt, short elem_cnt);
void addChildSegment(segment_t *parent, segment_t *child);
void loopFree(segment_t *loop);
void segmentFree(segment_t *segment);
void propertyFree(property_t *property);
segment_t *rewindLoop(segment_t *loop);
bool elementCountIn(segment_t *segment, int start, int end);

// parser

void *ediParsingMalloc(size_t size);
segment_t *parseSegment(parser_t *parser);
int parseElement(segment_t *segment, char *str, const char componentSeparator[2], short seg_cnt);
void parserInitialization(parser_t *parser);
void parserFree(parser_t *parser);
void parserFail(parser_t *parser, short error);

// traversal

void buildIndexes(parser_t *parser);
VALUE segmentFind(parser_t *parser, segment_t *segment, VALUE names_rb, VALUE limit_rb);
VALUE segmentToHash(segment_t *segment);
VALUE segmentChildren(parser_t *parser, segment_t *segment, VALUE names_rb, VALUE limit_rb);
VALUE propertiesToHash(property_t *property);
index_stat_t nameIndexSearch(parser_t *parser, const char *name);
bool missingSegment(parser_t *parser, char *src);
int segmentsWithName(parser_t *parser, char *src);
bool multipleWithName(parser_t *parser, char *src);
VALUE segmentWhere(parser_t *parser, segment_t *segment, VALUE name_rb, VALUE key_rb, VALUE value_rb, VALUE limit_rb);

// 835

void parse835(anchor_t *anchor, char *ediFile);

// interface

void Init_edi_parsing(void);
VALUE buildSegmentNode(parser_t *parser, segment_t *segment);

// errors

VALUE getErrors(parser_t *parser);

