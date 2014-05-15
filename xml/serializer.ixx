// file      : xml/serializer.ixx
// copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <xml/value-traits>

namespace xml
{
  inline void serializer::
  start_element (const qname_type& qname)
  {
    start_element (qname.namespace_ (), qname.name ());
  }

  inline void serializer::
  start_element (const std::string& name)
  {
    start_element (std::string (), name);
  }

  inline void serializer::
  element (const std::string& v)
  {
    if (!v.empty ())
      characters (v);

    end_element ();
  }

  template <typename T>
  inline void serializer::
  element (const T& v)
  {
    element (value_traits<T>::serialize (v, *this));
  }

  inline void serializer::
  element (const std::string& n, const std::string& v)
  {
    element (std::string (), n, v);
  }

  template <typename T>
  inline void serializer::
  element (const std::string& n, const T& v)
  {
    element (n, value_traits<T>::serialize (v, *this));
  }

  inline void serializer::
  element (const qname_type& qn, const std::string& v)
  {
    element (qn.namespace_ (), qn.name (), v);
  }

  template <typename T>
  inline void serializer::
  element (const qname_type& qn, const T& v)
  {
    element (qn, value_traits<T>::serialize (v, *this));
  }

  template <typename T>
  inline void serializer::
  element (const std::string& ns, const std::string& n, const T& v)
  {
    element (ns, n, value_traits<T>::serialize (v, *this));
  }

  inline void serializer::
  start_attribute (const qname_type& qname)
  {
    start_attribute (qname.namespace_ (), qname.name ());
  }

  inline void serializer::
  start_attribute (const std::string& name)
  {
    start_attribute (std::string (), name);
  }

  inline void serializer::
  attribute (const qname_type& qname, const std::string& value)
  {
    attribute (qname.namespace_ (), qname.name (), value);
  }

  template <typename T>
  inline void serializer::
  attribute (const qname_type& qname, const T& value)
  {
    attribute (qname, value_traits<T>::serialize (value, *this));
  }

  inline void serializer::
  attribute (const std::string& name, const std::string& value)
  {
    attribute (std::string (), name, value);
  }

  template <typename T>
  inline void serializer::
  attribute (const std::string& name, const T& value)
  {
    attribute (name, value_traits<T>::serialize (value, *this));
  }

  template <typename T>
  inline void serializer::
  attribute (const std::string& ns, const std::string& name, const T& value)
  {
    attribute (ns, name, value_traits<T>::serialize (value, *this));
  }

  template <typename T>
  inline void serializer::
  characters (const T& value)
  {
    characters (value_traits<T>::serialize (value, *this));
  }
}
