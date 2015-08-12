module ChooChoo
  class EDI835

    def initialize(isas)
      @isa_segments = isas
    end

    def isa_segments
      @isa_segments
    end

    def isa_segment_count
      isa_segments.length
    end

  end
end