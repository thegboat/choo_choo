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

    def find_claim(claim_number)
      clp = isa.first!(:CLP01, claim_number)
      claim = EDI835::ClaimPayment.new(clp, remittance)
      claim
    end

    def remittance
      @remittance ||= EDI835::Remittance.new(isa)
    end

    def claim_payments
      @claim_payments ||= remittance.map(&:claim_payments)
    end
    
    def  provider_level_adjustments
      provider_level_adjustments ||= remittance.map(&:provider_level_adjustments)
    end

    def service_details
      @service_details ||= claim_payments.flat_map(&:service_details)
    end

    def inpatient_adjudications
      @inpatient_adjudications ||= claim_payments.flat_map(&:inpatient_adjudications)
    end

    def outpatient_adjudications
      @outpatient_adjudications ||= claim_payments.flat_map(&:outpatient_adjudications)
    end

  end
end