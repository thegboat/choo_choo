//
//  choo_choo.h
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/11/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <search.h>
#include <ruby.h>
#include <ruby/st.h>
#include "choo_choo_constants.h"

#define getPropertyKey(element,component) (element)*100+(component)
#define isChildOf(thechild,theparent) (theparent)==(thechild)->parent
#define isDescendantOf(descendant,parent) ((descendant)->pkey>(parent)->pkey && (descendant)->pkey<=(parent)->boundary)
#define elementCountIn(segment,start,end) ((segment)->elements>=(start) && (segment)->elements<=(end))

#define identify(segment,segname) (segment&&!strcmp(segment->name,segname))
#define isPR(segment) identify(segment,PR_LOOP)
#define isPE(segment) identify(segment,PE_LOOP)
#define isISA(segment) identify(segment,ISA_SEGMENT)
#define isIEA(segment) identify(segment,IEA_SEGMENT)
#define isTS3(segment) identify(segment,TS3_SEGMENT)
#define isTS2(segment) identify(segment,TS2_SEGMENT)
#define isCLP(segment) identify(segment,CLP_SEGMENT)
#define isCAS(segment) identify(segment,CAS_SEGMENT)
#define isNM1(segment) identify(segment,NM1_SEGMENT)
#define isMIA(segment) identify(segment,MIA_SEGMENT)
#define isMOA(segment) identify(segment,MOA_SEGMENT)
#define isAMT(segment) identify(segment,AMT_SEGMENT)
#define isQTY(segment) identify(segment,QTY_SEGMENT)
#define isSVC(segment) identify(segment,SVC_SEGMENT)
#define isPLB(segment) identify(segment,PLB_SEGMENT)
#define isRDM(segment) identify(segment,RDM_SEGMENT)
#define isBPR(segment) identify(segment,BPR_SEGMENT)
#define isTRN(segment) identify(segment,TRN_SEGMENT)
#define isCUR(segment) identify(segment,CUR_SEGMENT)
#define isREF(segment) identify(segment,REF_SEGMENT)
#define isDTM(segment) identify(segment,DTM_SEGMENT)
#define isPER(segment) identify(segment,PER_SEGMENT)
#define isGS(segment) identify(segment,GS_SEGMENT)
#define isGE(segment) identify(segment,GE_SEGMENT)
#define isST(segment) identify(segment,ST_SEGMENT)
#define isSE(segment) identify(segment,SE_SEGMENT)
#define isN1(segment) identify(segment,N1_SEGMENT)
#define isN4(segment) identify(segment,N4_SEGMENT)
#define isN3(segment) identify(segment,N3_SEGMENT)
#define isLX(segment) identify(segment,LX_SEGMENT)
#define isLQ(segment) identify(segment,LQ_SEGMENT)

// data types

typedef struct segment_struct segment_t;
typedef struct parser_struct parser_t;
typedef struct index_stat_struct index_stat_t;
typedef struct parser835_struct parser835_t;
typedef struct anchor_struct anchor_t;

struct index_stat_struct
{
  int lower;
  int upper;
  char name[MAX_NAME_SIZE+1]; 
};

struct parser_struct
{
  short errors[MAX_ERROR_SIZE];
  short errorCount;
  char documentType[10];
  VALUE doc;
  segment_t *root;
  index_stat_t *nameIndex;
  segment_t **byName;
  segment_t **primaryIndex;
  char *str;
  char componentSeparator[2];
  char repititionSeparator[2];
  unsigned long segmentCount;
  unsigned long nameCount;
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
  segment_t *firstSegment;
  segment_t *lastSegment;
  short elements;
  short children;
  short depth;
  unsigned long pkey;
  unsigned long boundary;
  st_table* propertyCache;
};

// segment

void segmentInitializer(segment_t *segment, char *src);
void addChildSegment(segment_t *parent, segment_t *child);
void loopFree(segment_t *loop);
void segmentFree(segment_t *segment);
segment_t *rewindLoop(segment_t *loop);
void cacheProperty(segment_t *segment, char *data, short element, short component);

// parser

void *ediParsingMalloc(size_t nitems, size_t size);
void ediParsingDealloc(void *any);
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
VALUE propertiesToHash(segment_t *segment);
index_stat_t nameIndexSearch(parser_t *parser, const char *name);
bool missingSegment(parser_t *parser, char *src);
int segmentsWithName(parser_t *parser, char *src);
VALUE segmentExists(parser_t *parser, segment_t *segment, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb);
VALUE segmentWhere(parser_t *parser, segment_t *segment, VALUE name_rb, VALUE element_int_rb, VALUE component_int_rb, VALUE value_rb, VALUE limit_rb);
VALUE segmentGetProperty(segment_t *segment, VALUE element_int_rb, VALUE component_int_rb);
char *propertyLookup(segment_t *segment,  short element, short component);
void init_choo_choo_traversal();

// 835

void parse835(parser_t *s_parser, const char *ediFile);
void init_choo_choo_835();

// interface

void Init_choo_choo(void);
VALUE buildSegmentNode(parser_t *parser, segment_t *segment);
anchor_t *getAnchor(VALUE segment_rb);

// errors

VALUE getErrors(parser_t *parser);

// carecloud

void init_choo_choo_segment();

