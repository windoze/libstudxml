// file      : xml/serializer.cxx
// copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <new>     // std::bad_alloc
#include <cstring> // std::strlen

#include <xml/serializer>

using namespace std;

namespace xml
{
  // serialization
  //
  serialization::
  ~serialization () throw () {}

  serialization::
  serialization (const string& n, const string& d)
      : name_ (n), description_ (d)
  {
    init ();
  }

  serialization::
  serialization (const serializer& s, const std::string& d)
      : name_ (s.output_name ()), description_ (d)
  {
    init ();
  }

  void serialization::
  init ()
  {
    if (!name_.empty ())
    {
      what_ += name_;
      what_ += ": ";
    }

    what_ += "error: ";
    what_ += description_;
  }

  char const* serialization::
  what () const throw ()
  {
    return what_.c_str ();
  }

  // serializer
  //
  extern "C" genxStatus
  genx_write (void* p, constUtf8 us)
  {
    // It would have been easier to throw the exception directly,
    // however, the Genx code is most likely not exception safe.
    //
    ostream* os (static_cast<ostream*> (p));
    const char* s (reinterpret_cast<const char*> (us));
    os->write (s, static_cast<streamsize> (strlen (s)));
    return os->good () ? GENX_SUCCESS : GENX_IO_ERROR;
  }

  extern "C" genxStatus
  genx_write_bound (void* p, constUtf8 start, constUtf8 end)
  {
    ostream* os (static_cast<ostream*> (p));
    const char* s (reinterpret_cast<const char*> (start));
    streamsize n (static_cast<streamsize> (end - start));
    os->write (s, n);
    return os->good () ? GENX_SUCCESS : GENX_IO_ERROR;
  }

  extern "C" genxStatus
  genx_flush (void* p)
  {
    ostream* os (static_cast<ostream*> (p));
    os->flush ();
    return os->good () ? GENX_SUCCESS : GENX_IO_ERROR;
  }

  serializer::
  ~serializer ()
  {
    if (s_ != 0)
      genxDispose (s_);
  }

  serializer::
  serializer (ostream& os, const string& oname, unsigned short ind)
      : os_ (os), os_state_ (os.exceptions ()), oname_ (oname), depth_ (0)
  {
    // Temporarily disable exceptions on the stream.
    //
    os_.exceptions (ostream::goodbit);

    // Allocate the serializer. Make sure nothing else can throw after
    // this call since otherwise we will leak it.
    //
    s_ = genxNew (0, 0, 0);

    if (s_ == 0)
      throw bad_alloc ();

    genxSetUserData (s_, &os_);

    if (ind != 0)
      genxSetPrettyPrint (s_, ind);

    sender_.send = &genx_write;
    sender_.sendBounded = &genx_write_bound;
    sender_.flush = &genx_flush;

    if (genxStatus e = genxStartDocSender (s_, &sender_))
    {
      string m (genxGetErrorMessage (s_, e));
      genxDispose (s_);
      throw serialization (oname, m);
    }
  }

  void serializer::
  handle_error (genxStatus e)
  {
    switch (e)
    {
    case GENX_ALLOC_FAILED:
      throw bad_alloc ();
    case GENX_IO_ERROR:
      // Restoring the original exception state should trigger the
      // exception. If it doesn't (e.g., because the user didn't
      // configure the stream to throw), then fall back to the
      // serialiation exception.
      //
      os_.exceptions (os_state_);
      // Fall through.
    default:
      throw serialization (oname_, genxGetErrorMessage (s_, e));
    }
  }

  void serializer::
  start_element (const string& ns, const string& name)
  {
    if (genxStatus e = genxStartElementLiteral (
          s_,
          reinterpret_cast<constUtf8> (ns.empty () ? 0 : ns.c_str ()),
          reinterpret_cast<constUtf8> (name.c_str ())))
      handle_error (e);

    depth_++;
  }

  void serializer::
  end_element ()
  {
    if (genxStatus e = genxEndElement (s_))
      handle_error (e);

    // Call EndDocument() if we are past the root element.
    //
    if (--depth_ == 0)
    {
      if (genxStatus e = genxEndDocument (s_))
        handle_error (e);

      // Also restore the original exception state on the stream.
      //
      os_.exceptions (os_state_);
    }
  }

  void serializer::
  element (const string& ns, const string& n, const string& v)
  {
    start_element (ns, n);
    element (v);
  }

  void serializer::
  start_attribute (const string& ns, const string& name)
  {
    if (genxStatus e = genxStartAttributeLiteral (
          s_,
          reinterpret_cast<constUtf8> (ns.empty () ? 0 : ns.c_str ()),
          reinterpret_cast<constUtf8> (name.c_str ())))
      handle_error (e);
  }

  void serializer::
  end_attribute ()
  {
    if (genxStatus e = genxEndAttribute (s_))
      handle_error (e);
  }

  void serializer::
  attribute (const string& ns,
             const string& name,
             const string& value)
  {
    if (genxStatus e = genxAddAttributeLiteral (
          s_,
          reinterpret_cast<constUtf8> (ns.empty () ? 0 : ns.c_str ()),
          reinterpret_cast<constUtf8> (name.c_str ()),
          reinterpret_cast<constUtf8> (value.c_str ())))
      handle_error (e);
  }

  void serializer::
  characters (const string& value)
  {
    if (genxStatus e = genxAddCountedText (
          s_,
          reinterpret_cast<constUtf8> (value.c_str ()), value.size ()))
      handle_error (e);
  }

  void serializer::
  namespace_decl (const string& ns, const string& p)
  {
    if (genxStatus e = ns.empty () && p.empty ()
        ? genxUnsetDefaultNamespace (s_)
        : genxAddNamespaceLiteral (
          s_,
          reinterpret_cast<constUtf8> (ns.c_str ()),
          reinterpret_cast<constUtf8> (p.c_str ())))
      handle_error (e);
  }

  void serializer::
  xml_decl (const string& ver, const string& enc, const string& stl)
  {
    if (genxStatus e = genxXmlDeclaration (
          s_,
          reinterpret_cast<constUtf8> (ver.c_str ()),
          (enc.empty () ? 0 : reinterpret_cast<constUtf8> (enc.c_str ())),
          (stl.empty () ? 0 : reinterpret_cast<constUtf8> (stl.c_str ()))))
      handle_error (e);
  }

  bool serializer::
  lookup_namespace_prefix (const string& ns, string& p)
  {
    // Currently Genx will create a namespace mapping if one doesn't
    // already exist.
    //
    genxStatus e;
    genxNamespace gns (
      genxDeclareNamespace (
        s_, reinterpret_cast<constUtf8> (ns.c_str ()), 0, &e));

    if (e != GENX_SUCCESS)
      handle_error (e);

    p = reinterpret_cast<const char*> (genxGetNamespacePrefix (gns));
    return true;
  }
}
