# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'choo_choo/version'

Gem::Specification.new do |spec|
  spec.name          = "choo_choo"
  spec.version       = ChooChoo::VERSION
  spec.authors       = ["Grady Griffin"]
  spec.email         = ["ggriffin@carecloud.com"]

  if spec.respond_to?(:metadata)
    spec.metadata['allowed_push_host'] = "http://gem.carecloud.com"
  end

  spec.summary       = %q{custom edi parser}
  spec.description   = %q{custom edi parser}
  spec.homepage      = "TODO: Put your gem's website or public repo URL here."
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.bindir        = "exe"
  spec.extensions     = ["ext/choo_choo_ext/extconf.rb"]
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib", "ext/choo_choo_ext"]

  spec.add_dependency "rake-compiler", "~> 0.9"
  #spec.add_dependency "activesupport"
  spec.add_dependency "oj", "~> 2.12"
  spec.add_dependency "ox", "~> 2.2"
  spec.add_development_dependency "bundler", "~> 1.8"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rspec", "~> 3.0"
  spec.add_development_dependency "pry", "~> 0.9.12"
  spec.add_development_dependency "pry-byebug"
  spec.add_development_dependency "benchmark-ips"
  spec.add_development_dependency "memory_profiler"
end
