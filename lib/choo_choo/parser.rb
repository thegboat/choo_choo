require "stringio"

module ChooChoo
  class Parser

    attr_reader :stream

    def initialize(file_or_string)
      @stream = file_or_string.is_a?(String) ? StringIO.new(file_or_string) : file_or_string
    end

    def self.parse_835(file_or_string)
      parser = new(file_or_string)
      parser.parse_835
    end

    def parse_835
      isas = split {|isa_segment| _c_parse_835(isa_segment) }
      EDI835.new(isas)
    end

    def split
      str_buffer = ''
      obj_buffer = []
      until stream.eof?
        str_buffer << stream.gets("~IEA")
        trailer = stream.gets("ISA").to_s
        str_buffer << (trailer =~ /ISA\*$/ ? trailer[0..-5] : trailer)
        str_buffer.delete!("\000")
        isa = yield(str_buffer)
        obj_buffer << isa
        str_buffer = trailer[-4..-1]
      end
      obj_buffer
    end
  end
end