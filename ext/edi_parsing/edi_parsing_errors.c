//
//  edi_parsing_errors.c
//  choo_choo_parser
//
//  Created by Grady Griffin on 8/3/15.
//  Copyright (c) 2015 Grady Griffin. All rights reserved.
//

#include "edi_parsing.h"

const char* globalErrorMessages = {
  // ISA_SEGMENT_NOT_DETECTED_FIRST
  "There was no required ISA segment found.",
  // MORE_THAN_ONE_ISA_SEGMENT_FOUND
  "More than one ISA segment was found.",
  // WRONG_NUMBER_OF_ELEMENTS_FOR_ISA
  "The ISA segment should contain exactly 16 elements.",
  // MISSING_GS_SEGMENT
  "There was no required GS segment found within the ISA segment.",            
  // MISSING_ST_SEGMENT
  "There was no required ST segment found within the GS segment.",             
  // INVALID_SE_SEGMENT 
  "An unexpected SE segment was found.",                  
  // INVALID_ST_SEGMENT 
  "An unexpected ST segment was found.",               
  // INVALID_N1_SEGMENT 
  "An unexpected N1 segment was found.",               
  // INVALID_LX_SEGMENT    
  "An unexpected LX segment was found.",            
  // INVALID_CLP_SEGMENT   
  "An unexpected CLP segment was found.",            
  // INVALID_SVC_SEGMENT   
  "An unexpected SVC segment was found.",            
  // INVALID_GE_SEGMENT   
  "An unexpected GE segment was found.",             
  // INVALID_IEA_SEGMENT   
  "An unexpected IEA segment was found.",            
  // WRONG_NUMBER_OF_ELEMENTS_FOR_SE 
  "The SE segment should contain exactly 2 elements.",
  // WRONG_NUMBER_OF_ELEMENTS_FOR_GE 
  "The GE segment should contain exactly 2 elements.",
  // WRONG_NUMBER_OF_ELEMENTS_FOR_IEA
  "The IEA segment should contain exactly 2 elements.",
  // MISSING_SE_SEGMENT
  "There was no required SE trailer segment found for ST segment.",                
  // MISSING_GE_SEGMENT 
  "There was no required GE trailer segment found for GS segment.",              
  // WRONG_NUMBER_OF_ELEMENTS_FOR_GS 
  "The GS segment should contain exactly 8 elements.",
  // WRONG_NUMBER_OF_ELEMENTS_FOR_ST 
  "The ST segment should contain 2 to 3 elements.",
  // INVALID_PAYER_LOOP
  "An unexpected N1 segment was found.",                 
  // INVALID_GS_SEGMENT    
  "An unexpected GS segment was found.",           
  // MISSING_PAYER_LOOP   
  "A N1 segment was expected but not found.",            
  // MISSING_IEA_SEGMENT 
  "There was no required IEA trailer segment found for ISA segment.",              
  // INVALID_COMPONENT_SEPARATOR     
  "The component separator of ISA16 is missing or invalid."
}

VALUE getErrors(parser_t *parser){
  VALUE ary = rb_new_ary();
  for(short i=0; i<parser.errorCount; i++){
    rb_ary_push(ary, rb_str_new_cstr(globalErrorMessages[parser.errors[i]]));
  }

  return ary;
}