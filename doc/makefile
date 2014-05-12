# file      : doc/makefile
# copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

dist    := $(out_base)/.dist

# Dist.
#
$(dist): data_dist := default.css intro.xhtml
$(dist): export html_docs := $(data_dist)
$(dist):
	$(call dist-data,$(html_docs))
	$(call meta-automake)

$(call include,$(bld_root)/dist.make)
$(call include,$(bld_root)/meta/automake.make)
