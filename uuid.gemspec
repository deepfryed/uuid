Gem::Specification.new do |s|
  s.name = %q{uuid}
  s.version = "0.1.0"

  s.authors = ["Bharanee Rathna"]
  s.date = %q{2010-06-17}
  s.description = %q{Ruby interface to the uuid library for linux.}
  s.email = %q{deepfryed@gmail.com}
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = [ "README.rdoc" ]
  s.files = [
    "README.rdoc",
    "LICENSE",
     "ext/uuid.c",
     "lib/uuid.rb"
  ]
  s.homepage = %q{http://github.com/deepfryed/uuid}
  s.rdoc_options = ["--charset=UTF-8"]
  s.require_paths = ["lib"]
  s.rubygems_version = %q{1.3.5}
  s.summary = %q{Ruby interface to uuid library for linux.}

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 3
  end
end

