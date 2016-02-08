
require "bigdecimal"
require "stringio"
require "choo_choo_ext"
# require "oj"
# require "ox"
require "choo_choo/version"
require "choo_choo/parser"
require "choo_choo/document"
require "choo_choo/segment"
require "choo_choo/null_segment"
require "choo_choo/exceptions"

require "choo_choo/edi_835/edi_835"

module ChooChoo

  MONEY_ZERO      = BigDecimal('0.00').freeze
  EMPTY_STRING    = "".freeze
  DECIMAL_ZERO    = MONEY_ZERO
  SEGMENT_REGEX   = /^([A-Z][A-Z][A-Z1-9]|[A-Z][A-Z]|[A-Z][1-9])/.freeze
  PROPERTY_REGEX  = /^#{SEGMENT_REGEX}([0-9]{2})(|_([0-9]{2}))$/.freeze
  SHEBANG         = '!'.freeze
  EMPTY_HASH      = {}.freeze
  EMPTY_JSON      = '{}'.freeze

  def self.sample
    %{ISA*00* *00* *33*54704 *ZZ*PB000022*110726*1248*U*00501*000000209*0*P*>~GS*HP*54704*0001124*20110726*23562041*344*X*005010X221A1~ST*835*001~BPR*H*0*C*NON************20110726~TRN*1*0000010305*1234567890~DTM*405*20110706~N1*PR*INDEPENDENCE BLUE CROSS~N3*1901 MARKET STREET~N4*PHILADELPHIA*PA*19103~PER*CX*IBC Service Desk*TE*2152414200~PER*BL*Nancy Martyniuk*TE*2152414673~N1*PE*CHESTNUT HILL REHAB HOSPITAL*XX*NPI Number~N3*ATTENTION JOE SAMPLE*8835 MARKET AVENUE~N4*PHILADELPHIA*PA*191182718~REF*PQ*Legacy Provider Number~REF*TJ*Federal Tax ID~LX*1~CLP*9999999*4*385.20*0*385.20*12*999999999999*13*2~NM1*QC*1*SAMPLE*JOAN****MI*ZAR123456789~NM1*IL*1*SAMPLE*HARRY*J***MI*ZAR123456789~NM1*74*1*SAMPLE*HARRY*M***C*123456789~NM1*82*2*JEANES HOSPITAL*****XX*NPI Number~REF*CE*OUTPATIENT-PPO~REF*1A*Legacy Number/Federal Tax ID~DTM*232*20110225~DTM*233*20110225~DTM*036*20081031~SVC*HC>97001*385.20*0*0424*1*~DTM*472*20031125~CAS*PR*27*385.20*0~REF*6R*1~PLB*NPI Number*20111231*PI:PRE-PAYMENT AMOUNT*6173.4~SE*33*001~GE*1*58~IEA*1*000000209~}
  end

end
