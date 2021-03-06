//
//  choo_choo_constants.h
//  choo_choo
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 CareCloud. All rights reserved.
//

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
#define MAX_SEGMENT_NAMES 24336

#define MAX_NAME_SIZE 3
#define MAX_KEY_SIZE 10
#define MAX_ERROR_SIZE 10

#define UNKNOWN_ERROR                                        0
#define ISA_SEGMENT_NOT_DETECTED_FIRST                       1
#define INVALID_COMPONENT_SEPARATOR                          2
#define INVALID_ISA_SEGMENT                                  3
#define INVALID_IEA_SEGMENT                                  4
#define INVALID_TS3_SEGMENT                                  5
#define INVALID_TS2_SEGMENT                                  6
#define INVALID_CLP_SEGMENT                                  7
#define INVALID_CAS_SEGMENT                                  8
#define INVALID_NM1_SEGMENT                                  9
#define INVALID_MIA_SEGMENT                                  10
#define INVALID_MOA_SEGMENT                                  11
#define INVALID_AMT_SEGMENT                                  12
#define INVALID_QTY_SEGMENT                                  13
#define INVALID_SVC_SEGMENT                                  14
#define INVALID_PLB_SEGMENT                                  15
#define INVALID_RDM_SEGMENT                                  16
#define INVALID_BPR_SEGMENT                                  17
#define INVALID_TRN_SEGMENT                                  18
#define INVALID_CUR_SEGMENT                                  19
#define INVALID_REF_SEGMENT                                  20
#define INVALID_DTM_SEGMENT                                  21
#define INVALID_PER_SEGMENT                                  22
#define INVALID_GS_SEGMENT                                   23
#define INVALID_GE_SEGMENT                                   24
#define INVALID_ST_SEGMENT                                   25
#define INVALID_SE_SEGMENT                                   26
#define INVALID_N1_SEGMENT                                   27
#define INVALID_N4_SEGMENT                                   28
#define INVALID_N3_SEGMENT                                   29
#define INVALID_LX_SEGMENT                                   30
#define INVALID_LQ_SEGMENT                                   31
#define WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT             32
#define WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT             33
#define WRONG_NUMBER_OF_ELEMENTS_FOR_TS3_SEGMENT             34
#define WRONG_NUMBER_OF_ELEMENTS_FOR_TS2_SEGMENT             35
#define WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT             36
#define WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT             37
#define WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT             38
#define WRONG_NUMBER_OF_ELEMENTS_FOR_MIA_SEGMENT             39
#define WRONG_NUMBER_OF_ELEMENTS_FOR_MOA_SEGMENT             40
#define WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT             41
#define WRONG_NUMBER_OF_ELEMENTS_FOR_QTY_SEGMENT             42
#define WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT             43
#define WRONG_NUMBER_OF_ELEMENTS_FOR_PLB_SEGMENT             44
#define WRONG_NUMBER_OF_ELEMENTS_FOR_RDM_SEGMENT             45
#define WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT             46
#define WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT             47
#define WRONG_NUMBER_OF_ELEMENTS_FOR_CUR_SEGMENT             48
#define WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT             49
#define WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT             50
#define WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT             51
#define WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT              52
#define WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT              53
#define WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT              54
#define WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT              55
#define WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT              56
#define WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT              57
#define WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT              58
#define WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT              59
#define WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT              60
#define MISSING_ISA_SEGMENT                                  61
#define MISSING_IEA_SEGMENT                                  62
#define MISSING_TS3_SEGMENT                                  63
#define MISSING_TS2_SEGMENT                                  64
#define MISSING_CLP_SEGMENT                                  65
#define MISSING_CAS_SEGMENT                                  66
#define MISSING_NM1_SEGMENT                                  67
#define MISSING_MIA_SEGMENT                                  68
#define MISSING_MOA_SEGMENT                                  69
#define MISSING_AMT_SEGMENT                                  70
#define MISSING_QTY_SEGMENT                                  71
#define MISSING_SVC_SEGMENT                                  72
#define MISSING_PLB_SEGMENT                                  73
#define MISSING_RDM_SEGMENT                                  74
#define MISSING_BPR_SEGMENT                                  75
#define MISSING_TRN_SEGMENT                                  76
#define MISSING_CUR_SEGMENT                                  77
#define MISSING_REF_SEGMENT                                  78
#define MISSING_DTM_SEGMENT                                  79
#define MISSING_PER_SEGMENT                                  80
#define MISSING_GS_SEGMENT                                   81
#define MISSING_GE_SEGMENT                                   82
#define MISSING_ST_SEGMENT                                   83
#define MISSING_SE_SEGMENT                                   84
#define MISSING_N1_SEGMENT                                   85
#define MISSING_N4_SEGMENT                                   86
#define MISSING_N3_SEGMENT                                   87
#define MISSING_LX_SEGMENT                                   88
#define MISSING_LQ_SEGMENT                                   89
#define INVALID_REPITITON_SEPARATOR                          90


