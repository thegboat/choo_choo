require "stringio"

module ChooChoo
  class Parser

    attr_reader :stream

    def initialize(file_or_string)
      @stream = file_or_string.is_a?(String) ? file_or_string.dup : file_or_string.read
    end

    def self.parse
      raise MethodImplementationRequired
    end

    def parse
      raise MethodImplementationRequired
    end

    def _parse
      stream.delete!("\000")
      stream.strip!
      stream.gsub!(/~\s+/,'~')
      start = stream =~ /ISA\*/
      yield(stream[start..-1])
    end

    # def split
    #   str_buffer = ''
    #   obj_buffer = []
    #   until stream.eof?
    #     str_buffer << stream.gets("~IEA")
    #     trailer = stream.gets("ISA").to_s
    #     str_buffer << (trailer =~ /ISA\*$/ ? trailer[0..-5] : trailer)
    #     str_buffer.delete!("\000")
    #     str_buffer.gsub!(/~\s+/,'~')
    #     str_buffer.gsub!("**", "*#{empty}*")
    #     isa = yield(str_buffer)
    #     obj_buffer << isa
    #     str_buffer = trailer[-4..-1]
    #   end
    #   obj_buffer
    # end
  end
end