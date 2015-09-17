module ChooChoo
  class RDM < Segment

    def RDM01
      _c_get_property(1, 0)
    end
    
    def RDM02
      _c_get_property(2, 0)
    end
    
    def RDM03
      _c_get_property(3, 0)
    end
    
  end
end
