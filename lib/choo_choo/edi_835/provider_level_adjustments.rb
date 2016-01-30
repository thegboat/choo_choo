module EDI835
  class ProviderLevelAdjustment

    attr_reader :remittance

    include EDI835::HasAdjustments

    def initialize(plb, _remittance)
      raise ArgumentError, "Initialization requires a CLP object" unless plb.is_a?(EDI835::PLB)
      @root = plb
      @remittance = _remittance
    end

    def provider_adjustment1
      @provider_adjustment1 ||= root.strip(:PLB03_01)
    end

    def provider_adjustment2
      @provider_adjustment2 ||= root.strip(:PLB05_01)
    end

    def provider_adjustment3
      @provider_adjustment3 ||= root.strip(:PLB07_01)
    end

    def provider_adjustment4
      @provider_adjustment4 ||= root.strip(:PLB09_01)
    end

    def provider_adjustment5
      @provider_adjustment5 ||= root.strip(:PLB11_01)
    end

    def provider_adjustment6
      @provider_adjustment6 ||= root.strip(:PLB13_01)
    end

    def amount1
      @amount1 ||= root.strip(:PLB04)
    end

    def amount2
      @amount2 ||= root.strip(:PLB06)
    end

    def amount3
      @amount3 ||= root.strip(:PLB08)
    end

    def amount4
      @amount4 ||= root.strip(:PLB10)
    end

    def amount5
      @amount5 ||= root.strip(:PLB12)
    end

    def amount6
      @amount6 ||= root.strip(:PLB14)
    end

    def payer_claim_number1
      @payer_claim_number1 ||= root.upper(:PLB03_02)
    end

    def payer_claim_number2
      @payer_claim_number2 ||= root.upper(:PLB05_02)
    end

    def payer_claim_number3
      @payer_claim_number3 ||= root.upper(:PLB07_02)
    end

    def payer_claim_number4
      @payer_claim_number4 ||= root.upper(:PLB09_02)
    end

    def payer_claim_number5
      @payer_claim_number5 ||= root.upper(:PLB11_02)
    end

    def payer_claim_number6
      @payer_claim_number6 ||= root.upper(:PLB13_02)
    end

    private

    attr_reader :root
  end
end