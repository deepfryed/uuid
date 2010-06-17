#!/usr/bin/ruby

require 'mkmf'

$CFLAGS = "-std=c99"

if have_library('uuid')
  create_makefile 'uuid'
else
  puts error=<<-TEXT
    Unable to find uuid development library.
    Try sudo apt-get install uuid-dev
  TEXT
  exit 1
end
