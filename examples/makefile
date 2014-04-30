# file      : examples/makefile
# copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

examples := roundtrip performance

default   := $(out_base)/
test      := $(out_base)/.test
dist      := $(out_base)/.dist
clean     := $(out_base)/.clean

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(examples)))
$(test): $(addprefix $(out_base)/,$(addsuffix /.test,$(examples)))

$(dist): export dirs := $(examples)
$(dist): export extra_dist := test.bat examples-vc9.sln examples-vc10.sln \
examples-vc11.sln examples-vc12.sln
$(dist): $(addprefix $(out_base)/,$(addsuffix /.dist,$(examples)))
	$(call meta-automake)
	$(call meta-vc9sln,examples-vc9.sln)
	$(call meta-vc10sln,examples-vc10.sln)
	$(call meta-vc11sln,examples-vc11.sln)
	$(call meta-vc12sln,examples-vc12.sln)
	$(call meta-vctest,examples-vc9.sln,test.bat)

$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(examples)))

$(call include,$(bld_root)/meta/vc9sln.make)
$(call include,$(bld_root)/meta/vc10sln.make)
$(call include,$(bld_root)/meta/vc11sln.make)
$(call include,$(bld_root)/meta/vc12sln.make)
$(call include,$(bld_root)/meta/vctest.make)
$(call include,$(bld_root)/meta/automake.make)

$(foreach t,$(examples),$(call import,$(src_base)/$t/makefile))
