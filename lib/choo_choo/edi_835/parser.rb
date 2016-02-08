module EDI835
  class Parser < ChooChoo::Parser

    def self.parse(file_or_string)
      parser = new(file_or_string)
      parser.parse
    end

    def parse
      _parse {|isa| _c_parse_835(isa) }
    end
  end
end