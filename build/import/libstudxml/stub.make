# file      : build/import/libstudxml/stub.make
# copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

$(call include-once,$(scf_root)/import/libstudxml/configuration-rules.make,$(dcf_root))

libstudxml_installed :=

$(call -include,$(dcf_root)/import/libstudxml/configuration-dynamic.make)

ifdef libstudxml_installed

ifeq ($(libstudxml_installed),y)

$(call export,l: -lstudxml,cpp-options: )

else

# Include export stub.
#
$(call include,$(scf_root)/export/libstudxml/stub.make)

endif

else

.NOTPARALLEL:

endif
