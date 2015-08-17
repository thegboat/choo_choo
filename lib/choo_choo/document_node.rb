module ChooChoo
  module DocumentNode
    def to_h
      to_hash
    end
    
    def to_json
      Oj.dump(to_hash)
    end

    def descendants(*names)
      names = prepare_names(names)
      _c_descendants(names)
    end

    def children(*names)
      names = prepare_names(names)
      segments = _c_children(names)
      segments.select! { |segment| names.include?(segment.name.to_sym) } unless names.empty?
      segments
    end

    def name
      @_name
    end

    def document_type
      @_document_type
    end

    private

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
      case document_type
      when "835" then EDI835.valid_segments
      else raise Exception
      end
    end
  end
end