module EDI835
  class ClaimPayment

    attr_reader :remittance

    include EDI835::HasAdjustments

    def initialize(claim_loop, _remittance)
      raise ArgumentError, "Initialization requires a CLP object" unless claim_loop.is_a?(ChooChoo::CLP)
      @root = claim_loop
      @remittance = _remittance
    end

    def claim_number
      @claim_number ||= root.strip(:CLP01)
    end

    def payment_type_code
      @payment_type_code ||= root.strip(:CLP02)
    end

    def billed_amount
      @billed_amount ||= root.money(:CLP03)
    end

    def amount
      @amount ||= root.money(:CLP04)
    end

    def patient_responsibility_amount
      @patient_responsibility_amount ||= root.money(:CLP05)
    end

    def payer_claim_number
      @payer_claim_number ||= root.strip(:CLP07)
    end

    def is_crossed_over
      !crossed_over_payer.null_segment?
    end

    def patient_last_name
      @patient_last_name ||= patient.upper(:NM103)
    end

    def patient_first_name
      @patient_first_name ||= patient.upper(:NM104)
    end

    def patient_middle_initial
      @patient_middle_initial ||= patient.upper(:NM105)
    end

    def member_number
      @member_number ||= patient.strip(:NM109)
    end

    def primary_insured_last_name
      @primary_insured_last_name ||= primary_insured.upper(:NM103)
    end

    def primary_insured_first_name
      @primary_insured_first_name ||= primary_insured.upper(:NM104)
    end

    def primary_insured_middle_name
      @primary_insured_middle_name ||= primary_insured.upper(:NM105)
    end

    def primary_insured_number
      @primary_insured_number ||= primary_insured.strip(:NM109)
    end

    def rendering_provider_last_name
      @rendering_provider_last_name ||= if rendering_provider_entity_type == EDI835::PERSON
        rendering_provider.upper(:NM103)
      end
    end

    def rendering_provider_organization_name
      @rendering_provider_organization_name ||= if rendering_provider_entity_type == EDI835::ORGANIZATION
        rendering_provider.upper(:NM103)
      end
    end

    def rendering_provider_entity_type
      @rendering_provider_entity_type ||= rendering_provider.strip(:NM102)
    end

    def rendering_provider_first_name
      @rendering_provider_first_name ||= rendering_provider.upper(:NM104)
    end

    def rendering_provider_middle_name
      @rendering_provider_middle_name ||= rendering_provider.upper(:NM105)
    end

    def npi
      @npi ||= rendering_provider.upper(:NM109)
    end

    def crossed_over_payer_name
      @crossed_over_payer_name ||= crossed_over_payer.strip(:NM103, length: 56)
    end

    def crossover_sender_number
      @crossover_sender_number ||=  if crossed_over_payer.upper(:NM108) == EDI835::NM1_PI
        crossed_over_payer.strip(:NM109, length: 30)
      end
    end

    def billing_provider_secondary_number2
      @billing_provider_secondary_number2 ||= claim_ref_1G_0B.strip(:REF02)
    end

    def service_details
      @service_details ||= root.children(:SVC).map do |svc|
        EDI835::ServiceDetail.new(svc, self)
      end
    end

    def inpatient_adjudications
      root.children(:MIA)
    end

    def outpatient_adjudications
      root.children(:MOA)
    end

    def crossed_over_payer
      @crossed_over_payer ||= root.first_or_null(:NM101, EDI835::CROSSOVER)
    end

    def approved
      @approved ||= root.first_or_null(:AMT01, EDI835::APPROVED_AMOUNT).money(:AMT02)
    end

    def billing_provider_secondary_number2
      @billing_provider_secondary_number2 ||= claim_ref_1G_0B.strip(:REF02)
    end

    private

    attr_reader :root

    def patient
      @patient ||= root.first(:NM101, EDI835::PATIENT) || root.first(:NM101, EDI835::CORRECTED_INSURED) || ChooChoo::NullSegment.new(EDI835::Document)
    end

    def primary_insured
      @primary_insured ||= root.first(:NM101, EDI835::INSURED_OR_SUBSCRIBER) || ChooChoo::NullSegment.new(EDI835::Document)
    end

    def rendering_provider
      @rendering_provider ||= root.first(:NM101, EDI835::RENDERING_PROVIDER) || ChooChoo::NullSegment.new(EDI835::Document)
    end

    def claim_ref_1G_0B
      @claim_ref_1G_0B ||= root.first(:REF01, EDI835::UPIN) || root.first(:REF01, EDI835::STATE_NUMBER) || ChooChoo::NullSegment.new(EDI835::Document)
    end
  end
end