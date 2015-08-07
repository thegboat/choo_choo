module Choo
  class Segment < Hash


    def children
      self[:_children]
    end
  end
end