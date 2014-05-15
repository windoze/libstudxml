// file      : tests/serializer/driver.cxx
// copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifdef NDEBUG
#  error tests require enabled assert(); un-define the NDEBUG macro
#endif

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>

#include <xml/serializer>

using namespace std;
using namespace xml;

int
main ()
{
  // Test error handling.
  //
  try
  {
    ostringstream os;
    serializer s (os, "test");

    s.attribute ("foo", "bar");
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  try
  {
    ostringstream os;
    os.exceptions (ios_base::badbit | ios_base::failbit);
    serializer s (os, "test");

    s.start_element ("root");
    s.characters ("one");
    os.setstate (ios_base::badbit);
    s.characters ("two");
    assert (false);
  }
  catch (const ios_base::failure&)
  {
  }

  // Test value serialization.
  //
  {
    ostringstream os;
    serializer s (os, "test", 0);

    s.start_element ("root");
    s.attribute ("version", 123);
    s.characters (true);
    s.end_element ();

    assert (os.str () == "<root version=\"123\">true</root>\n");
  }

  // Test helpers for serializing elements with simple content.
  //
  {
    ostringstream os;
    serializer s (os, "element", 0);

    s.start_element ("root");

    s.start_element ("nested");
    s.element ("X");

    s.start_element ("nested");
    s.element (123);

    s.element ("nested", "X");
    s.element ("nested", 123);
    s.element ("test", "nested", "X");
    s.element ("test", "nested", 123);
    s.element (qname ("test", "nested"), "X");
    s.element (qname ("test", "nested"), 123);

    s.end_element (); // root

    assert (os.str () ==
            "<root>"
            "<nested>X</nested>"
            "<nested>123</nested>"
            "<nested>X</nested>"
            "<nested>123</nested>"
            "<g1:nested xmlns:g1=\"test\">X</g1:nested>"
            "<g1:nested xmlns:g1=\"test\">123</g1:nested>"
            "<g1:nested xmlns:g1=\"test\">X</g1:nested>"
            "<g1:nested xmlns:g1=\"test\">123</g1:nested>"
            "</root>\n");
  }
}
