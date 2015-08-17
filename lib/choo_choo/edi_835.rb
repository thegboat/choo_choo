module ChooChoo
  class EDI835

    def initialize(isas)
      @isa_segments = isas
    end

    def self.valid_segments
      @valid_segments ||= Set.new([
        :ISA, :BPR, :TRN, :CUR, :DTM, :PER, :MIA, :REF, :CAS,
        :IEA, :QTY, :SVC, :CLP, :PLB, :TS3, :TS2, :MOA, :RDM,
        :LX, :LQ, :N1, :N3, :N4, :GS, :ST, :GE, :SE, :NM1, :AMT
      ])
    end

    def isa_segments
      @isa_segments
    end

    def isa_segment_count
      isa_segments.length
    end

  end
end