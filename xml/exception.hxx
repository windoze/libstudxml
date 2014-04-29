// file      : xml/exception.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef XML_EXCEPTION_HXX
#define XML_EXCEPTION_HXX

#include <xml/details/pre.hxx>

#include <exception>

#include <xml/details/export.hxx>

namespace xml
{
  struct LIBSTUDXML_EXPORT exception: std::exception {};
}

#include <xml/details/post.hxx>

#endif // XML_EXCEPTION_HXX
