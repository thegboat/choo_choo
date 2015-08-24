

require "stringio"
require "edi_parsing"
# require "oj"
# require "ox"

module ChooChoo

  def self.segment_regex
    @segment_regex ||= /^([A-Z1-9]{2,3})/
  end

  require "choo_choo/version"
  require "choo_choo/parser"
  require "choo_choo/edi_835"
  require "choo_choo/document_node"
  require "choo_choo/interchange_loop"
  require "choo_choo/segment"
  require "choo_choo/exceptions"
end
