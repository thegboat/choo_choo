module ChooChoo
  class Document

    def initialize(isa)
      @isa_segment = isa
    end

    def self.name
      raise MethodImplementationRequired
    end

    def self.valid_segments
      raise MethodImplementationRequired
    end

    def has_errors?
      isa_segment.errors?
    end

    def isa_segment
      @isa_segment
    end
    alias :interchange_loop :isa_segment 
    alias :interchange :isa_segment 
    alias :root :isa_segment 
    alias :isa :isa_segment 
  end
end