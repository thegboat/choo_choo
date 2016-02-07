
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

end
