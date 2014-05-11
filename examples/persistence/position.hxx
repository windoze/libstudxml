// file      : examples/persistence/position.hxx
// copyright : not copyrighted - public domain

#ifndef POSITION_HXX
#define POSITION_HXX

#include <string>
#include <vector>
#include <iosfwd>

#include <xml/forward.hxx> // xml::{parser,serializer} forward declarations.

enum object_type {building, mountain};

// XML parser and serializer will use these operators to convert
// object_type to/from a string representation unless we provide
// an xml::value_traits specialization.
//
std::ostream&
operator<< (std::ostream&, object_type);

std::istream&
operator>> (std::istream&, object_type&);

class position
{
public:
  position (float lat = 0, float lon = 0): lat_ (lat), lon_ (lon) {}

  float
  lat () const {return lat_;}

  float
  lon () const {return lon_;}

  // XML persistence.
  //
public:
  position (xml::parser&);

  void
  serialize (xml::serializer&) const;

private:
  float lat_;
  float lon_;
};

class object
{
public:
  object (const std::string& name, object_type type, unsigned int id)
      : name_ (name), type_ (type), id_ (id) {}

  const std::string&
  name () const {return name_;}

  object_type
  type () const {return type_;}

  unsigned int
  id () const {return id_;}

  typedef std::vector<position> positions_type;

  positions_type&
  positions () {return positions_;}

  const positions_type&
  positions () const {return positions_;}

  // XML persistence.
  //
public:
  object (xml::parser&);

  void
  serialize (xml::serializer&) const;

private:
  std::string name_;
  object_type type_;
  unsigned int id_;
  positions_type positions_;
};

#endif // POSITION_HXX
