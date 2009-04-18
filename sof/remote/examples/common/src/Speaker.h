/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __SPEAKER_H__
#define __SPEAKER_H__




class Speaker;
typedef Speaker *Speaker_ptr;
typedef Speaker_ptr SpeakerRef;
typedef ObjVar< Speaker > Speaker_var;
typedef ObjOut< Speaker > Speaker_out;


#include "../../../common/src/sof/framework/remote/corba/generated/CORBAObjects.h"


/*
 * Base class and common definitions for interface Speaker
 */

class Speaker : 
  virtual public ::sof::framework::remote::corba::generated::CORBAService
{
  public:
    virtual ~Speaker();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Speaker_ptr _ptr_type;
    typedef Speaker_var _var_type;
    #endif

    static Speaker_ptr _narrow( CORBA::Object_ptr obj );
    static Speaker_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Speaker_ptr _duplicate( Speaker_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Speaker_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void sayHello( const char* text ) = 0;

  protected:
    Speaker() {};
  private:
    Speaker( const Speaker& );
    void operator=( const Speaker& );
};

// Stub for interface Speaker
class Speaker_stub:
  virtual public Speaker,
  virtual public ::sof::framework::remote::corba::generated::CORBAService_stub
{
  public:
    virtual ~Speaker_stub();
    void sayHello( const char* text );

  private:
    void operator=( const Speaker_stub& );
};

#ifndef MICO_CONF_NO_POA

class Speaker_stub_clp :
  virtual public Speaker_stub,
  virtual public ::sof::framework::remote::corba::generated::CORBAService_stub_clp
{
  public:
    Speaker_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~Speaker_stub_clp ();
    void sayHello( const char* text );

  protected:
    Speaker_stub_clp ();
  private:
    void operator=( const Speaker_stub_clp & );
};

#endif // MICO_CONF_NO_POA

#ifndef MICO_CONF_NO_POA

class POA_Speaker : 
  virtual public POA_sof::framework::remote::corba::generated::CORBAService
{
  public:
    virtual ~POA_Speaker ();
    Speaker_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static POA_Speaker * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void sayHello( const char* text ) = 0;

  protected:
    POA_Speaker () {};

  private:
    POA_Speaker (const POA_Speaker &);
    void operator= (const POA_Speaker &);
};

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_Speaker;

#endif
