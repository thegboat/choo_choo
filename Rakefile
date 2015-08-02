require "bundler/gem_tasks"
require "rake/extensiontask"

# somewhere in your Rakefile, define your gem spec
spec = Gem::Specification.new do |s|
  s.name = "choo_choo"
  s.platform = Gem::Platform::RUBY
  s.extensions = FileList["ext/**/extconf.rb"]
end

# add your default gem packing task
Gem::PackageTask.new(spec) do |pkg|
end

# feed the ExtensionTask with your spec
Rake::ExtensionTask.new('choo_choo_parsing', spec)

