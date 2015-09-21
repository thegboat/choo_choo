module ChooChoo
  class NullSegment

    def name
      ChooChoo::EMPTY_STRING
    end

    def to_h
      ChooChoo::EMPTY_HASH
    end
    
    def to_json
      Oj.dump(to_hash)
    end

    def exists?(sym,val)
      ChooChoo::FALSE
    end

    def first_or_null
      self
    end

    def cannot_assert(*args)
      raise MethodNotImplemented, "NULL Segment can not assert one since it has no descendants."
    end
    alias :descendant! :cannot_assert 
    alias :child! :cannot_assert 
    alias :first! :cannot_assert 

    def null(*args)
      ChooChoo::NULL
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
      !!options[:default]
    end
    alias :bool :boolean

    def integer(key, options = {})
      options[:default].to_i
    end
    alias :int :integer

    def upper(key, options = {})
      string_cast(key, options)
    end
    alias :up :upper

    def lower(key, options = {})
      string_cast(key, options)
    end
    alias :low :lower

    def string(key, options = {})
      string_cast(key, options)
    end
    alias :str :string
    alias :raw :string

    def strip(key, options = {})
      string_cast(key, options)
    end

    def date(key, options = {})
      ChooChoo::NULL
    end

    def money(key, options = {})
      ChooChoo::MONEY_ZERO
    end

    def decimal(key, options = {})
      ChooChoo::DECIMAL_ZERO
    end
    alias :dec :decimal
  end
end