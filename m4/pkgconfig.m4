dnl file      : m4/pkgconfig.m4
dnl copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
dnl license   : MIT; see accompanying LICENSE file
dnl
AC_DEFUN([PKGCONFIG],[
AC_ARG_WITH(
  [pkgconfigdir],
  [AC_HELP_STRING([--with-pkgconfigdir=DIR],[location of pkgconfig dir (default is libdir/pkgconfig)])],
  [pkgconfigdir=${withval}],
  [pkgconfigdir='${libdir}/pkgconfig'])
AC_SUBST([pkgconfigdir])
])dnl
