require 'stupidedi'

class ChooChoo::Parser

  def initialize(file)
    @input = file
  end

  def self.config
    @config ||= Stupidedi::Config.hipaa
  end

  def parse

  end

  private

  def _parser
    @_parser ||= Stupidedi::Builder::StateMachine.build(self.class.config)
  end


end