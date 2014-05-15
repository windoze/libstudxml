# file      : examples/template/Makefile.am
# copyright : not copyrighted - public domain

EXTRA_DIST = __file__(extra_dist)

noinst_PROGRAMS = driver
driver_SOURCES = driver.cxx __path__(extra_sources) __path__(extra_headers)
LDADD = $(top_builddir)/xml/libstudxml.la

AM_CPPFLAGS = -I'$(top_builddir)' -I'$(top_srcdir)'

TESTS=$(top_builddir)/tester
TESTS_ENVIRONMENT=example=1; export example;

# Make sure make doesn't try to build the no-extension headers
# thinking that they are executable. Those are pulled in through
# auto-generated dependencies.
#
__foreach_w__(__f,__path__(xml_headers),$(top_srcdir)/xml/__f ): ; @:
