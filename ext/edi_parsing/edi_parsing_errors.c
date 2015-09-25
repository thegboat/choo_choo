//
//  edi_parsing_errors.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"


VALUE getErrors(parser_t *parser){
  VALUE result = rb_ary_new2(parser->errorCount);
  char error[60];
  short errorNumber;

  for(short i=0; i<parser->errorCount;i++){
    errorNumber = parser->errors[i];
    switch(errorNumber){
      case UNKNOWN_ERROR :
        rb_ary_push(result, rb_str_new_cstr("UNKNOWN_ERROR"));
        break;
      case ISA_SEGMENT_NOT_DETECTED_FIRST :
        rb_ary_push(result, rb_str_new_cstr("ISA_SEGMENT_NOT_DETECTED_FIRST"));
        break;
      case INVALID_COMPONENT_SEPARATOR :
        rb_ary_push(result, rb_str_new_cstr("INVALID_COMPONENT_SEPARATOR"));
        break;
      case INVALID_ISA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_ISA_SEGMENT"));
        break;
      case INVALID_IEA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_IEA_SEGMENT"));
        break;
      case INVALID_TS3_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_TS3_SEGMENT"));
        break;
      case INVALID_TS2_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_TS2_SEGMENT"));
        break;
      case INVALID_CLP_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_CLP_SEGMENT"));
        break;
      case INVALID_CAS_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_CAS_SEGMENT"));
        break;
      case INVALID_NM1_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_NM1_SEGMENT"));
        break;
      case INVALID_MIA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_MIA_SEGMENT"));
        break;
      case INVALID_MOA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_MOA_SEGMENT"));
        break;
      case INVALID_AMT_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_AMT_SEGMENT"));
        break;
      case INVALID_QTY_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_QTY_SEGMENT"));
        break;
      case INVALID_SVC_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_SVC_SEGMENT"));
        break;
      case INVALID_PLB_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_PLB_SEGMENT"));
        break;
      case INVALID_RDM_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_RDM_SEGMENT"));
        break;
      case INVALID_BPR_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_BPR_SEGMENT"));
        break;
      case INVALID_TRN_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_TRN_SEGMENT"));
        break;
      case INVALID_CUR_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_CUR_SEGMENT"));
        break;
      case INVALID_REF_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_REF_SEGMENT"));
        break;
      case INVALID_DTM_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_DTM_SEGMENT"));
        break;
      case INVALID_PER_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_PER_SEGMENT"));
        break;
      case INVALID_GS_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_GS_SEGMENT"));
        break;
      case INVALID_GE_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_GE_SEGMENT"));
        break;
      case INVALID_ST_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_ST_SEGMENT"));
        break;
      case INVALID_SE_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_SE_SEGMENT"));
        break;
      case INVALID_N1_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_N1_SEGMENT"));
        break;
      case INVALID_N4_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_N4_SEGMENT"));
        break;
      case INVALID_N3_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_N3_SEGMENT"));
        break;
      case INVALID_LX_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_LX_SEGMENT"));
        break;
      case INVALID_LQ_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("INVALID_LQ_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_TS3_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_TS3_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_TS2_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_TS2_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_MIA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_MIA_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_MOA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_MOA_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_QTY_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_QTY_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_PLB_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_PLB_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_RDM_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_RDM_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_CUR_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_CUR_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT"));
        break;
      case WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT"));
        break;
      case MISSING_ISA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_ISA_SEGMENT"));
        break;
      case MISSING_IEA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_IEA_SEGMENT"));
        break;
      case MISSING_TS3_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_TS3_SEGMENT"));
        break;
      case MISSING_TS2_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_TS2_SEGMENT"));
        break;
      case MISSING_CLP_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_CLP_SEGMENT"));
        break;
      case MISSING_CAS_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_CAS_SEGMENT"));
        break;
      case MISSING_NM1_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_NM1_SEGMENT"));
        break;
      case MISSING_MIA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_MIA_SEGMENT"));
        break;
      case MISSING_MOA_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_MOA_SEGMENT"));
        break;
      case MISSING_AMT_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_AMT_SEGMENT"));
        break;
      case MISSING_QTY_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_QTY_SEGMENT"));
        break;
      case MISSING_SVC_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_SVC_SEGMENT"));
        break;
      case MISSING_PLB_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_PLB_SEGMENT"));
        break;
      case MISSING_RDM_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_RDM_SEGMENT"));
        break;
      case MISSING_BPR_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_BPR_SEGMENT"));
        break;
      case MISSING_TRN_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_TRN_SEGMENT"));
        break;
      case MISSING_CUR_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_CUR_SEGMENT"));
        break;
      case MISSING_REF_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_REF_SEGMENT"));
        break;
      case MISSING_DTM_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_DTM_SEGMENT"));
        break;
      case MISSING_PER_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_PER_SEGMENT"));
        break;
      case MISSING_GS_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_GS_SEGMENT"));
        break;
      case MISSING_GE_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_GE_SEGMENT"));
        break;
      case MISSING_ST_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_ST_SEGMENT"));
        break;
      case MISSING_SE_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_SE_SEGMENT"));
        break;
      case MISSING_N1_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_N1_SEGMENT"));
        break;
      case MISSING_N4_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_N4_SEGMENT"));
        break;
      case MISSING_N3_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_N3_SEGMENT"));
        break;
      case MISSING_LX_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_LX_SEGMENT"));
        break;
      case MISSING_LQ_SEGMENT :
        rb_ary_push(result, rb_str_new_cstr("MISSING_LQ_SEGMENT"));
        break;
      case INVALID_REPITITON_SEPARATOR :
        rb_ary_push(result, rb_str_new_cstr("INVALID_REPITITON_SEPARATOR"));
        break;
      default: 
        rb_raise(rb_eRuntimeError, "A failure occurred while resolving errors.");
    }
  }

  return result;
}