module ChooChoo
  class NullSegment
    attr_reader :document_type

    def inspect
      to_s
    end

    def initialize(doc_type)
      @document_type = doc_type
    end

    def null_segment?
      true
    end

    def name
      ChooChoo::EMPTY_STRING
    end

    def to_h
      ChooChoo::EMPTY_HASH
    end
    alias :to_hash :to_h
    
    def to_json
      Oj.dump(to_hash)
    end

    def exists?(sym,val)
      false
    end

    def first_or_null
      self
    end

    def null_cast(key, options)
      Segment.parse_property_key(key, document_type)
      return options[:default] if options.key?(:default)
      yield
    end

    def cannot_assert(*args)
      raise MethodNotImplemented, "NULL Segment can not assert."
    end
    alias :descendant! :cannot_assert 
    alias :child! :cannot_assert 
    alias :first! :cannot_assert
    alias :first! :cannot_assert
    alias :integer! :cannot_assert
    alias :int! :cannot_assert
    alias :money! :cannot_assert
    alias :string! :cannot_assert
    alias :str! :cannot_assert
    alias :raw! :cannot_assert
    alias :upper! :cannot_assert
    alias :up! :cannot_assert
    alias :lower! :cannot_assert
    alias :low! :cannot_assert
    alias :strip! :cannot_assert
    alias :decimal! :cannot_assert
    alias :boolean! :cannot_assert
    alias :bool! :cannot_assert
    alias :date! :cannot_assert

    def null(*args)
      nil
    end
    alias :parent :null
    alias :descendant :null
    alias :child :null
    alias :first :null

    def empty_array(*args)
      ChooChoo::FALSE
    end
    alias :children :empty_array 
    alias :descendants :empty_array 
    alias :where :empty_array 

    def no_error_info
      raise MethodNotImplemented, "NULL Segment can not return error information."
    end
    alias :errors? :no_error_info 
    alias :errors :no_error_info 
    alias :humanized_errors :no_error_info 

    def string_cast(key, options)
      options[:default] || ChooChoo::EMPTY_STRING
    end

    def get_property(key)
      ChooChoo::EMPTY_STRING
    end

    def boolean(key, options = {})
      null_cast(key, options) { false }
    end
    alias :bool :boolean

    def integer(key, options = {})
      null_cast(key, options) { 0 }
    end
    alias :int :integer

    def upper(key, options = {})
      null_cast(key, options) { nil }
    end
    alias :up :upper

    def lower(key, options = {})
      null_cast(key, options) { nil }
    end
    alias :low :lower

    def string(key, options = {})
      null_cast(key, options) { ChooChoo::EMPTY_STRING }
    end
    alias :str :string
    alias :raw :string

    def strip(key, options = {})
      null_cast(key, options) { nil }
    end

    def date(key, options = {})
      null_cast(key, options) { nil }
    end

    def money(key, options = {})
      null_cast(key, options) { ChooChoo::MONEY_ZERO }
    end

    def decimal(key, options = {})
      null_cast(key, options) { ChooChoo::DECIMAL_ZERO }
    end
    alias :dec :decimal
  end
end