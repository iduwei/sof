/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__




class Multiplier;
typedef Multiplier *Multiplier_ptr;
typedef Multiplier_ptr MultiplierRef;
typedef ObjVar< Multiplier > Multiplier_var;
typedef ObjOut< Multiplier > Multiplier_out;


#include "../../impl/src/sof/framework/remote/corba/generated/CORBAObjects.h"


/*
 * Base class and common definitions for interface Multiplier
 */

class Multiplier : 
  virtual public ::sof::framework::remote::corba::generated::CORBAService
{
  public:
    virtual ~Multiplier();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Multiplier_ptr _ptr_type;
    typedef Multiplier_var _var_type;
    #endif

    static Multiplier_ptr _narrow( CORBA::Object_ptr obj );
    static Multiplier_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Multiplier_ptr _duplicate( Multiplier_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Multiplier_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual CORBA::Long multiply( CORBA::Long x, CORBA::Long y ) = 0;

  protected:
    Multiplier() {};
  private:
    Multiplier( const Multiplier& );
    void operator=( const Multiplier& );
};

// Stub for interface Multiplier
class Multiplier_stub:
  virtual public Multiplier,
  virtual public ::sof::framework::remote::corba::generated::CORBAService_stub
{
  public:
    virtual ~Multiplier_stub();
    CORBA::Long multiply( CORBA::Long x, CORBA::Long y );

  private:
    void operator=( const Multiplier_stub& );
};

#ifndef MICO_CONF_NO_POA

class Multiplier_stub_clp :
  virtual public Multiplier_stub,
  virtual public ::sof::framework::remote::corba::generated::CORBAService_stub_clp
{
  public:
    Multiplier_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~Multiplier_stub_clp ();
    CORBA::Long multiply( CORBA::Long x, CORBA::Long y );

  protected:
    Multiplier_stub_clp ();
  private:
    void operator=( const Multiplier_stub_clp & );
};

#endif // MICO_CONF_NO_POA

#ifndef MICO_CONF_NO_POA

class POA_Multiplier : 
  virtual public POA_sof::framework::remote::corba::generated::CORBAService
{
  public:
    virtual ~POA_Multiplier ();
    Multiplier_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static POA_Multiplier * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual CORBA::Long multiply( CORBA::Long x, CORBA::Long y ) = 0;

  protected:
    POA_Multiplier () {};

  private:
    POA_Multiplier (const POA_Multiplier &);
    void operator= (const POA_Multiplier &);
};

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_Multiplier;

#endif
