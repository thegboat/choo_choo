require 'choo_choo/edi_835/document'
require 'choo_choo/segments/amt'
require 'choo_choo/segments/bpr'
require 'choo_choo/segments/cas'
require 'choo_choo/segments/clp'
require 'choo_choo/segments/cur'
require 'choo_choo/segments/dtm'
require 'choo_choo/segments/ge'
require 'choo_choo/segments/gs'
require 'choo_choo/segments/iea'
require 'choo_choo/segments/isa'
require 'choo_choo/segments/lq'
require 'choo_choo/segments/lx'
require 'choo_choo/segments/mia'
require 'choo_choo/segments/moa'
require 'choo_choo/segments/n1'
require 'choo_choo/segments/n3'
require 'choo_choo/segments/n4'
require 'choo_choo/segments/nm1'
require 'choo_choo/segments/per'
require 'choo_choo/segments/plb'
require 'choo_choo/segments/qty'
require 'choo_choo/segments/rdm'
require 'choo_choo/segments/ref'
require 'choo_choo/segments/se'
require 'choo_choo/segments/st'
require 'choo_choo/segments/svc'
require 'choo_choo/segments/trn'
require 'choo_choo/segments/ts2'
require 'choo_choo/segments/ts3'

module EDI835
  class Parser < ChooChoo::Parser

    def self.parse(file_or_string)
      parser = new(file_or_string)
      parser.parse
    end

    def parse
      isas = split {|isa_segment| _c_parse_835(isa_segment) }
      EDI835::Document.new(isas)
    end
  end
end