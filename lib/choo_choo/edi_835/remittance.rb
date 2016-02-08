module EDI835
  class Remittance

    def initialize(isa)
      raise ArgumentError, "Initialization requires a ISA object" unless isa.is_a?(ChooChoo::ISA)
      @interchange_loop = isa
    end

    def inspect
      to_s
    end

    def payment_method_code
      @payment_method_code ||= bpr.upper(:BPR04)
    end

    def check_number
      @check_number ||= trn.strip(:TRN02)
    end

    def check_date
      @check_date ||= bpr.date(:BPR16)
    end

    def check_amount
      @check_amount ||= bpr.money(:BPR02)
    end

    def pay_to_npi
      @pay_to_npi ||= if payee_loop.upper(:N103) == EDI835::N1_XX
        payee_loop.strip(:N104)
      end
    end

    def tax_id
      @tax_id ||= if payee_loop.upper(:N103) == EDI835::N1_FI
        payee_loop.strip(:N104)
      elsif payee_tj_ref
        payee_tj_ref.strip(:REF02)
      end
    end

    def billing_provider_secondary_number1
      @billing_provider_secondary_number1 ||= payee_ref_PQ_0B.strip(:REF02) if payee_ref_PQ_0B
    end

    def pay_to_provider_secondary_number1
      if payee_tj_ref
        tax_id
      end
    end

    def billing_provider_name
      @billing_provider_name ||= payee_loop.upper(:N102)
    end
    alias :pay_to_provider_name :billing_provider_name

    def pay_to_provider_identification_code
      @pay_to_provider_identification_code ||= payee_loop.strip(:N104)
    end

    def billing_provider_address_line1
      @billing_provider_address_line1 ||= payee_loop.upper(:N301)
    end
    alias :pay_to_provider_address_line1 :billing_provider_address_line1

    def billing_provider_address_line2
      @billing_provider_address_line2 ||= payee_loop.upper(:N302)
    end
    alias :pay_to_provider_address_line2 :billing_provider_address_line2

    def billing_provider_address_city
      @billing_provider_address_city ||= payee_loop.upper(:N401)
    end
    alias :pay_to_provider_address_city :billing_provider_address_city

    def billing_provider_address_state
      @billing_provider_address_state ||= payee_loop.upper(:N402)
    end
    alias :pay_to_provider_address_state :billing_provider_address_state

    def billing_provider_address_zip_code
      @billing_provider_address_zip_code ||= payee_loop.upper(:N403)
    end
    alias :pay_to_provider_address_zip_code :billing_provider_address_zip_code

    def payer_code
      @payer_code ||= payer_loop.strip(:N101)
    end

    def payer_name
      @payer_name ||= payer_loop.upper(:N102)
    end

    def payer_address_line1
      @payer_address_line1 ||= payer_loop.upper(:N301)
    end

    def payer_address_line2
      @payer_address_line2 ||= payer_loop.upper(:N302)
    end

    def payer_city
      @payer_city ||= payer_loop.upper(:N401)
    end

    def payer_state
      @payer_state ||= payer_loop.upper(:N402)
    end

    def payer_zip_code
      @payer_zip_code ||= payer_loop.upper(:N403)
    end

    def payer_sender_number
      @payer_sender_number ||= payer_ref_2U.strip(:REF02) if payer_ref_2U
    end

    def claim_payments
      @claim_payments ||= transaction_loop.descendants(:CLP).map do |clp|
        EDI835::ClaimPayment.new(clp, self)
      end
    end

    def provider_level_adjustments
      @summaries ||= transaction_loop.children(:PLB).map do |plb|
        EDI835::ProviderLevelAdjustment.new(plb, self)
      end
    end

    private

    attr_reader :interchange_loop

    def interchange_trailer
      @interchange_trailer ||= interchange_loop.child!(:IEA)
    end

    def functional_loop
      @functional_loop ||= interchange_loop.child!(:GS)
    end

    def functional_trailer
      @functional_trailer ||= functional_loop.child!(:GE)
    end

    def transaction_loop
      @transaction_loop ||= functional_loop.child!(:ST)
    end

    def transaction_trailer
      @transaction_trailer ||= transaction_loop.child!(:SE)
    end

    def payer_loop
      @payer_loop ||= transaction_loop.child!(:N1)
    end

    def payee_loop
      @payee_loop ||= payer_loop.child!(:N1)
    end

    def claim_header
      @claim_header ||= payee_loop.child!(:LX)
    end

    def bpr
      @bpr ||= transaction_loop.child!(:BPR)
    end

    def trn
      @trn ||= transaction_loop.child!(:TRN)
    end

    def payee_tj_ref
      @payee_tj_ref ||= payee_loop.first(:REF01, EDI835::EIN)
    end

    def payer_ref_2U
      @payer_ref_2U ||= payer_loop.first(:REF01, EDI835::PAYER_ID)
    end

    def payee_ref_PQ_0B
      @payee_ref_PQ_0B ||= payee_loop.first(:REF01, EDI835::PAYEE_ID) || payee_loop.first(:REF01, EDI835::STATE_NUMBER)
    end
  end
end