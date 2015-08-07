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
#define COMPONENT_SEPARATOR     ":"
#define SEGMENT_SEPARATOR       "~"

#define MAX_KEY_SIZE 10
#define MAX_ERROR_SIZE 100
#define MAX_NAME_SIZE 5

#define LOOP_HEADER "LOOP_HEADER"
#define LOOP_1000A  "LOOP_1000A"
#define LOOP_1000B  "LOOP_1000B"
#define LOOP_2000   "LOOP_2000"
#define LOOP_2100   "LOOP_2100"
#define LOOP_2110   "LOOP_2110"
#define RECEIVER_IDENTIFICATION_NUMBER_REF01    "EV"
#define LINE_ITEM_CONTROL_NUMBER_REF01          "6R"
#define HEALTHCARE_POLICY_IDENTIFICATION_REF01  "0K"
#define VERSION_CODE_LOCAL_REF01                "F2"
#define CLAIM_RELATED_REF01_VALUES      {"1L", "1W","28", "6P", "9A", "9C", "BB", "CE", "EA", "F8", "G1", "G3", "IG", "SY"}
#define RENDERING_PROVIDER_ID_REF01_VALUES {"1A", "1B", "1C", "1D", "1G", "1H", "D3", "G2", "0B", "1J", "LU"}
#define SERVICE_REF01_VALUES            {"1S", "APC", "BB", "E9", "G1", "G3", "LU", "RB"}
#define RENDERING_PROVIDER_INFO_REF01_VALUES {"1A", "1B", "1C", "1D", "1G", "1H", "1J", "HPI", "SY", "TJ", "0B", "D3", "G2"}
#define INTERCHANGE_CONTROL_DE_LENGTH   16


#define VERSION_IDENTIFIER    "00501"

#define PROVIDER_UPIN_NUMBER  "1G"
#define PAYER_ID              "2U"
#define STATE_LICENCE_NUMBER  "0B"
#define PAYEE_ID              "PQ"
#define TAX_ID                "TJ"
#define RENDERING_PROVIDER    "82"   
#define INSURED_OR_SUBSCRIBER "IL" 
#define PATIENT               "QC" 
#define CORRECTED_INSURED     "74"

#endif

