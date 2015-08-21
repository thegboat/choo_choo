//
//  edi_parsing_errors.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"


VALUE getErrors(parser_t *parser){
  VALUE result = rb_ary_new();
  char error[60];
  short errorNumber;

  for(short i=0; i<parser->errorCount;i++){
    errorNumber = parser->errors[i];
    switch(errorNumber){
      case UNKNOWN_ERROR :
        strcpy(error,"UNKNOWN_ERROR");
        break;
      case ISA_SEGMENT_NOT_DETECTED_FIRST :
        strcpy(error,"ISA_SEGMENT_NOT_DETECTED_FIRST");
        break;
      case INVALID_COMPONENT_SEPARATOR :
        strcpy(error,"INVALID_COMPONENT_SEPARATOR");
        break;
      case INVALID_ISA_SEGMENT :
        strcpy(error,"INVALID_ISA_SEGMENT");
        break;
      case INVALID_IEA_SEGMENT :
        strcpy(error,"INVALID_IEA_SEGMENT");
        break;
      case INVALID_TS3_SEGMENT :
        strcpy(error,"INVALID_TS3_SEGMENT");
        break;
      case INVALID_TS2_SEGMENT :
        strcpy(error,"INVALID_TS2_SEGMENT");
        break;
      case INVALID_CLP_SEGMENT :
        strcpy(error,"INVALID_CLP_SEGMENT");
        break;
      case INVALID_CAS_SEGMENT :
        strcpy(error,"INVALID_CAS_SEGMENT");
        break;
      case INVALID_NM1_SEGMENT :
        strcpy(error,"INVALID_NM1_SEGMENT");
        break;
      case INVALID_MIA_SEGMENT :
        strcpy(error,"INVALID_MIA_SEGMENT");
        break;
      case INVALID_MOA_SEGMENT :
        strcpy(error,"INVALID_MOA_SEGMENT");
        break;
      case INVALID_AMT_SEGMENT :
        strcpy(error,"INVALID_AMT_SEGMENT");
        break;
      case INVALID_QTY_SEGMENT :
        strcpy(error,"INVALID_QTY_SEGMENT");
        break;
      case INVALID_SVC_SEGMENT :
        strcpy(error,"INVALID_SVC_SEGMENT");
        break;
      case INVALID_PLB_SEGMENT :
        strcpy(error,"INVALID_PLB_SEGMENT");
        break;
      case INVALID_RDM_SEGMENT :
        strcpy(error,"INVALID_RDM_SEGMENT");
        break;
      case INVALID_BPR_SEGMENT :
        strcpy(error,"INVALID_BPR_SEGMENT");
        break;
      case INVALID_TRN_SEGMENT :
        strcpy(error,"INVALID_TRN_SEGMENT");
        break;
      case INVALID_CUR_SEGMENT :
        strcpy(error,"INVALID_CUR_SEGMENT");
        break;
      case INVALID_REF_SEGMENT :
        strcpy(error,"INVALID_REF_SEGMENT");
        break;
      case INVALID_DTM_SEGMENT :
        strcpy(error,"INVALID_DTM_SEGMENT");
        break;
      case INVALID_PER_SEGMENT :
        strcpy(error,"INVALID_PER_SEGMENT");
        break;
      case INVALID_GS_SEGMENT :
        strcpy(error,"INVALID_GS_SEGMENT");
        break;
      case INVALID_GE_SEGMENT :
        strcpy(error,"INVALID_GE_SEGMENT");
        break;
      case INVALID_ST_SEGMENT :
        strcpy(error,"INVALID_ST_SEGMENT");
        break;
      case INVALID_SE_SEGMENT :
        strcpy(error,"INVALID_SE_SEGMENT");
        break;
      case INVALID_N1_SEGMENT :
        strcpy(error,"INVALID_N1_SEGMENT");
        break;
      case INVALID_N4_SEGMENT :
        strcpy(error,"INVALID_N4_SEGMENT");
        break;
      case INVALID_N3_SEGMENT :
        strcpy(error,"INVALID_N3_SEGMENT");
        break;
      case INVALID_LX_SEGMENT :
        strcpy(error,"INVALID_LX_SEGMENT");
        break;
      case INVALID_LQ_SEGMENT :
        strcpy(error,"INVALID_LQ_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_TS3_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_TS3_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_TS2_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_TS2_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_MIA_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_MIA_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_MOA_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_MOA_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_QTY_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_QTY_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_PLB_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_PLB_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_RDM_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_RDM_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_CUR_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_CUR_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT");
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT :
        strcpy(error,"WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT");
        break;
      case MISSING_ISA_SEGMENT :
        strcpy(error,"MISSING_ISA_SEGMENT");
        break;
      case MISSING_IEA_SEGMENT :
        strcpy(error,"MISSING_IEA_SEGMENT");
        break;
      case MISSING_TS3_SEGMENT :
        strcpy(error,"MISSING_TS3_SEGMENT");
        break;
      case MISSING_TS2_SEGMENT :
        strcpy(error,"MISSING_TS2_SEGMENT");
        break;
      case MISSING_CLP_SEGMENT :
        strcpy(error,"MISSING_CLP_SEGMENT");
        break;
      case MISSING_CAS_SEGMENT :
        strcpy(error,"MISSING_CAS_SEGMENT");
        break;
      case MISSING_NM1_SEGMENT :
        strcpy(error,"MISSING_NM1_SEGMENT");
        break;
      case MISSING_MIA_SEGMENT :
        strcpy(error,"MISSING_MIA_SEGMENT");
        break;
      case MISSING_MOA_SEGMENT :
        strcpy(error,"MISSING_MOA_SEGMENT");
        break;
      case MISSING_AMT_SEGMENT :
        strcpy(error,"MISSING_AMT_SEGMENT");
        break;
      case MISSING_QTY_SEGMENT :
        strcpy(error,"MISSING_QTY_SEGMENT");
        break;
      case MISSING_SVC_SEGMENT :
        strcpy(error,"MISSING_SVC_SEGMENT");
        break;
      case MISSING_PLB_SEGMENT :
        strcpy(error,"MISSING_PLB_SEGMENT");
        break;
      case MISSING_RDM_SEGMENT :
        strcpy(error,"MISSING_RDM_SEGMENT");
        break;
      case MISSING_BPR_SEGMENT :
        strcpy(error,"MISSING_BPR_SEGMENT");
        break;
      case MISSING_TRN_SEGMENT :
        strcpy(error,"MISSING_TRN_SEGMENT");
        break;
      case MISSING_CUR_SEGMENT :
        strcpy(error,"MISSING_CUR_SEGMENT");
        break;
      case MISSING_REF_SEGMENT :
        strcpy(error,"MISSING_REF_SEGMENT");
        break;
      case MISSING_DTM_SEGMENT :
        strcpy(error,"MISSING_DTM_SEGMENT");
        break;
      case MISSING_PER_SEGMENT :
        strcpy(error,"MISSING_PER_SEGMENT");
        break;
      case MISSING_GS_SEGMENT :
        strcpy(error,"MISSING_GS_SEGMENT");
        break;
      case MISSING_GE_SEGMENT :
        strcpy(error,"MISSING_GE_SEGMENT");
        break;
      case MISSING_ST_SEGMENT :
        strcpy(error,"MISSING_ST_SEGMENT");
        break;
      case MISSING_SE_SEGMENT :
        strcpy(error,"MISSING_SE_SEGMENT");
        break;
      case MISSING_N1_SEGMENT :
        strcpy(error,"MISSING_N1_SEGMENT");
        break;
      case MISSING_N4_SEGMENT :
        strcpy(error,"MISSING_N4_SEGMENT");
        break;
      case MISSING_N3_SEGMENT :
        strcpy(error,"MISSING_N3_SEGMENT");
        break;
      case MISSING_LX_SEGMENT :
        strcpy(error,"MISSING_LX_SEGMENT");
        break;
      case MISSING_LQ_SEGMENT :
        strcpy(error,"MISSING_LQ_SEGMENT");
        break;
      default: 
        rb_raise(rb_eRuntimeError, "A failure occurred while resolving errors.");
    }
    rb_ary_push(result, rb_str_new_cstr(error));
  }

  return result;
}