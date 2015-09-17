
require "bigdecimal"
require "stringio"
require "edi_parsing"
# require "oj"
# require "ox"
require "choo_choo/version"
require "choo_choo/parser"
require "choo_choo/document"
require "choo_choo/segment"
require "choo_choo/exceptions"

require "choo_choo/edi_835/parser"

module ChooChoo

  def self.segment_regex
    @segment_regex ||= /^([A-Z][A-Z][A-Z1-9]|[A-Z][A-Z]|[A-Z][1-9])/
  end

  def self.property_regex
    @segment_regex ||= /^#{segment_regex}([0-9]{2})(|_([0-9]{2}))$/
  end

end
