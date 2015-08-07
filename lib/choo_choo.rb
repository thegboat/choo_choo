require "edi_parsing"
require "choo_choo/version"

module ChooChoo

  def self.parse_835(file_string)
    _c_parse_835(file_string)
  end
end
