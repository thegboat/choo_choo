require 'fileutils'
FileUtils.cp('./edi_parsing.bundle', '../../lib/edi_parsing.bundle')

require_relative "../spec/spec_helper"

    string = "ISA*extra_element**00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<"
    isa = edit_line(ChooChoo.test_string, 0, string)
# ChooChoo.to_hash