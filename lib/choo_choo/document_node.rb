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

    def descendants(*names)
      names = prepare_names(names)
      _c_descendants(names)
    end

    def children(*names)
      names = prepare_names(names)
      _c_children(names)
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
                item.values.each do |n|
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
        segname = funcname.gsub(/[0-9_]+$/, '')
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