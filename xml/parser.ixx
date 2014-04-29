// file      : xml/parser.ixx
// copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <xml/value-traits.hxx>

namespace xml
{
  inline const std::string& parser::
  attribute (const std::string& n) const
  {
    return attribute (qname_type (n));
  }

  template <typename T>
  inline T parser::
  attribute (const std::string& n) const
  {
    return attribute<T> (qname_type (n));
  }

  inline std::string parser::
  attribute (const std::string& n, const std::string& dv) const
  {
    return attribute (qname_type (n), dv);
  }

  template <typename T>
  inline T parser::
  attribute (const std::string& n, const T& dv) const
  {
    return attribute<T> (qname_type (n), dv);
  }

  template <typename T>
  inline T parser::
  attribute (const qname_type& qn) const
  {
    return value_traits<T>::parse (attribute (qn), *this);
  }

  inline bool parser::
  attribute_present (const std::string& n) const
  {
    return attribute_present (qname_type (n));
  }

  inline const parser::attribute_map_type& parser::
  attribute_map () const
  {
    if (const element_entry* e = get_element ())
    {
      e->attr_unhandled_ = 0; // Assume all handled.
      return e->attr_map_;
    }

    return empty_attr_map_;
  }

  inline void parser::
  next_expect (event_type e, const qname_type& qn)
  {
    return next_expect (e, qn.namespace_ (), qn.name ());
  }

  inline void parser::
  next_expect (event_type e, const std::string& n)
  {
    return next_expect (e, std::string (), n);
  }
}
