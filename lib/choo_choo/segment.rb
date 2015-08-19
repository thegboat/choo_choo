module ChooChoo
  class Segment

    include ChooChoo::DocumentNode
    
    def parent
      _c_parent
    end

    
  end
end