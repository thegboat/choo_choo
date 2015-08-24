require 'fileutils'
FileUtils.cp('./edi_parsing.bundle', '../../lib/edi_parsing.bundle')

require_relative "../spec/spec_helper"

    edi = ChooChoo::Parser.parse_835(ChooChoo.test_string)
    isa = edi.isa_segments.first
    isa.where(:N101, "PR")
# ChooChoo.to_hash