module ChooChoo
  module DocumentNode

    def self.included(base)
      methods = method_builder
      base.class_eval(methods.join("\n"))
    end

    def self.document_types
      [ChooChoo::EDI835]
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
      _c_descendants(names, 2)
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
      _c_children(names, 2)
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
      result = _where(sym, val, 2)
      len = result.length
      if len != 1
        raise AssertedValueNotFound, "No singular element of name #{sym} with value #{val} exists."
      else
        result.first
      end
    end

    private

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
      case document_type
      when "835" then EDI835.valid_segments
      else raise Exception
      end
    end

    def self.method_builder
      methods = document_types.inject({}) do |result, obj|
        hash = obj.valid_document_nodes
        hash.keys.each do |key|

          if hash[key].is_a?(Fixnum)
            1.upto(hash[key]) do |n|
              funcname = "#{key}#{n.to_s.rjust(2,'0')}"
              result[funcname] ||= []
              result[funcname] << obj.document_type
            end
          else
            hash[key].each do |item|
              if item.is_a?(Fixnum)
                funcname = "#{key}#{item.to_s.rjust(2,'0')}"
                result[funcname] ||= []
                result[funcname] << obj.document_type
              elsif item.is_a?(Range)
                item.each do |n|
                funcname = "#{key}#{n.to_s.rjust(2,'0')}"
                result[funcname] ||= []
                result[funcname] << obj.document_type
                end
              else
                el = item.keys.first
                cm = item.values.first
                1.upto(cm).each do |n|
                  funcname = "#{key}#{el.to_s.rjust(2,'0')}_#{n.to_s.rjust(2,'0')}"
                  result[funcname] ||= []
                  result[funcname] << obj.document_type
                end
              end
            end
          end
        end

        result
      end

      methods.keys.map do |funcname|
        funcname =~ ChooChoo.segment_regex
        segname = $1
        docs = methods[funcname].inspect.to_s
        %{
            def #{funcname}
              raise ChooChoo::MethodNotImplemented, "no method #{funcname} for Document type } +'#{document_type}' + %{" if !#{docs}.include?(document_type)
              raise ChooChoo::MethodNotImplemented, "no method #{funcname} for Segment } + '#{name}' + %{"  if name != :#{segname}
              get_property('#{funcname}')
            end
        }
      end
    end
  end
end