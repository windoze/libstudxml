# file      : tests/template/Makefile.am
# copyright : not copyrighted - public domain

EXTRA_DIST = __file__(extra_dist)

noinst_PROGRAMS = driver
driver_SOURCES = driver.cxx __path__(extra_sources) __path__(extra_headers)
LDADD = $(top_builddir)/xml/libstudxml.la

AM_CPPFLAGS = -I'$(top_builddir)' -I'$(top_srcdir)'

TESTS=$(top_builddir)/tester
TESTS_ENVIRONMENT=example=; export example;

CLEANFILES = test.out
