require "choo_choo_parsing"
require "choo_choo/version"
require "choo_choo/remittance_object"
require "choo_choo/charge_level_object"
require "choo_choo/check_level_object"
require "choo_choo/claim_level_object"

module ChooChoo
  def self.parse_remittance(filestring)
    _parse_remittance(filestring, filestring.length)
  end
end
