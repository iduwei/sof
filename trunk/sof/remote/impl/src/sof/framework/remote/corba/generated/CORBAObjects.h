/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __CORBAOBJECTS_H__
#define __CORBAOBJECTS_H__






namespace sof
{
namespace framework
{
namespace remote
{
namespace corba
{
namespace generated
{

class CORBAService;
typedef CORBAService *CORBAService_ptr;
typedef CORBAService_ptr CORBAServiceRef;
typedef ObjVar< CORBAService > CORBAService_var;
typedef ObjOut< CORBAService > CORBAService_out;

class CORBAServiceListener;
typedef CORBAServiceListener *CORBAServiceListener_ptr;
typedef CORBAServiceListener_ptr CORBAServiceListenerRef;
typedef ObjVar< CORBAServiceListener > CORBAServiceListener_var;
typedef ObjOut< CORBAServiceListener > CORBAServiceListener_out;

class CORBARegistryObserver;
typedef CORBARegistryObserver *CORBARegistryObserver_ptr;
typedef CORBARegistryObserver_ptr CORBARegistryObserverRef;
typedef ObjVar< CORBARegistryObserver > CORBARegistryObserver_var;
typedef ObjOut< CORBARegistryObserver > CORBARegistryObserver_out;

class CORBARegistry;
typedef CORBARegistry *CORBARegistry_ptr;
typedef CORBARegistry_ptr CORBARegistryRef;
typedef ObjVar< CORBARegistry > CORBARegistry_var;
typedef ObjOut< CORBARegistry > CORBARegistry_out;

}
}
}
}
}






