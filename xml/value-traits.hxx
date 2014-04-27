// file      : xml/value-traits.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef XML_VALUE_TRAITS_HXX
#define XML_VALUE_TRAITS_HXX

#include <string>
#include <cstddef> // std::size_t

#include <xml/details/export.hxx>

namespace xml
{
  //@@ forward
  class parser;
  class serializer;

  template <typename T>
  struct default_value_traits
  {
    static T
    parse (std::string, const parser&);

    static std::string
    serialize (const T&, const serializer&);
  };

  template <>
  struct LIBSTUDXML_EXPORT default_value_traits<bool>
  {
    static bool
    parse (std::string, const parser&);

    static std::string
    serialize (bool v, const serializer&)
    {
      return v ? "true" : "false";
    }
  };

  template <typename T>
  struct value_traits: default_value_traits<T> {};

  template <typename T, std::size_t N>
  struct value_traits<T[N]>: default_value_traits<const T*> {};
}

#include <xml/value-traits.txx>

#endif // XML_VALUE_TRAITS_HXX
