module ChooChoo
  class Segment
    
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
      _c_descendants(names, 1)
    end

    def descendant!(name)
      names = prepare_names([name])
      assert_one { _c_descendants(names, 2) }
    end

    def descendants(*names)
      names = prepare_names(names)
      _c_descendants(names, -1)
    end

    def child(name)
      names = prepare_names([name])
      _c_children(names, 1)
    end

    def child!(name)
      names = prepare_names([name])
      assert_one { _c_children(names, 2) }
    end

    def children(*names)
      names = prepare_names(names)
      _c_children(names, -1)
    end

    def where(sym, val)
      _where(sym, val, -1)
    end

    def first(sym,val)
      _where(sym, val, 1)
    end

    def first!(sym,val)
      assert_one { _where(sym, val, 2) }
    end

    def errors?
      _errors?
    end

    def errors
      _errors
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

    private

    def assert_one
      result = yield
      if result.length != 1
        raise AssertedValueNotFound, "No singular element of name #{sym} with value #{val} exists."
      else
        result.first
      end
    end

    def _where(sym, val, limit)
      sym.to_s =~ ChooChoo.segment_regex
      name = prepare_names([$1]).first
      name ? _c_where(name, sym.to_s, val, limit) : []
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