namespace sof
{
namespace framework
{
namespace remote
{
namespace corba
{
namespace generated
{


/*
 * Base class and common definitions for interface CORBAService
 */

class CORBAService : 
  virtual public CORBA::Object
{
  public:
    virtual ~CORBAService();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef CORBAService_ptr _ptr_type;
    typedef CORBAService_var _var_type;
    #endif

    static CORBAService_ptr _narrow( CORBA::Object_ptr obj );
    static CORBAService_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static CORBAService_ptr _duplicate( CORBAService_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static CORBAService_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

  protected:
    CORBAService() {};
  private:
    CORBAService( const CORBAService& );
    void operator=( const CORBAService& );
};

// Stub for interface CORBAService
class CORBAService_stub:
  virtual public CORBAService
{
  public:
    virtual ~CORBAService_stub();
  private:
    void operator=( const CORBAService_stub& );
};

#ifndef MICO_CONF_NO_POA

class CORBAService_stub_clp :
  virtual public CORBAService_stub,
  virtual public PortableServer::StubBase
{
  public:
    CORBAService_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~CORBAService_stub_clp ();
  protected:
    CORBAService_stub_clp ();
  private:
    void operator=( const CORBAService_stub_clp & );
};

#endif // MICO_CONF_NO_POA

struct CORBAServiceProps;
typedef TVarVar< CORBAServiceProps > CORBAServiceProps_var;
typedef TVarOut< CORBAServiceProps > CORBAServiceProps_out;


struct CORBAServiceProps {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef CORBAServiceProps_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  CORBAServiceProps();
  ~CORBAServiceProps();
  CORBAServiceProps( const CORBAServiceProps& s );
  CORBAServiceProps& operator=( const CORBAServiceProps& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  typedef StringSequenceTmpl<CORBA::String_var> _keys_seq;
  _keys_seq keys;
  typedef StringSequenceTmpl<CORBA::String_var> _values_seq;
  _values_seq values;
};

struct CORBAServiceReference;
typedef TVarVar< CORBAServiceReference > CORBAServiceReference_var;
typedef TVarOut< CORBAServiceReference > CORBAServiceReference_out;


struct CORBAServiceReference {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef CORBAServiceReference_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  CORBAServiceReference();
  ~CORBAServiceReference();
  CORBAServiceReference( const CORBAServiceReference& s );
  CORBAServiceReference& operator=( const CORBAServiceReference& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  CORBA::String_var serviceName;
  CORBAServiceProps props;
  CORBAService_var service;
};

struct CORBAServiceEvent;
typedef TVarVar< CORBAServiceEvent > CORBAServiceEvent_var;
typedef TVarOut< CORBAServiceEvent > CORBAServiceEvent_out;


struct CORBAServiceEvent {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef CORBAServiceEvent_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  CORBAServiceEvent();
  ~CORBAServiceEvent();
  CORBAServiceEvent( const CORBAServiceEvent& s );
  CORBAServiceEvent& operator=( const CORBAServiceEvent& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  CORBA::Short serviceType;
  CORBAServiceReference serviceRef;
};


/*
 * Base class and common definitions for interface CORBAServiceListener
 */

class CORBAServiceListener : 
  virtual public CORBA::Object
{
  public:
    virtual ~CORBAServiceListener();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef CORBAServiceListener_ptr _ptr_type;
    typedef CORBAServiceListener_var _var_type;
    #endif

    static CORBAServiceListener_ptr _narrow( CORBA::Object_ptr obj );
    static CORBAServiceListener_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static CORBAServiceListener_ptr _duplicate( CORBAServiceListener_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static CORBAServiceListener_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual CORBA::Boolean serviceChanged( const ::sof::framework::remote::corba::generated::CORBAServiceEvent& serviceEvent ) = 0;

  protected:
    CORBAServiceListener() {};
  private:
    CORBAServiceListener( const CORBAServiceListener& );
    void operator=( const CORBAServiceListener& );
};

// Stub for interface CORBAServiceListener
class CORBAServiceListener_stub:
  virtual public CORBAServiceListener
{
  public:
    virtual ~CORBAServiceListener_stub();
    CORBA::Boolean serviceChanged( const ::sof::framework::remote::corba::generated::CORBAServiceEvent& serviceEvent );

  private:
    void operator=( const CORBAServiceListener_stub& );
};

#ifndef MICO_CONF_NO_POA

class CORBAServiceListener_stub_clp :
  virtual public CORBAServiceListener_stub,
  virtual public PortableServer::StubBase
{
  public:
    CORBAServiceListener_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~CORBAServiceListener_stub_clp ();
    CORBA::Boolean serviceChanged( const ::sof::framework::remote::corba::generated::CORBAServiceEvent& serviceEvent );

  protected:
    CORBAServiceListener_stub_clp ();
  private:
    void operator=( const CORBAServiceListener_stub_clp & );
};

#endif // MICO_CONF_NO_POA


/*
 * Base class and common definitions for interface CORBARegistryObserver
 */

class CORBARegistryObserver : 
  virtual public CORBA::Object
{
  public:
    virtual ~CORBARegistryObserver();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef CORBARegistryObserver_ptr _ptr_type;
    typedef CORBARegistryObserver_var _var_type;
    #endif

    static CORBARegistryObserver_ptr _narrow( CORBA::Object_ptr obj );
    static CORBARegistryObserver_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static CORBARegistryObserver_ptr _duplicate( CORBARegistryObserver_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static CORBARegistryObserver_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void ping() = 0;
    virtual void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;
    virtual void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;

  protected:
    CORBARegistryObserver() {};
  private:
    CORBARegistryObserver( const CORBARegistryObserver& );
    void operator=( const CORBARegistryObserver& );
};

// Stub for interface CORBARegistryObserver
class CORBARegistryObserver_stub:
  virtual public CORBARegistryObserver
{
  public:
    virtual ~CORBARegistryObserver_stub();
    void ping();
    void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );
    void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );

  private:
    void operator=( const CORBARegistryObserver_stub& );
};

#ifndef MICO_CONF_NO_POA

class CORBARegistryObserver_stub_clp :
  virtual public CORBARegistryObserver_stub,
  virtual public PortableServer::StubBase
{
  public:
    CORBARegistryObserver_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~CORBARegistryObserver_stub_clp ();
    void ping();
    void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );
    void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );

  protected:
    CORBARegistryObserver_stub_clp ();
  private:
    void operator=( const CORBARegistryObserver_stub_clp & );
};

#endif // MICO_CONF_NO_POA


/*
 * Base class and common definitions for interface CORBARegistry
 */

class CORBARegistry : 
  virtual public CORBA::Object
{
  public:
    virtual ~CORBARegistry();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef CORBARegistry_ptr _ptr_type;
    typedef CORBARegistry_var _var_type;
    #endif

    static CORBARegistry_ptr _narrow( CORBA::Object_ptr obj );
    static CORBARegistry_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static CORBARegistry_ptr _duplicate( CORBARegistry_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static CORBARegistry_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void addRegistryObserver( ::sof::framework::remote::corba::generated::CORBARegistryObserver_ptr observer ) = 0;
    virtual void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;
    virtual void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;

  protected:
    CORBARegistry() {};
  private:
    CORBARegistry( const CORBARegistry& );
    void operator=( const CORBARegistry& );
};

// Stub for interface CORBARegistry
class CORBARegistry_stub:
  virtual public CORBARegistry
{
  public:
    virtual ~CORBARegistry_stub();
    void addRegistryObserver( ::sof::framework::remote::corba::generated::CORBARegistryObserver_ptr observer );
    void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );
    void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );

  private:
    void operator=( const CORBARegistry_stub& );
};

#ifndef MICO_CONF_NO_POA

class CORBARegistry_stub_clp :
  virtual public CORBARegistry_stub,
  virtual public PortableServer::StubBase
{
  public:
    CORBARegistry_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~CORBARegistry_stub_clp ();
    void addRegistryObserver( ::sof::framework::remote::corba::generated::CORBARegistryObserver_ptr observer );
    void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );
    void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props );
    void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener );

