module ChooChoo
  class EDI835

    def initialize(isas)
      @isa_segments = isas
    end

    def to_s
      to_json
    end

    def to_json(*args)
      Oj.dump(isa_segments)
    end

    def to_xml
      Ox.dump(isa_segments)
    end

    def isa_segments
      @isa_segments
    end

    def isa_segment_count
      isa_segments.length
    end

  end
end