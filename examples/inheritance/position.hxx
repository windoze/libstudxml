// file      : examples/inheritance/position.hxx
// copyright : not copyrighted - public domain

#ifndef POSITION_HXX
#define POSITION_HXX

#include <string>
#include <vector>
#include <iosfwd>

#include <xml/forward.hxx> // xml::{parser,serializer} forward declarations.

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
  object (const std::string& name, unsigned int id): name_ (name), id_ (id) {}

  const std::string&
  name () const {return name_;}

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
  serialize_attributes (xml::serializer&) const;

  void
  serialize_content (xml::serializer&) const;

  void
  serialize (xml::serializer& s) const
  {
    serialize_attributes (s);
    serialize_content (s);
  }

private:
  std::string name_;
  unsigned int id_;
  positions_type positions_;
};

class elevation
{
public:
  elevation (float value = 0): value_ (value) {}

  float
  value () const {return value_;}

  // XML persistence.
  //
public:
  elevation (xml::parser&);

  void
  serialize (xml::serializer&) const;

private:
  float value_;
};

class elevated_object: public object
{
public:
  elevated_object (const std::string& name,
                   const std::string& units,
                   unsigned int id)
      : object (name, id), units_ (units) {}

  const std::string&
  units () const {return units_;}

  typedef std::vector<elevation> elevations_type;

  elevations_type&
  elevations () {return elevations_;}

  const elevations_type&
  elevations () const {return elevations_;}

  // XML persistence.
  //
public:
  elevated_object (xml::parser&);

  void
  serialize_attributes (xml::serializer&) const;

  void
  serialize_content (xml::serializer&) const;

  void
  serialize (xml::serializer& s) const
  {
    serialize_attributes (s);
    serialize_content (s);
  }

private:
  std::string units_;
  elevations_type elevations_;
};

class objects
{
public:
  typedef std::vector<object> simple_objects_type;
  typedef std::vector<elevated_object> elevated_objects_type;

  simple_objects_type&
  simple_objects () {return simple_objects_;}

  const simple_objects_type&
  simple_objects () const {return simple_objects_;}

  elevated_objects_type&
  elevated_objects () {return elevated_objects_;}

  const elevated_objects_type&
  elevated_objects () const {return elevated_objects_;}

  // XML persistence.
  //
public:
  objects (xml::parser&);

  void
  serialize (xml::serializer&) const;

private:
  simple_objects_type simple_objects_;
  elevated_objects_type elevated_objects_;
};

#endif // POSITION_HXX
