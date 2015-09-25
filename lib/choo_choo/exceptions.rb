module ChooChoo

  class MethodNotImplemented < StandardError
  end

  class UnhandledParserError < StandardError
  end

  class AssertedValueNotFound < StandardError
  end

  class MultipleChildrenFound < StandardError
  end

  class MethodImplementationRequired < StandardError
  end
end