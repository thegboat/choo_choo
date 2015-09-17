module ChooChoo
  class ST < Segment

    def ST01
      _c_get_property(1, 0)
    end
    
    def ST02
      _c_get_property(2, 0)
    end
    
    def ST03
      _c_get_property(3, 0)
    end
    
  end
end
