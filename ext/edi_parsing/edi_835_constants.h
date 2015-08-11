//
//  edi_835_constants.h
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//
#ifndef edi_835_constants_h
#define edi_835_constants_h

#define ISA_SEGMENT "ISA"
#define IEA_SEGMENT "IEA"
#define TS3_SEGMENT "TS3"
#define TS2_SEGMENT "TS2"
#define CLP_SEGMENT "CLP"
#define CAS_SEGMENT "CAS"
#define NM1_SEGMENT "NM1"
#define MIA_SEGMENT "MIA"
#define MOA_SEGMENT "MOA"
#define AMT_SEGMENT "AMT"
#define QTY_SEGMENT "QTY"
#define SVC_SEGMENT "SVC"
#define PLB_SEGMENT "PLB"
#define RDM_SEGMENT "RDM"
#define BPR_SEGMENT "BPR"
#define TRN_SEGMENT "TRN"
#define CUR_SEGMENT "CUR"
#define REF_SEGMENT "REF"
#define DTM_SEGMENT "DTM"
#define PER_SEGMENT "PER"
#define GS_SEGMENT "GS" 
#define GE_SEGMENT "GE" 
#define ST_SEGMENT "ST" 
#define SE_SEGMENT "SE" 
#define N1_SEGMENT "N1"
#define N4_SEGMENT "N4"
#define N3_SEGMENT "N3"
#define LX_SEGMENT "LX"
#define LQ_SEGMENT "LQ"

#define PR_LOOP "PR"
#define PE_LOOP "PE"

#define ELEMENT_SEPARATOR       "*"
#define SEGMENT_SEPARATOR       "~"
#define REPITITION_SEPARATOR       "^"

#define MAX_NAME_SIZE 5
#define MAX_KEY_SIZE 10
#define MAX_ERROR_SIZE 10
#define MAX_THREADS 2
#define SEGMENT_INDEX_RESIZE 500
#define PROPERTY_INDEX_RESIZE 5000

#define ISA_SEGMENT_NOT_DETECTED_FIRST    1
#define MORE_THAN_ONE_ISA_SEGMENT_FOUND   2
#define WRONG_NUMBER_OF_ELEMENTS_FOR_ISA  3
#define MISSING_GS_SEGMENT                4
#define MISSING_ST_SEGMENT                5
#define INVALID_SE_SEGMENT                6
#define INVALID_ST_SEGMENT                7
#define INVALID_N1_SEGMENT                8
#define INVALID_LX_SEGMENT                9
#define INVALID_CLP_SEGMENT               10
#define INVALID_SVC_SEGMENT               11
#define INVALID_GE_SEGMENT                12
#define INVALID_IEA_SEGMENT               13
#define WRONG_NUMBER_OF_ELEMENTS_FOR_SE   14
#define WRONG_NUMBER_OF_ELEMENTS_FOR_GE   15
#define WRONG_NUMBER_OF_ELEMENTS_FOR_IEA  16
#define MISSING_SE_SEGMENT                17
#define MISSING_GE_SEGMENT                18
#define WRONG_NUMBER_OF_ELEMENTS_FOR_GS   19
#define WRONG_NUMBER_OF_ELEMENTS_FOR_ST   20
#define INVALID_PAYER_LOOP                21
#define INVALID_GS_SEGMENT                22
#define MISSING_PAYER_LOOP                23
#define MISSING_IEA_SEGMENT               24
#define INVALID_COMPONENT_SEPARATOR       25


#endif

