##
# This class represents an arbitrary segment from a EDI file.
module ChooChoo
  class Segment

    def inspect
      to_s
    end

    ##
    # always returns true; supplies common interface with NullSegment
    def null_segment?
      false
    end

    ##
    # returns the class type of the document from which this segment originates
    def document_type
      @document_type ||= document.class
    end

    ##
    # returns the instance of the document from which this segment originates
    def document
      _c_doc
    end
    alias :doc :document

    ##
    # returns the root interchange loop segment of the document
    def isa
      _c_isa_segment
    end
    alias :root :isa
    alias :isa_segment :isa

    ##
    # returns the segment's name as a symbol
    def name
      @name ||= _c_name
    end

    ##
    # returns the parent segment; nil when the segment is ISA
    def parent
      _c_parent
    end

    ##
    # returns the hash representation of segment
    def to_hash
      _c_to_hash
    end
    alias :to_h :to_hash

    ##
    # returns the json representation of segment    
    def to_json
      Oj.dump(to_hash)
    end

    ##
    # returns the first segment that is a descendant matching the given segment name
    def descendant(seg_name)
      names = prepare_names([seg_name])
      _c_descendants(names, 1).first
    end

    ##
    # returns the first segment that is a descendant matching the given segment name
    # throws an error if the exact matches is not one
    def descendant!(seg_name)
      names = prepare_names([seg_name])
      assert_one { _c_descendants(names, 2) }.first
    end

    ##
    # returns the all descendants of the segment
    # or if one are more names are given the descendants of the segment that have that name
    def descendants(*names)
      names = prepare_names(names)
      _c_descendants(names, -1)
    end

    ##
    # returns the first segment that is a child matching the given segment name
    def child(name)
      names = prepare_names([name])
      _c_children(names, 1).first
    end

    ##
    # returns the first segment that is a child matching the given segment name
    #throws an error if the exact matches is not one
    def child!(seg_name)
      names = prepare_names([seg_name])
      assert_one { _c_children(names, 2) }.first
    end

    ##
    # returns the all children of the segment
    # or if one are more names are given the children of the segment that have that name
    def children(*names)
      names = prepare_names(names)
      _c_children(names, -1)
    end

    ##
    # returns the all descendants of the segment
    # where the property value sym is equal to the value val
    def where(sym, val)
      _where(sym, val, -1)
    end

    ##
    # returns the true if a segment descendant with property value sym is equal to the value val
    # returns false otherwise 
    def exists?(sym,val)
      _exists?(sym, val)
    end

    ##
    # returns the first descendant of the segment
    # where the property value sym is equal to the value val
    def first(sym,val)
      _where(sym, val, 1).first
    end

    ##
    # returns the first descendant of the segment
    # where the property value sym is equal to the value val
    # if no such descendant exists returns a null segment
    def first_or_null(sym,val)
      _where(sym, val, 1).first || ChooChoo::NullSegment.new(document_type)
    end

    ##
    # returns the first descendant of the segment
    # where the property value sym is equal to the value val
    #throws an error if the exact matches is not one
    def first!(sym,val)
      assert_one { _where(sym, val, 2) }.first
    end

    ##
    # returns a hunanized version of parser errors 
    # this method is meant to be overridden for custom error rendering
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

    ##
    # cast the value at key of segment or at key of a singular child to a boolean
    # if multiple children with key exists, an error is raised
    # returns true if the property value if matches the expression /true/i
    # return false otherwise
    def boolean(key, options = {})
      cast(:boolean, key, options)
    end
    alias :bool :boolean

    ##
    # cast the value at key of segment or at key of a singular child to a integer
    # if multiple children with key exists, an error is raised
    # returns Fixnum value using Object#to_i or property string
    def integer(key, options = {})
      cast(:integer, key, options)
    end
    alias :int :integer

    ##
    # mutates the value at key of segment or at key of a singular child
    # if multiple children with key exists, an error is raised
    # returns String instance using String#upcase and String#strip
    def upper(key, options = {})
      cast(:string, key, options.merge(apply: [:upcase, :strip], default: nil))
    end
    alias :up :upper

    ##
    # mutates the value at key of segment or at key of a singular child
    # if multiple children with key exists, an error is raised
    # returns String instance using String#downcase and String#strip
    def lower(key, options = {})
      cast(:string, key, options.merge(apply: [:downcase, :strip], default: nil))
    end
    alias :low :lower

    ##
    # returns the value at key of segment or at key of a singular child
    # if multiple children with key exists, an error is raised
    # if the key is value of segment this is equivalent to send(key)
    def string(key, options = {})
      cast(:string, key, options)
    end
    alias :str :string
    alias :raw :string

    ##
    # mutates the value at key of segment or at key of a singular child
    # if multiple children with key exists, an error is raised
    # returns String instance using String#strip
    def strip(key, options = {})
      cast(:string, key, options.merge(apply: :strip, default: nil))
    end

    ##
    # cast the value at key of segment or at key of a singular child to date
    # if multiple children with key exists, an error is raised
    # returns Date instance using Date::parse on property string
    def date(key, options = {})
      cast(:date, key, options)
    end

    ##
    # cast the value at key of segment or at key of a singular child to BigDecimal
    # if multiple children with key exists, an error is raised
    # returns BigDecimal instance using BigDecimal::new on property string, truncated to precision 2
    def money(key, options = {})
      cast(:decimal, key, options.merge(precision: 2))
    end

    ##
    # cast the value at key of segment or at key of a singular child to BigDecimal
    # if multiple children with key exists, an error is raised
    # returns BigDecimal instance using BigDecimal::new on property string
    def decimal(key, options = {})
      cast(:decimal, key, options)
    end
    alias :dec :decimal

    ##
    # cast the value at key of segment or at key of a singular child to a boolean
    # if delegated to children and there is not exactly on match, an error is raised
    # returns true if the property value if matches the expression /true/i
    # return false otherwise
    def boolean!(key, options = {})
      boolean(key, options.merge(assert: true))
    end
    alias :bool! :boolean!

    ##
    # cast the value at key of segment or at key of a singular child to a integer
    # if delegated to children and there is not exactly on match, an error is raised
    # returns Fixnum value using Object#to_i or property string
    def integer!(key, options = {})
      integer(key, options.merge(assert: true))
    end
    alias :int! :integer!

    ##
    # mutates the value at key of segment or at key of a singular child
    # if delegated to children and there is not exactly on match, an error is raised
    # returns String instance using String#upcase and String#strip
    def upper!(key, options = {})
      upper(key, options.merge(assert: true))
    end
    alias :up! :upper!

    ##
    # mutates the value at key of segment or at key of a singular child
    # if delegated to children and there is not exactly on match, an error is raised
    # returns String instance using String#downcase and String#strip
    def lower!(key, options = {})
      lower(key, options.merge(assert: true))
    end
    alias :low! :lower!

    ##
    # returns the value at key of segment or at key of a singular child
    # if delegated to children and there is not exactly on match, an error is raised
    # if the key is value of segment this is equivalent to send(key)
    def string!(key, options = {})
      string(key, options.merge(assert: true))
    end
    alias :str! :string!
    alias :raw! :string!

    ##
    # mutates the value at key of segment or at key of a singular child
    # if delegated to children and there is not exactly on match, an error is raised
    # returns String instance using String#strip
    def strip!(key, options = {})
      strip(key, options.merge(assert: true))
    end

    ##
    # cast the value at key of segment or at key of a singular child to date
    # if delegated to children and there is not exactly on match, an error is raised
    # returns Date instance using Date::parse on property string
    def date!(key, options = {})
      date(key, options.merge(assert: true))
    end

    ##
    # cast the value at key of segment or at key of a singular child to BigDecimal
    # if delegated to children and there is not exactly on match, an error is raised
    # returns BigDecimal instance using BigDecimal::new on property string, truncated to precision 2
    def money!(key, options = {})
      money(key, options.merge(assert: true))
    end

    ##
    # cast the value at key of segment or at key of a singular child to BigDecimal
    # if delegated to children and there is not exactly on match, an error is raised
    # returns BigDecimal instance using BigDecimal::new on property string
    def decimal!(key, options = {})
      decimal(key, options.merge(assert: true))
    end
    alias :dec! :decimal!

    protected

    def self.apply_methods(val, methods)
      methods = [methods].flatten.compact
      methods.each do |sym|
        meth = sym.to_s
        next unless val.respond_to?(meth)
        if meth[-1] == ChooChoo::SHEBANG
          val.send(meth)
        else
          val = val.send(meth)
        end
      end
      val
    end

    def self.parse_property_key(string, document_type)
      string =~ ChooChoo::PROPERTY_REGEX
      raise InvalidPropertyName if $1.nil? || $2.nil?
      raise InvalidElementName unless document_type.valid_segments.include?($1)
      [$1, $2.to_i, $4.to_i]
    end

    private

    def parse_property_key(string)
      self.class.parse_property_key(string, document_type)
    end

    def cast(assign_type, key, options)
      val = extract(key, options[:assert])
      return options[:default] if options.key?(:default) && val.to_s.empty?
      return options[:blank] if options.key?(:blank) && val =~ /^\s+$/
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

    def extract(key, assert = false)
      if respond_to?(key)
        send(key)
      else
        seg_name, element, component = parse_property_key(key)
        names = prepare_names([seg_name])
        list = _c_children(names, 2)
        if list.length == 1 
          list.first.send(key.to_sym)
        elsif list.length > 1 
          raise MultipleChildrenFound, "can not cast from multiple children."
        elsif assert
          assert_one { list }
        else
          ChooChoo::EMPTY_STRING
        end
      end
    end

    def _boolean(val, options)
      !!(val.strip =~ /true/i)
    end

    def _integer(val, options)
      val.to_i
    end

    def _string(val, options)
      return nil if val.nil?
      val = val.to_s
      return val if val.empty?
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
      val_s = val.to_s
      return ChooChoo::DECIMAL_ZERO if val_s.empty?
      val = BigDecimal.new(val_s)
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
      seg_name, element, component = parse_property_key(sym.to_s)
      seg_name = prepare_names([seg_name]).first
      seg_name ? _c_where(seg_name, element, component, val, limit) : []
    end

    def _exists?(sym, val)
      seg_name, element, component = parse_property_key(sym.to_s)
      seg_name = prepare_names([seg_name]).first
      seg_name ? _c_exists?(seg_name, element, component, val) : false
    end

    def prepare_names(list)
      list = list.flatten
      list.map! do |item|
        item = item.to_s
        item.upcase!
        item
      end
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