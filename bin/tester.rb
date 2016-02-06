require 'fileutils'
FileUtils.cp('/Users/gradygriffin/dev/choo_choo/ext/choo_choo_ext/choo_choo_ext.bundle', '/Users/gradygriffin/dev/choo_choo/lib/choo_choo_ext.bundle')



require_relative "../spec/spec_helper"

doc = EDI835::Parser.parse(ChooChoo.test_string).isa.descendant(:CLP).first!(:NM101, 'QC')