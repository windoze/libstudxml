// file      : xml/details/export.hxx
// copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef XML_DETAILS_EXPORT_HXX
#define XML_DETAILS_EXPORT_HXX

#include <xml/details/config.hxx>

#ifdef LIBSTUDXML_STATIC_LIB
#  define LIBSTUDXML_EXPORT
#else
#  ifdef _WIN32
#    ifdef _MSC_VER
#      ifdef LIBSTUDXML_DYNAMIC_LIB
#        define LIBSTUDXML_EXPORT __declspec(dllexport)
#      else
#        define LIBSTUDXML_EXPORT __declspec(dllimport)
#      endif
#    else
#      ifdef LIBSTUDXML_DYNAMIC_LIB
#        ifdef DLL_EXPORT
#          define LIBSTUDXML_EXPORT __declspec(dllexport)
#        else
#          define LIBSTUDXML_EXPORT
#        endif
#      else
#        define LIBSTUDXML_EXPORT __declspec(dllimport)
#      endif
#    endif
#  else
#    define LIBSTUDXML_EXPORT
#  endif
#endif

#endif // XML_DETAILS_EXPORT_HXX
