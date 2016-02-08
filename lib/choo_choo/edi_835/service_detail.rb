module EDI835
  class ServiceDetail

    include EDI835::HasAdjustments

    SVC01 = 'SVC01'.freeze
    SVC06 = 'SVC06'.freeze

    def initialize(service_loop, claim_loop)
      raise ArgumentError, "Initialization requires a SVC object" unless service_loop.is_a?(ChooChoo::SVC)
      @claim = claim_loop
      @root = service_loop
    end

    def inspect
      to_s
    end

    def min_date_of_service
      @min_date_of_service ||= begin
        segment   = root.first(:DTM01, EDI835::DTM_150) 
        segment ||= root.first(:DTM01, EDI835::DTM_472)
        segment ||= claim.first(:DTM01, EDI835::DTM_232)
        segment ||= claim.first(:DTM01, EDI835::DTM_233)
        segment && segment.date(:DTM02)
      end
    end

    def max_date_of_service
      @max_date_of_service ||= begin
        segment   = root.first(:DTM01, EDI835::DTM_151)
        segment ||= root.first(:DTM01,  EDI835::DTM_472)
        segment ||= claim.first(:DTM01, EDI835::DTM_233)
        segment ||= claim.first(:DTM01, EDI835::DTM_232)
        segment && segment.date(:DTM02)
      end
    end

    def billed_amount
      @billed_amount ||= root.money(:SVC02)
    end

    def approved
      @approved ||= root.first_or_null(:AMT01, EDI835::SERVICE_APPROVED).money(:AMT02)
    end

    def amount
      @amount ||= root.money(:SVC03)
    end

    def charge_number
      @charge_number ||= root.first_or_null(:REF01, EDI835::CHARGE_NUMBER).strip(:REF02)
    end

    def revenue_code
      @revenue_code ||= root.strip(:SVC04)
    end

    def service_units
      @service_units ||= root.integer(:SVC05, default: nil)
    end

    def adjusted_service_units
      @adjusted_service_units ||= root.integer(:SVC07, default: nil)
    end

    def procedure_code
      @procedure_code ||= root.strip("#{procedure_property}_02")
    end

    def adjusted_procedure_code
      @adjusted_procedure_code ||= root.strip("#{adjusted_procedure_property}_02")
    end

    def adjusted_modifier1_code
      @adjusted_modifier1_code ||= root.strip("#{adjusted_procedure_property}_03")
    end

    def adjusted_modifier2_code
      @adjusted_modifier2_code ||= root.strip("#{adjusted_procedure_property}_04")
    end

    def adjusted_modifier3_code
      @adjusted_modifier3_code ||= root.strip("#{adjusted_procedure_property}_05")
    end

    def adjusted_modifier4_code
      @adjusted_modifier4_code ||= root.strip("#{adjusted_procedure_property}_06")
    end

    def modifier1_code
      @modifier1_code ||= root.strip("#{procedure_property}_03")
    end

    def modifier2_code
      @modifier2_code ||= root.strip("#{procedure_property}_04")
    end

    def modifier3_code
      @modifier3_code ||= root.strip("#{procedure_property}_05")
    end

    def modifier4_code
      @modifier4_code ||= root.strip("#{procedure_property}_06")
    end

    def remark_code1
      @remark_code1 ||= remark_codes[0] && remark_codes[0].strip(:LQ02)
    end
        
    def remark_code2
      @remark_code2 ||= remark_codes[1] && remark_codes[1].strip(:LQ02)
    end

    def remark_code3
      @remark_code3 ||= remark_codes[2] && remark_codes[2].strip(:LQ02)
    end
    
    def remark_code4
      @remark_code4 ||= remark_codes[3] && remark_codes[3].strip(:LQ02)
    end
    
    def remark_code5
      @remark_code5 ||= remark_codes[4] && remark_codes[4].strip(:LQ02)
    end

    private

    attr_reader :root, :claim

    def remark_codes
      root.children(:LQ)
    end

    def adjusted_procedure_property
      @adjusted_procedure_property ||= procedure_property == SVC01 ? SVC06 : SVC01
    end

    def procedure_property
      @procedure_property ||= if root.upper(:SVC01_01) == EDI835::SVC_HC || root.upper(:SVC06_01) != EDI835::SVC_HC
        SVC01
      else
        SVC06
      end
    end
  end
end