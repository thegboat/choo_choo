require 'set'
require 'choo_choo/edi_835/has_adjustments'
require 'choo_choo/edi_835/document'
require 'choo_choo/edi_835/parser'
require 'choo_choo/edi_835/remittance'
require 'choo_choo/edi_835/service_detail'
require 'choo_choo/edi_835/claim_payment'

module EDI835
  UPIN                    = '1G'.freeze
  PAYER_ID                = '2U'.freeze
  STATE_NUMBER            = '0B'.freeze
  PAYEE_ID                = 'PQ'.freeze
  EIN                     = 'TJ'.freeze
  RENDERING_PROVIDER      = '82' .freeze
  INSURED_OR_SUBSCRIBER   = 'IL'.freeze
  PATIENT                 = 'QC'.freeze
  CORRECTED_INSURED       = '74'.freeze
  CROSSOVER               = 'TT'.freeze
  DEDUCTIBLE              = '1'.freeze
  CO_INSURANCE            = '2'.freeze
  CO_PAYMENT              = '3'.freeze
  PERSON                  = '1'.freeze
  ORGANIZATION            = '2'.freeze
  PATIENT_RESPONSIBILITY  = 'PR'.freeze
  CHARGE_NUMBER           = '6R'.freeze
  N1_XX                   = 'XX'.freeze
  N1_FI                   = 'FI'.freeze
  NM1_PI                  = 'PI'.freeze
  AMT_AU                  = 'AU'.freeze

  SVC_HC                  = 'HC'.freeze
  DTM_150                 = '150'.freeze
  DTM_472                 = '472'.freeze
  DTM_232                 = '232'.freeze
  DTM_233                 = '232'.freeze
  DTM_151                 = '151'.freeze
  AMT_B6                  = 'B6'.freeze

  PR_CODES                = Set.new([DEDUCTIBLE, CO_INSURANCE, CO_PAYMENT])
  WITHHOLD_CODES          = Set.new(%w{104 253 105 245 144})
end