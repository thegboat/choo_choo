module EDI835
  class OutpatientAdjudication

    attr_reader :claim_payment

    def initialize(moa_segment, @claim_payment)
      raise ArgumentError, "Initialization requires a MOA object" unless moa_segment.is_a?(ChooChoo::MOA)
      @root = moa_segment
      @claim_payment = _claim_payment
    end

    def reimbursement_rate
      root.money(:MOA01)
    end

    def claim_payable_amount
      root.money(:MOA02)
    end

    def claim_esrd_payment
      root.money(:MOA08)
    end

    def non_payable_professional_amount
      root.money(:MOA09)
    end

    def remittance_remark_code1
      root.str(:MOA03)
    end

    def remittance_remark_code2
      root.str(:MOA04)
    end

    def remittance_remark_code3
      root.str(:MOA05)
    end

    def remittance_remark_code4
      root.str(:MOA06)
    end

    def remittance_remark_code5
      root.str(:MOA07)
    end

    private

    attr_accessor :root
  end
end