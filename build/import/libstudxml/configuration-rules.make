# file      : build/import/libstudxml/configuration-rules.make
# copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

$(dcf_root)/import/libstudxml/configuration-dynamic.make: | $(dcf_root)/import/libstudxml/.
	$(call message,,$(scf_root)/import/libstudxml/configure $@)

ifndef %foreign%

$(dcf_root)/.disfigure::
	$(call message,rm $(dcf_root)/import/libstudxml/configuration-dynamic.make,\
rm -f $(dcf_root)/import/libstudxml/configuration-dynamic.make)

endif
