module ChooChoo
  class Document

    def initialize(isas)
      @isa_segments = isas
    end

    def self.name
      raise MethodImplementationRequired
    end

    def self.valid_segments
      raise MethodImplementationRequired
    end

    def has_errors?
      isa_segments.any? {|isa| isa.errors? }
    end

    def isa_segments_with_errors
      isa_segments.select {|isa| isa.errors? }
    end

    def isa_segments_without_errors
      isa_segments.reject {|isa| isa.errors? }
    end

    def isa_segments
      @isa_segments
    end

    def isa_segment_count
      isa_segments.length
    end
  end
end