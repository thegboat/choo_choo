module ChooChoo
  class InterchangeLoop
    include ChooChoo::DocumentNode

    def errors?
      _errors?
    end

    def errors
      _errors
    end

    def humanized_errors
      _errors.map do |code|
        case code
        when "UNKNOWN_ERROR" then "An unknown error has occurred."
        when "ISA_SEGMENT_NOT_DETECTED_FIRST" then "ISA segment was not detected first."
        when "INVALID_COMPONENT_SEPARATOR" then "Either no component separator was found or it was not of length one."
        else errorMessageHandler(code)
        end
      end.compact
    end

    private 

    def errorMessageHandler(code)
      if code =~ /INVALID_(\w+)_SEGMENT/
        "An unexpected #{$1} segment found."
      elsif code =~ /WRONG_NUMBER_OF_ELEMENTS_FOR_(\w+)_SEGMENT/
        "Incorrect number of elements found for #{$1} segment."
      elsif code =~ /MISSING_(\w+)_SEGMENT/
        "#{$1} segment is missing."
      else
        raise ChooChoo::UnhandledParserError, "#{code} is not an expected ChooChoo::Parser error type"
      end
    end


  end
end


