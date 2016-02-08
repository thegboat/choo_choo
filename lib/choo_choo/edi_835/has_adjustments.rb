module EDI835
  module HasAdjustments

    def deductible
      @deductible ||= patient_responsibility.map do |segment| 
        segment.strip(:CAS02) == EDI835::DEDUCTIBLE ? segment.money(:CAS03) : ChooChoo::MONEY_ZERO
      end.sum
    end

    def co_payment
      @co_payment ||= patient_responsibility.map do |segment| 
        segment.strip(:CAS02) == EDI835::CO_PAYMENT ? segment.money(:CAS03) : ChooChoo::MONEY_ZERO
      end.sum
    end

    def co_insurance
      @co_insurance ||= patient_responsibility.map do |segment| 
        segment.strip(:CAS02) == EDI835::CO_INSURANCE ? segment.money(:CAS03) : ChooChoo::MONEY_ZERO
      end.sum
    end

    def adjustment_code1
      @adjustment_code1 ||= adjustments[0] && adjustments[0].upper(:CAS02, length: 5)
    end

    def adjustment_code2
      @adjustment_code2 ||= adjustments[1] && adjustments[1].upper(:CAS02, length: 5)
    end

    def adjustment_code3
      @adjustment_code3 ||= adjustments[2] && adjustments[2].upper(:CAS02, length: 5)
    end

    def adjustment_code4
      @adjustment_code4 ||= adjustments[3] && adjustments[3].upper(:CAS02, length: 5)
    end

    def adjustment_code5
      @adjustment_code5 ||= adjustments[4] && adjustments[4].upper(:CAS02, length: 5)
    end

    def adjustment_qualifier_code1
      @adjustment_qualifier_code1 ||= adjustments[0] && adjustments[0].upper(:CAS01, length: 2)
    end

    def adjustment_qualifier_code2
      @adjustment_qualifier_code2 ||= adjustments[1] && adjustments[1].upper(:CAS01, length: 2)
    end

    def adjustment_qualifier_code3
      @adjustment_qualifier_code3 ||= adjustments[2] && adjustments[2].upper(:CAS01, length: 2)
    end

    def adjustment_qualifier_code4
      @adjustment_qualifier_code4 ||= adjustments[3] && adjustments[3].upper(:CAS01, length: 2)
    end

    def adjustment_qualifier_code5
      @adjustment_qualifier_code5 ||= adjustments[4] && adjustments[4].upper(:CAS01, length: 2)
    end

    def adjustment_amount_code1
      @adjustment_amount_code1 ||= adjustments[0] ? adjustments[0].money(:CAS03) : ChooChoo::MONEY_ZERO 
    end

    def adjustment_amount_code2
      @adjustment_amount_code2 ||= adjustments[1] ? adjustments[1].money(:CAS03) : ChooChoo::MONEY_ZERO
    end

    def adjustment_amount_code3
      @adjustment_amount_code3 ||= adjustments[2] ? adjustments[2].money(:CAS03) : ChooChoo::MONEY_ZERO
    end

    def adjustment_amount_code4
      @adjustment_amount_code4 ||= adjustments[3] ? adjustments[3].money(:CAS03) : ChooChoo::MONEY_ZERO
    end

    def adjustment_amount_code5
      @adjustment_amount_code5 ||= adjustments[4] ? adjustments[4].money(:CAS03) : ChooChoo::MONEY_ZERO
    end
    
    def withhold
      @withhold ||= withholds.map { |segment| segment.money(:CAS03) }.sum
    end

    def adjustment
      @adjustment ||= adjustment_amount_code1 + adjustment_amount_code2 + adjustment_amount_code3 + adjustment_amount_code4 + adjustment_amount_code5
    end
    alias :insurance_adjustment_amount :adjustment

    protected

    def withholds
      adjustments.select do |segment|
        segment.upper(:CAS01) != EDI835::PATIENT_RESPONSIBILITY && EDI835::WITHHOLD_CODES.include?(segment.strip(:CAS02))
      end
    end

    def adjustments
      @adjustments ||= root.children(:CAS).reject do |segment| 
        EDI835::PR_CODES.include?(segment.strip(:CAS02)) || segment.strip(:CAS01).nil? || segment.strip(:CAS02).nil?
      end
    end

    def patient_responsibility
      @pr ||= root.children(:CAS).select do |segment| 
        EDI835::PR_CODES.include?(segment.strip(:CAS02))
      end
    end
  end
end
