require 'fileutils'
FileUtils.cp('./edi_parsing.bundle', '../../lib/edi_parsing.bundle')

require_relative "../spec/spec_helper"

ChooChoo.children
#ChooChoo.to_hash