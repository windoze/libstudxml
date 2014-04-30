# file      : tests/makefile
# copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

tests := parser serializer roundtrip

default   := $(out_base)/
test      := $(out_base)/.test
dist      := $(out_base)/.dist
clean     := $(out_base)/.clean

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(tests)))
$(test): $(addprefix $(out_base)/,$(addsuffix /.test,$(tests)))

$(dist): export dirs := $(tests)
$(dist): export extra_dist := test.bat tests-vc9.sln tests-vc10.sln \
tests-vc11.sln tests-vc12.sln
$(dist): $(addprefix $(out_base)/,$(addsuffix /.dist,$(tests)))
	$(call meta-automake)
	$(call meta-vc9sln,tests-vc9.sln)
	$(call meta-vc10sln,tests-vc10.sln)
	$(call meta-vc11sln,tests-vc11.sln)
	$(call meta-vc12sln,tests-vc12.sln)
	$(call meta-vctest,tests-vc9.sln,test.bat)

$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(tests)))

$(call include,$(bld_root)/meta/vc9sln.make)
$(call include,$(bld_root)/meta/vc10sln.make)
$(call include,$(bld_root)/meta/vc11sln.make)
$(call include,$(bld_root)/meta/vc12sln.make)
$(call include,$(bld_root)/meta/vctest.make)
$(call include,$(bld_root)/meta/automake.make)

$(foreach t,$(tests),$(call import,$(src_base)/$t/makefile))
