module EDI835
  class Document < ChooChoo::Document

    def self.name
      "835"
    end

    def self.valid_segments
      @valid_segments ||= Set.new([
        :ISA, :BPR, :TRN, :CUR, :DTM, :PER, :MIA, :REF, :CAS, 
        :IEA, :QTY, :SVC, :CLP, :PLB, :TS3, :TS2, :MOA, :RDM, 
        :LX, :LQ, :N1, :N3, :N4, :GS, :ST, :GE, :SE, :NM1, 
        :AMT
      ]).freeze
    end

  end
end