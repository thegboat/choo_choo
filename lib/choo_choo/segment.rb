module ChooChoo
  class Segment

    def name
      _name
    end
    
    def parent
      _c_parent
    end

    def to_h
      to_hash
    end
    
    def to_json
      Oj.dump(to_hash)
    end

    def descendant(name)
      names = prepare_names([name])
      _c_descendants(names, 1).first
    end

    def descendant!(name)
      names = prepare_names([name])
      assert_one { _c_descendants(names, 2) }.first
    end

    def descendants(*names)
      names = prepare_names(names)
      _c_descendants(names, -1)
    end

    def child(name)
      names = prepare_names([name])
      _c_children(names, 1).first
    end

    def child!(name)
      names = prepare_names([name])
      assert_one { _c_children(names, 2) }.first
    end

    def children(*names)
      names = prepare_names(names)
      _c_children(names, -1)
    end

    def where(sym, val)
      _where(sym, val, -1)
    end

    def exists?(sym,val)
      _exists?(sym, val)
    end

    def first(sym,val)
      _where(sym, val, 1).first
    end

    def first!(sym,val)
      assert_one { _where(sym, val, 2) }.first
    end

    def errors?
      _c_errors?
    end

    def errors
      _c_errors
    end

    def get_property(key)
      unless key.starts_with?(_name_s) && args = ChooChoo.parse_property_key(key)
        raise MethodNotImplemented, "Method #{key} not implemented for #{_name_s} segment."
      end
      _c_get_property(*args[1..-1])
    end

    def humanized_errors
      _errors.map do |code|
        case code
        when "UNKNOWN_ERROR" then "An unknown error has occurred."
        when "ISA_SEGMENT_NOT_DETECTED_FIRST" then "ISA segment was not detected first."
        when "INVALID_COMPONENT_SEPARATOR" then "Either no component separator was found or it was not of length one."
        else errorMessageHandler(code)
        end
      end.compact
    end

    def boolean(key, options = {})
      cast(:boolean, key, options)
    end
    alias :bool :boolean

    def integer(key, options = {})
      cast(:integer, key, options)
    end
    alias :int :integer

    def upper(key, options = {})
      cast(:string, key, options.merge(apply: [:upcase, :strip]))
    end
    alias :up :upper

    def lower(key, options = {})
      cast(:string, key, options.merge(apply: [:downcase, :strip]))
    end
    alias :low :lower

    def string(key, options = {})
      cast(:string, key, options)
    end
    alias :str :string
    alias :raw :string

    def strip(key, options = {})
      cast(:string, key, options.merge(apply: :strip))
    end

    def date(key, options = {})
      cast(:date, key, options)
    end

    def money(key, options = {})
      cast(:decimal, key, options.merge(precision: 2))
    end

    def decimal(key, options = {})
      cast(:decimal, key, options)
    end
    alias :dec :decimal

    protected

    def self.apply_methods(val, methods)
      methods = [methods].flatten.compact
      methods.each do |sym|
        meth = sym.to_s
        next unless val.respond_to?(meth)
        val = val.send(meth)
      end
      val
    end

    private

    def parse_property_key(string)
      string =~ ChooChoo.property_regex
      $1.nil? ? nil : [$1, $2.to_i, $4.to_i]
    end

    def _name
      @name ||= _c_name
    end

    def _name_s
      @_name_s ||= name.to_s
    end

    def cast(assign_type, key, options)
      val = extract(key)
      options[:default] ||= nil
      options[:blank] ||= nil
      return options[:default] if val.to_s.empty?
      return options[:blank] if val =~ /^\s+$/
      casted = case assign_type
      when :boolean then _boolean(val, options)
      when :integer then _integer(val, options)
      when :string then _string(val, options)
      when :date then _date(val, options)
      when :decimal then _decimal(val, options)
      else raise ArgumentError, "not a valid assign_type"
      end

      casted = self.class.apply_methods(casted, options[:apply]) if options[:apply]
      casted
    end

    def extract(key)
      if respond_to?(key)
        send(key)
      else
        key =~ ChooChoo.segment_regex
        child!($1).get_property(key)
      end
    end

    def _boolean(val, options)
      !!(val.strip =~ /true/i)
    end

    def _integer(val, options)
      val.to_i
    end

    def _string(val, options)
      val = val.to_s
      options.key?(:length) && val.length > options[:length].to_i ? val.to(options[:length].to_i - 1) : val
    end

    def _date(val, options)
      return if val !~ /^(\d+\/\d+\/\d+|\d{8}|\d{4}-\d{2}\d{2})$/
      if val =~ /^(\d{2})\/(\d{2})\/(\d{4})$/
        return Date.parse("#{$3}/#{$1}/#{$2}")
      end
      Date.parse(val) rescue nil
    end

    def _decimal(val, options)
      val = BigDecimal.new(val.to_s)
      truncation = options[:truncation] || :floor
      precision = options.key?(:precision) ? options[:precision].to_i : nil

      precision ? val.send(truncation, *[precision].compact) : val
    end

    def assert_one
      result = yield
      if result.length != 1
        raise AssertedValueNotFound, "No singular element exists."
      end
      result
    end

    def _where(sym, val, limit)
      name, element, component = parse_property_key(sym.to_s)
      name = prepare_names([name]).first
      name ? _c_where(name, element, component, val, limit) : []
    end

    def _exists?(sym, val)
      name, element, component = parse_property_key(sym.to_s)
      name = prepare_names([name]).first
      name ? _c_exists?(name, element, component, val) : false
    end

    def prepare_names(list)
      list = list.flatten
      list.map! do |item|
        item = item.to_s
        item.upcase!
        item
      end
      list.select! {|item| valid_segments.include?(item.to_sym) }
      list
    end

    def valid_segments
      document_type.valid_segments
    end

    def errorMessageHandler(code)
      if code =~ /INVALID_(\w+)_SEGMENT/
        "An unexpected #{$1} segment found."
      elsif code =~ /WRONG_NUMBER_OF_ELEMENTS_FOR_(\w+)_SEGMENT/
        "Incorrect number of elements found for #{$1} segment."
      elsif code =~ /MISSING_(\w+)_SEGMENT/
        "#{$1} segment is missing."
      else
        raise ChooChoo::UnhandledParserError, "#{code} is not an expected ChooChoo::Parser error type"
      end
    end
    
  end
end