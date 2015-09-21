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