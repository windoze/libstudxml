# file      : build/export/libstudxml/stub.make
# copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

$(call include-once,$(src_root)/xml/makefile,$(out_root))

$(call export,\
  l: $(out_root)/xml/studxml.l,\
  cpp-options: $(out_root)/xml/studxml.l.cpp-options)
