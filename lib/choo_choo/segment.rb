module ChooChoo
  class Segment

    def document_type
      @document_type.dup
    end

    def to_h
      to_hash
    end
    
    def to_json
      Oj.dump(to_hash)
    end
  end
end