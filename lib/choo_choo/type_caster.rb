module ChooChoo
  module TypeCaster

    def self.apply_methods(val, methods)
      methods = [methods].flatten.compact
      methods.each do |sym|
        meth = sym.to_s
        next unless val.respond_to?(meth)
        val = val.send(meth)
      end
      val
    end

    def self.key_cache
      @key_cache ||= {}.with_indifferent_access
    end

    def assign(obj)
      recorder = AssignmentRecorder.new(instance)
      recorder.each_assignment do |assignment|
        assign_type, meth, ele, options = assignment
        val = case assign_type
        when :boolean then boolean(ele, options)
        when :integer then integer(ele, options)
        when :string then string(ele, options)
        when :date then date(ele, options)
        when :decimal then decimal(ele, options)
        else raise ArgumentError, "not a valid assign_type"
        end

        val = ChooChoo::TypeCaster.apply_methods(val, options[:apply])

        obj.send("#{meth}=", val)
      end

      recorder.each_setter do |delayed_setter|
        meth = delayed_setter.first
        obj.send(meth, *delayed_setter[1..-1])
      end
    end

    private

    def extract(key)
      ChooChoo::TypeCaster.key_cache[key] ||= key.to_s.upcase
      key = ChooChoo::TypeCaster.key_cache[key]
      key =~ ChooChoo.segment_regex
      target_segment = $1

      if name == target_segment || target_segment.nil?
        send(key)
      else
        child!($1).send(key)
      end
    end

    def boolean(key, options)
      rtn = extract(key)
      return options[:default] if rtn.nil? && options.key?(:default)
      !!(rtn.to_s =~ /true/i)
    end

    def integer(key, options)
      rtn = extract(key)
      return options[:default] if rtn.nil? && options.key?(:default)
      rtn.to_i
    end

    def string(key, options)
      rtn = extract(key)
      return options[:default] if rtn.nil? && options.key?(:default)
      return unless rtn
      options.key?(:length) && rtn.length > options[:length].to_i ? rtn.to(options[:length].to_i - 1) : rtn
    end

    def date(key, options)
      rtn = extract(key)
      return options[:default] if rtn.nil?
      return if rtn !~ /^\d+\/\d+\/\d+$/
      if rtn =~ /^(\d{2})\/(\d{2})\/(\d{4})$/
        return Date.parse("#{$3}/#{$1}/#{$2}")
      end
      Date.parse(rtn) rescue nil
    end

    def decimal(key, options)
      rtn = extract(key)
      return options[:default] if rtn.nil? && options.key?(:default)
      rtn = BigDecimal.new(rtn.to_s)
      truncation = options[:truncation] || :floor
      precision = options.key?(:precision) ? options[:precision].to_i : nil

      precision ? rtn.send(truncation, *[precision].compact) : rtn
    end
  end
end