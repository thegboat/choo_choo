require 'choo_choo/edi_835/document'
require 'choo_choo/edi_835/segments/amt'
require 'choo_choo/edi_835/segments/bpr'
require 'choo_choo/edi_835/segments/cas'
require 'choo_choo/edi_835/segments/clp'
require 'choo_choo/edi_835/segments/cur'
require 'choo_choo/edi_835/segments/dtm'
require 'choo_choo/edi_835/segments/ge'
require 'choo_choo/edi_835/segments/gs'
require 'choo_choo/edi_835/segments/iea'
require 'choo_choo/edi_835/segments/isa'
require 'choo_choo/edi_835/segments/lq'
require 'choo_choo/edi_835/segments/lx'
require 'choo_choo/edi_835/segments/mia'
require 'choo_choo/edi_835/segments/moa'
require 'choo_choo/edi_835/segments/n1'
require 'choo_choo/edi_835/segments/n3'
require 'choo_choo/edi_835/segments/n4'
require 'choo_choo/edi_835/segments/nm1'
require 'choo_choo/edi_835/segments/per'
require 'choo_choo/edi_835/segments/plb'
require 'choo_choo/edi_835/segments/qty'
require 'choo_choo/edi_835/segments/rdm'
require 'choo_choo/edi_835/segments/ref'
require 'choo_choo/edi_835/segments/se'
require 'choo_choo/edi_835/segments/st'
require 'choo_choo/edi_835/segments/svc'
require 'choo_choo/edi_835/segments/trn'
require 'choo_choo/edi_835/segments/ts2'
require 'choo_choo/edi_835/segments/ts3'

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