module ChooChoo
  class Document

    def initialize
      @segment_cache = {}
    end

    def self.name
      raise MethodImplementationRequired
    end

    def self.valid_segments
      raise MethodImplementationRequired
    end

    def inspect
      to_s
    end

    def errors?
      _c_errors?
    end

    def errors
      _c_errors
    end

    def isa_segment
      _c_isa_segment
    end
    alias :interchange_loop :isa_segment 
    alias :interchange :isa_segment 
    alias :root :isa_segment 
    alias :isa :isa_segment 
  end
end