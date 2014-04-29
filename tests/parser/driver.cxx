// file      : tests/parser/driver.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifdef NDEBUG
#  error tests require enabled assert(); un-define the NDEBUG macro
#endif

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>

#include <xml/parser.hxx>

using namespace std;
using namespace xml;

int
main ()
{
  // Test error handling.
  //
  try
  {
    istringstream is ("<root><nested>X</nasted></root>");
    parser p (is, "test");

    assert (p.next () == parser::start_element);
    assert (p.next () == parser::start_element);
    assert (p.next () == parser::characters && p.value () == "X");
    p.next ();
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  try
  {
    istringstream is ("<root/>");
    is.exceptions (ios_base::badbit | ios_base::failbit);
    parser p (is, "test");

    is.setstate (ios_base::badbit);
    p.next ();
    assert (false);
  }
  catch (const ios_base::failure&)
  {
  }

  // Test the next_expect() functionality.
  //
  {
    istringstream is ("<root/>");
    parser p (is, "test");
    p.next_expect (parser::start_element, "root");
    p.next_expect (parser::end_element);
  }

  try
  {
    istringstream is ("<root/>");
    parser p (is, "test");
    p.next_expect (parser::end_element);
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  try
  {
    istringstream is ("<root/>");
    parser p (is, "test");
    p.next_expect (parser::start_element, "root1");
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  // Test attribute maps.
  //
  {
    istringstream is ("<root a='a' b='b' d='123' t='true'/>");
    parser p (is, "test");
    p.next_expect (parser::start_element, "root");

    assert (p.attribute ("a") == "a");
    assert (p.attribute ("b", "B") == "b");
    assert (p.attribute ("c", "C") == "C");
    assert (p.attribute<int> ("d") == 123);
    assert (p.attribute<bool> ("t") == true);
    assert (p.attribute ("f", false) == false);

    p.next_expect (parser::end_element);
  }

  {
    istringstream is ("<root a='a'><nested a='A'><inner/></nested></root>");
    parser p (is, "test");
    p.next_expect (parser::start_element, "root");
    assert (p.attribute ("a") == "a");
    assert (p.peek () == parser::start_element && p.name () == "nested");
    assert (p.attribute ("a") == "a");
    p.next_expect (parser::start_element, "nested");
    assert (p.attribute ("a") == "A");
    p.next_expect (parser::start_element, "inner");
    assert (p.attribute ("a", "") == "");
    p.next_expect (parser::end_element);
    assert (p.attribute ("a") == "A");
    assert (p.peek () == parser::end_element);
    assert (p.attribute ("a") == "A"); // Still valid.
    p.next_expect (parser::end_element);
    assert (p.attribute ("a") == "a");
    p.next_expect (parser::end_element);
    assert (p.attribute ("a", "") == "");
  }

  try
  {
    istringstream is ("<root a='a' b='b'/>");
    parser p (is, "test");
    p.next_expect (parser::start_element, "root");
    assert (p.attribute ("a") == "a");
    p.next_expect (parser::end_element);
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  try
  {
    istringstream is ("<root a='abc'/>");
    parser p (is, "test");
    p.next_expect (parser::start_element, "root");
    p.attribute<int> ("a");
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  // Test peeking and getting the current event.
  //
  {
    istringstream is ("<root x='x'>x<nested/></root>");
    parser p (is, "peek",
              parser::receive_default | parser::receive_attributes_event);

    assert (p.event () == parser::eof);

    assert (p.peek () == parser::start_element);
    assert (p.next () == parser::start_element);
    assert (p.event () == parser::start_element);

    assert (p.peek () == parser::start_attribute);
    assert (p.event () == parser::start_attribute);
    assert (p.next () == parser::start_attribute);

    assert (p.peek () == parser::characters && p.value () == "x");
    assert (p.next () == parser::characters && p.value () == "x");
    assert (p.event () == parser::characters && p.value () == "x");

    assert (p.peek () == parser::end_attribute);
    assert (p.event () == parser::end_attribute);
    assert (p.next () == parser::end_attribute);

    assert (p.peek () == parser::characters && p.value () == "x");
    assert (p.next () == parser::characters && p.value () == "x");
    assert (p.event () == parser::characters && p.value () == "x");

    assert (p.peek () == parser::start_element);
    assert (p.next () == parser::start_element);
    assert (p.event () == parser::start_element);

    assert (p.peek () == parser::end_element);
    assert (p.next () == parser::end_element);
    assert (p.event () == parser::end_element);

    assert (p.peek () == parser::end_element);
    assert (p.next () == parser::end_element);
    assert (p.event () == parser::end_element);

    assert (p.peek () == parser::eof);
    assert (p.next () == parser::eof);
    assert (p.event () == parser::eof);
  }

  // Test content processing.
  //

  // empty
  //
  {
    istringstream is ("<root x=' x '>  \n\t </root>");
    parser p (is, "empty",
              parser::receive_default | parser::receive_attributes_event);

    assert (p.next () == parser::start_element);
    p.content (parser::empty);
    assert (p.next () == parser::start_attribute);
    assert (p.next () == parser::characters && p.value () == " x ");
    assert (p.next () == parser::end_attribute);
    assert (p.next () == parser::end_element);
    assert (p.next () == parser::eof);
  }

  try
  {
    istringstream is ("<root>  \n &amp; X \t </root>");
    parser p (is, "empty");

    assert (p.next () == parser::start_element);
    p.content (parser::empty);
    p.next ();
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  // simple
  //
  {
    istringstream is ("<root> X </root>");
    parser p (is, "simple");

    assert (p.next () == parser::start_element);
    p.content (parser::simple);
    assert (p.next () == parser::characters && p.value () == " X ");
    assert (p.next () == parser::end_element);
    assert (p.next () == parser::eof);
  }

  try
  {
    istringstream is ("<root> ? <nested/></root>");
    parser p (is, "simple");

    assert (p.next () == parser::start_element);
    p.content (parser::simple);
    assert (p.next () == parser::characters && p.value () == " ? ");
    p.next ();
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }

  // complex
  //
  {
    istringstream is ("<root x=' x '>\n"
                      "  <nested>\n"
                      "    <inner/>\n"
                      "    <inner> X </inner>\n"
                      "  </nested>\n"
                      "</root>\n");
    parser p (is, "complex",
              parser::receive_default | parser::receive_attributes_event);

    assert (p.next () == parser::start_element); // root
    p.content (parser::complex);

    assert (p.next () == parser::start_attribute);
    assert (p.next () == parser::characters && p.value () == " x ");
    assert (p.next () == parser::end_attribute);

    assert (p.next () == parser::start_element); // nested
    p.content (parser::complex);

    assert (p.next () == parser::start_element); // inner
    p.content (parser::empty);
    assert (p.next () == parser::end_element);   // inner

    assert (p.next () == parser::start_element); // inner
    p.content (parser::simple);
    assert (p.next () == parser::characters && p.value () == " X ");
    assert (p.next () == parser::end_element);   // inner

    assert (p.next () == parser::end_element);   // nested
    assert (p.next () == parser::end_element);   // root
    assert (p.next () == parser::eof);
  }

  try
  {
    istringstream is ("<root> \n<n/> X <n> X </n>  </root>");
    parser p (is, "complex");

    assert (p.next () == parser::start_element);
    p.content (parser::complex);
    assert (p.next () == parser::start_element);
    assert (p.next () == parser::end_element);
    p.next ();
    assert (false);
  }
  catch (const xml::exception&)
  {
    // cerr << e.what () << endl;
  }
}
