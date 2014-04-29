dnl file      : m4/libexpat.m4
dnl copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
dnl license   : MIT; see accompanying LICENSE file
dnl
dnl LIBEXPAT([ACTION-IF-FOUND[, ACTION-IF-NOT-FOUND]])
dnl
dnl
AC_DEFUN([LIBEXPAT], [
libexpat_found=no

AC_MSG_CHECKING([for expat])

save_LIBS="$LIBS"
LIBS="-lexpat $LIBS"

CXX_LIBTOOL_LINK_IFELSE([
AC_LANG_SOURCE([
#include <expat.h>

int
main ()
{
  XML_Parser p (XML_ParserCreateNS (0, XML_Char (' ')));
  XML_ParserFree (p);
}
])],
[
libexpat_found=yes
])

if test x"$libexpat_found" = xyes; then
  AC_MSG_RESULT([yes])
  [$1]
else
  LIBS="$save_LIBS"
  AC_MSG_RESULT([no])
  [$2]
fi
])dnl