  protected:
    CORBARegistry_stub_clp ();
  private:
    void operator=( const CORBARegistry_stub_clp & );
};

#endif // MICO_CONF_NO_POA

}
}
}
}
}


#ifndef MICO_CONF_NO_POA



namespace POA_sof
{
namespace framework
{
namespace remote
{
namespace corba
{
namespace generated
{

class CORBAService : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~CORBAService ();
    sof::framework::remote::corba::generated::CORBAService_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static CORBAService * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

  protected:
    CORBAService () {};

  private:
    CORBAService (const CORBAService &);
    void operator= (const CORBAService &);
};

class CORBAServiceListener : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~CORBAServiceListener ();
    sof::framework::remote::corba::generated::CORBAServiceListener_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static CORBAServiceListener * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual CORBA::Boolean serviceChanged( const ::sof::framework::remote::corba::generated::CORBAServiceEvent& serviceEvent ) = 0;

  protected:
    CORBAServiceListener () {};

  private:
    CORBAServiceListener (const CORBAServiceListener &);
    void operator= (const CORBAServiceListener &);
};

class CORBARegistryObserver : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~CORBARegistryObserver ();
    sof::framework::remote::corba::generated::CORBARegistryObserver_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static CORBARegistryObserver * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void ping() = 0;
    virtual void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;
    virtual void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;

  protected:
    CORBARegistryObserver () {};

  private:
    CORBARegistryObserver (const CORBARegistryObserver &);
    void operator= (const CORBARegistryObserver &);
};

class CORBARegistry : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~CORBARegistry ();
    sof::framework::remote::corba::generated::CORBARegistry_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static CORBARegistry * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void addRegistryObserver( ::sof::framework::remote::corba::generated::CORBARegistryObserver_ptr observer ) = 0;
    virtual void registerService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void registerServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;
    virtual void unregisterService( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAService_ptr service, const ::sof::framework::remote::corba::generated::CORBAServiceProps& props ) = 0;
    virtual void unregisterServiceListener( const char* bundleName, const char* serviceName, ::sof::framework::remote::corba::generated::CORBAServiceListener_ptr listener ) = 0;

  protected:
    CORBARegistry () {};

  private:
    CORBARegistry (const CORBARegistry &);
    void operator= (const CORBARegistry &);
};

}
}
}
}
}


#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAService;

extern CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceProps;

extern CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceReference;

extern CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent;

extern CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceListener;

extern CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver;

extern CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBARegistry;

#endif
