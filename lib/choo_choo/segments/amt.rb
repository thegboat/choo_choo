module ChooChoo
  class AMT < Segment

    def AMT01
      _c_get_property(1, 0)
    end
    
    def AMT02
      _c_get_property(2, 0)
    end
    
    def AMT03
      _c_get_property(3, 0)
    end
    
  end
end
