require 'fileutils'
FileUtils.cp('/Users/gradygriffin/dev/choo_choo/ext/choo_choo_ext/choo_choo_ext.bundle', '/Users/gradygriffin/dev/choo_choo/lib/choo_choo_ext.bundle')



require_relative "../spec/spec_helper"
Benchmark.ips do |x|
  x.report("x") { EDI835::Parser.parse(ChooChoo.test_string) }
end