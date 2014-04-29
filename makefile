# file      : makefile
# copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))build/bootstrap.make

dirs := xml tests examples

default  := $(out_base)/
test     := $(out_base)/.test
dist     := $(out_base)/.dist
clean    := $(out_base)/.clean

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(dirs)))
$(test): $(addprefix $(out_base)/,$(addsuffix /.test,$(dirs)))

$(dist): export dirs := $(dirs)
$(dist): export docs := LICENSE NEWS README INSTALL version tester.bat
$(dist): data_dist := libstudxml-vc9.sln libstudxml-vc10.sln \
libstudxml-vc11.sln
$(dist): exec_dist := bootstrap tester.in
$(dist): export extra_dist := $(data_dist) $(exec_dist)
$(dist): export version = $(shell cat $(src_root)/version)

$(dist): $(addprefix $(out_base)/,$(addsuffix /.dist,$(dirs)))
	$(call dist-data,$(docs) $(data_dist) libstudxml.pc.in)
	$(call dist-exec,$(exec_dist))
	$(call dist-dir,m4)
	$(call meta-automake)
	$(call meta-autoconf)

$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(dirs)))

$(call include,$(bld_root)/dist.make)
$(call include,$(bld_root)/meta/automake.make)
$(call include,$(bld_root)/meta/autoconf.make)

$(foreach d,$(dirs),$(call import,$(src_base)/$d/makefile))
