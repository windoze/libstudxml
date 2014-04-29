# file      : configure.ac
# copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

AC_PREREQ(2.60)
AC_INIT([libstudxml], [__value__(version)], [studxml-users@codesynthesis.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([xml/exception.hxx])

AM_INIT_AUTOMAKE([-Wall -Werror foreign nostdinc subdir-objects dist-bzip2 dist-zip tar-ustar])
m4_equote()[m4_ifdef]m4_dquote()([AM_PROG_AR], [AM_PROG_AR]) # Required by automake 1.12.

LT_INIT([win32-dll])

AC_CANONICAL_HOST

# Check for diff.
#
DIFF_TOOL

# Check for C++ compiler and use it to compile the tests.
#
AC_PROG_CXX
AC_LANG(C++)

# Create the libtool executable so that we can use it in further tests.
#
LT_OUTPUT

# Check if we need to use external Expat.
#
AC_MSG_CHECKING([if we should use external expat])

AC_ARG_WITH(
  [external-expat],
  [AC_HELP_STRING([--with-external-expat],[use external expat instead of the internal subset])],
  [external_expat=${withval}],
  [external_expat=no])

if test x"$external_expat" != xno; then
  AC_MSG_RESULT([yes])

  # Check if we have Expat.
  #
  expat_found=yes
  LIBEXPAT([],[expat_found=no])

  if test x"$expat_found" = xno; then
    AC_MSG_ERROR([expat is not found; consider using CPPFLAGS/LDFLAGS to specify its location])
  fi

  AC_DEFINE([LIBSTUDXML_EXTERNAL_EXPAT], [1], [Use external expat.])
else
  AC_MSG_RESULT([no])
fi

AM_CONDITIONAL([LIBSTUDXML_EXTERNAL_EXPAT], [test x"$external_expat" != xno])

# If we have internal Expat, then determine the byteorder.
#
if test x"$external_expat" = xno; then
  AC_C_BIGENDIAN([byteorder=4321], [byteorder=1234])
  AC_DEFINE_UNQUOTED([LIBSTUDXML_BYTEORDER], [$byteorder], [1234 = little, 4321 = big])
fi

# Define LIBSTUDXML_STATIC_LIB if we are build static library on certain
# platforms.
#
STATIC_LIB([LIBSTUDXML_STATIC_LIB], [Static library interface.])

# Allow the user to specify the pkgconfig directory.
#
PKGCONFIG

# Check if we should disable rpath.
#
DISABLE_RPATH

# Output.
#
AC_CONFIG_HEADERS([xml/config.h xml/details/config.h])
AC_CONFIG_FILES([ __path__(config_files)])
AC_CONFIG_COMMANDS([tester-mode], [chmod +x tester])
AC_OUTPUT
