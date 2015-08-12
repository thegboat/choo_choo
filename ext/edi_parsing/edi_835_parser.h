//
//  edi_835_parser.h
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#ifndef edi_835_parser_h
#define edi_835_parser_h

#include "edi_parsing.h"

typedef struct parser835_struct parser835_t;

struct parser835_struct
{
  parser_t super;
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

/* parser */

void parse835(parser835_t *parser, char *ediFile);
void parse835Segment(parser835_t *parser);
void parse835Element(parser835_t *parser, char *str, segment_t *segment, short seg_cnt);
void attach835Segment(parser835_t *parser, segment_t *segment);

void rewind835Parser(parser835_t *parser);
void parse835Fail(parser835_t *parser, short error);
void default835Handler(parser835_t *parser, segment_t *segment);
void validate835Parser(parser835_t *parser);
void parser835Free(parser835_t *parser);
void parser835Initialization(parser835_t *parser);
void isa835Handler(parser835_t *parser, segment_t *segment);
void gs835Handler(parser835_t *parser, segment_t *segment);
void st835Handler(parser835_t *parser, segment_t *segment);
void n1835Handler(parser835_t *parser, segment_t *segment);
void lx835Handler(parser835_t *parser, segment_t *segment);
void clp835Handler(parser835_t *parser, segment_t *segment);
void svc835Handler(parser835_t *parser, segment_t *segment);
void plb835Handler(parser835_t *parser, segment_t *segment);
void se835Handler(parser835_t *parser, segment_t *segment);
void ge835Handler(parser835_t *parser, segment_t *segment);
void iea835Handler(parser835_t *parser, segment_t *segment);
void parser835Cleanup(parser835_t *parser);

#endif
