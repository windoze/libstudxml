# file      : examples/persistence/makefile
# copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../build/bootstrap.make

cxx_tun := driver.cxx position.cxx

cxx_obj  := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od   := $(cxx_obj:.o=.o.d)

studxml.l             := $(out_root)/xml/studxml.l
studxml.l.cpp-options := $(out_root)/xml/studxml.l.cpp-options

driver   := $(out_base)/driver
test     := $(out_base)/.test
dist     := $(out_base)/.dist
clean    := $(out_base)/.clean

# Build.
#
$(driver): $(cxx_obj) $(studxml.l)
$(cxx_obj) $(cxx_od): $(studxml.l.cpp-options)

$(call include-dep,$(cxx_od))

# Alias for default target.
#
$(out_base)/: $(driver)

# Dist
#
$(dist): name := $(subst $(src_root)/examples/,,$(src_base))
$(dist): sources := $(cxx_tun)
$(dist): extras := README position.xml
$(dist): export extra_headers := position.hxx
$(dist): export extra_dist := $(extras) $(name)-vc9.vcproj \
$(name)-vc10.vcxproj $(name)-vc10.vcxproj.filters \
$(name)-vc11.vcxproj $(name)-vc11.vcxproj.filters \
$(name)-vc12.vcxproj $(name)-vc12.vcxproj.filters 
$(dist):
	$(call dist-data,$(sources) $(extra_headers) $(extras))
	$(call meta-automake,../template/Makefile.am)
	$(call meta-vc9proj,../template/template-vc9.vcproj,$(name)-vc9.vcproj)
	$(call meta-vc10proj,../template/template-vc10.vcxproj,$(name)-vc10.vcxproj)
	$(call meta-vc11proj,../template/template-vc11.vcxproj,$(name)-vc11.vcxproj)
	$(call meta-vc12proj,../template/template-vc12.vcxproj,$(name)-vc12.vcxproj)

# Test.
#
$(test): $(driver)
	$(call message,test $<,$< $(src_base)/position.xml)

# Clean.
#
$(clean):                            \
  $(driver).o.clean                  \
  $(addsuffix .cxx.clean,$(cxx_obj)) \
  $(addsuffix .cxx.clean,$(cxx_od))


# Generated .gitignore.
#
ifeq ($(out_base),$(src_base))
$(driver): | $(out_base)/.gitignore

$(out_base)/.gitignore: files := driver
$(clean): $(out_base)/.gitignore.clean

$(call include,$(bld_root)/git/gitignore.make)
endif


# How to.
#
$(call include,$(bld_root)/dist.make)
$(call include,$(bld_root)/meta/vc9proj.make)
$(call include,$(bld_root)/meta/vc10proj.make)
$(call include,$(bld_root)/meta/vc11proj.make)
$(call include,$(bld_root)/meta/vc12proj.make)
$(call include,$(bld_root)/meta/automake.make)

$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)

# Dependencies.
#
$(call import,$(src_root)/xml/makefile)
