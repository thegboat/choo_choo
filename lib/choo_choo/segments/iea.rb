module ChooChoo
  class IEA < Segment

    def IEA01
      _c_get_property(1, 0)
    end
    
    def IEA02
      _c_get_property(2, 0)
    end
    
  end
end
