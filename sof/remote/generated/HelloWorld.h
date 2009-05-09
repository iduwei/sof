/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__




class HelloWorld;
typedef HelloWorld *HelloWorld_ptr;
typedef HelloWorld_ptr HelloWorldRef;
typedef ObjVar< HelloWorld > HelloWorld_var;
typedef ObjOut< HelloWorld > HelloWorld_out;




/*
 * Base class and common definitions for interface HelloWorld
 */

class HelloWorld : 
  virtual public CORBA::Object
{
  public:
    virtual ~HelloWorld();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef HelloWorld_ptr _ptr_type;
    typedef HelloWorld_var _var_type;
    #endif

    static HelloWorld_ptr _narrow( CORBA::Object_ptr obj );
    static HelloWorld_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static HelloWorld_ptr _duplicate( HelloWorld_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static HelloWorld_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void hello() = 0;

  protected:
    HelloWorld() {};
  private:
    HelloWorld( const HelloWorld& );
    void operator=( const HelloWorld& );
};

// Stub for interface HelloWorld
class HelloWorld_stub:
  virtual public HelloWorld
{
  public:
    virtual ~HelloWorld_stub();
    void hello();

  private:
    void operator=( const HelloWorld_stub& );
};

#ifndef MICO_CONF_NO_POA

class HelloWorld_stub_clp :
  virtual public HelloWorld_stub,
  virtual public PortableServer::StubBase
{
  public:
    HelloWorld_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~HelloWorld_stub_clp ();
    void hello();

  protected:
    HelloWorld_stub_clp ();
  private:
    void operator=( const HelloWorld_stub_clp & );
};

#endif // MICO_CONF_NO_POA

#ifndef MICO_CONF_NO_POA

class POA_HelloWorld : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~POA_HelloWorld ();
    HelloWorld_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static POA_HelloWorld * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void hello() = 0;

  protected:
    POA_HelloWorld () {};

  private:
    POA_HelloWorld (const POA_HelloWorld &);
    void operator= (const POA_HelloWorld &);
};

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_HelloWorld;

#endif
