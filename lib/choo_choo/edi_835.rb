module ChooChoo
  class EDI835

    def initialize(isas)
      @isa_segments = isas
    end

    def self.document_type
      "835"
    end

    def self.valid_segments
      @valid_segments ||= Set.new(valid_document_nodes.keys)
    end

    def self.valid_document_nodes
      {
        ISA: 16,
        BPR: 21,
        TRN: 4,
        CUR: 21,
        DTM: 6,
        PER: 9,
        MIA: 24,
        REF: 4,
        CAS: 19,
        IEA: 2,
        QTY: 4,
        SVC: [{1 => 7}, (2..5), {6 => 8}, 7],
        CLP: 14, 
        PLB: [(1..2), {3 => 2}, 4, {5 => 2}, 6, {7 => 2}, 8, {9 => 2}, 10, {11 => 2}, 12, {13 => 2}, 14],
        TS3: 19,
        TS2: 24,
        MOA: 9,
        RDM: 3,
        LX: 1,
        LQ: 2,
        N1: 6,
        N3: 2,
        N4: 6,
        GS: 8,
        ST: 3,
        GE: 2,
        SE: 2,
        NM1: 11,
        AMT: 3
      }
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

