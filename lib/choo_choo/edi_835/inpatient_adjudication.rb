module EDI835
  class InpatientAdjudication

    def initialize(mia_segment)
      raise ArgumentError, "Initialization requires a MIA object" unless mia_segment.is_a?(EDI835::MIA)
      @root = mia_segment
    end

    def visit_count
      root.integer(:MIA01, default: nil)
    end

    def operating_outlier_count
      root.integer(:MIA02, default: nil)
    end

    def psychiatric_days_count
      root.integer(:MIA03, default: nil)
    end

    def report_date_count
      root.integer(:MIA15, default: nil)
    end

    def claim_drg_amount
      root.money(:MIA04)
    end

    def claim_share_amount
      root.money(:MIA06)
    end

    def claim_msp_amount
      root.money(:MIA07)
    end

    def claim_capital_amount
      root.money(:MIA08)
    end

    def claim_fsp_amount
      root.money(:MIA09)
    end

    def claim_hsp_amount
      root.money(:MIA10)
    end

    def claim_dsh_amount
      root.money(:MIA11)
    end

    def old_capital_amount
      root.money(:MIA12)
    end

    def capital_ime_amount
      root.money(:MIA13)
    end

    def operating_hospital_amount
      root.money(:MIA14)
    end

    def operating_federal_amount
      root.money(:MIA16)
    end

    def capital_outlier_amount
      root.money(:MIA17)
    end

    def indirect_teaching_amount
      root.money(:MIA18)
    end

    def non_payable_professional_amount
      root.money(:MIA19)
    end

    def capital_exception_amount
      root.money(:MIA24)
    end

    def remittance_remark_code1
      root.str(:MIA05)
    end

    def remittance_remark_code2
      root.str(:MIA20)
    end

    def remittance_remark_code3
      root.str(:MIA21)
    end

    def remittance_remark_code4
      root.str(:MIA22)
    end

    def remittance_remark_code5
      root.str(:MIA23)
    end

    private

    attr_accessor :root

  end
end