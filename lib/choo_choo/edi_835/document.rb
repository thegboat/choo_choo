module EDI835
  class Document < ChooChoo::Document

    def self.name
      "835"
    end

    def self.valid_segments
      @valid_segments ||= Set.new(_valid_segments.flat_map {|i| [i,i.to_s]}).freeze
    end

    def self._valid_segments
      [
        :ISA, :BPR, :TRN, :CUR, :DTM, :PER, :MIA, :REF, :CAS, 
        :IEA, :QTY, :SVC, :CLP, :PLB, :TS3, :TS2, :MOA, :RDM, 
        :LX, :LQ, :N1, :N3, :N4, :GS, :ST, :GE, :SE, :NM1, 
        :AMT
      ]
    end

  end
end