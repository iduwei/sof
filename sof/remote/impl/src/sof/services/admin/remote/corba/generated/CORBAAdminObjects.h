/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __CORBAADMINOBJECTS_H__
#define __CORBAADMINOBJECTS_H__






namespace sof
{
namespace services
{
namespace admin
{
namespace remote
{
namespace corba
{
namespace generated
{

class CORBAAdminService;
typedef CORBAAdminService *CORBAAdminService_ptr;
typedef CORBAAdminService_ptr CORBAAdminServiceRef;
typedef ObjVar< CORBAAdminService > CORBAAdminService_var;
typedef ObjOut< CORBAAdminService > CORBAAdminService_out;

}
}
}
}
}
}






namespace sof
{
namespace services
{
namespace admin
{
namespace remote
{
namespace corba
{
namespace generated
{

typedef StringSequenceTmpl<CORBA::String_var> CORBAPropertyKeysSequence;
typedef TSeqVar< StringSequenceTmpl<CORBA::String_var> > CORBAPropertyKeysSequence_var;
typedef TSeqOut< StringSequenceTmpl<CORBA::String_var> > CORBAPropertyKeysSequence_out;

typedef StringSequenceTmpl<CORBA::String_var> CORBAPropertyValuesSequence;
typedef TSeqVar< StringSequenceTmpl<CORBA::String_var> > CORBAPropertyValuesSequence_var;
typedef TSeqOut< StringSequenceTmpl<CORBA::String_var> > CORBAPropertyValuesSequence_out;

struct CORBAAdminServiceProps;
typedef TVarVar< CORBAAdminServiceProps > CORBAAdminServiceProps_var;
typedef TVarOut< CORBAAdminServiceProps > CORBAAdminServiceProps_out;


struct CORBAAdminServiceProps {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef CORBAAdminServiceProps_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  CORBAAdminServiceProps();
  ~CORBAAdminServiceProps();
  CORBAAdminServiceProps( const CORBAAdminServiceProps& s );
  CORBAAdminServiceProps& operator=( const CORBAAdminServiceProps& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  CORBAPropertyKeysSequence keys;
  CORBAPropertyValuesSequence values;
};

struct CORBAAdminServiceInfo;
typedef TVarVar< CORBAAdminServiceInfo > CORBAAdminServiceInfo_var;
typedef TVarOut< CORBAAdminServiceInfo > CORBAAdminServiceInfo_out;


struct CORBAAdminServiceInfo {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef CORBAAdminServiceInfo_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  CORBAAdminServiceInfo();
  ~CORBAAdminServiceInfo();
  CORBAAdminServiceInfo( const CORBAAdminServiceInfo& s );
  CORBAAdminServiceInfo& operator=( const CORBAAdminServiceInfo& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  CORBA::String_var serviceName;
  CORBAAdminServiceProps properties;
  CORBA::String_var objID;
};

struct CORBAAdminServiceListenerInfo;
typedef TVarVar< CORBAAdminServiceListenerInfo > CORBAAdminServiceListenerInfo_var;
typedef TVarOut< CORBAAdminServiceListenerInfo > CORBAAdminServiceListenerInfo_out;


struct CORBAAdminServiceListenerInfo {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef CORBAAdminServiceListenerInfo_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  CORBAAdminServiceListenerInfo();
  ~CORBAAdminServiceListenerInfo();
  CORBAAdminServiceListenerInfo( const CORBAAdminServiceListenerInfo& s );
  CORBAAdminServiceListenerInfo& operator=( const CORBAAdminServiceListenerInfo& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  CORBA::String_var serviceName;
};

typedef SequenceTmpl< CORBAAdminServiceInfo,MICO_TID_DEF> CORBAAdminServiceInfoSequence;
typedef TSeqVar< SequenceTmpl< CORBAAdminServiceInfo,MICO_TID_DEF> > CORBAAdminServiceInfoSequence_var;
typedef TSeqOut< SequenceTmpl< CORBAAdminServiceInfo,MICO_TID_DEF> > CORBAAdminServiceInfoSequence_out;

typedef SequenceTmpl< CORBAAdminServiceListenerInfo,MICO_TID_DEF> CORBAAdminServiceListenerInfoSequence;
typedef TSeqVar< SequenceTmpl< CORBAAdminServiceListenerInfo,MICO_TID_DEF> > CORBAAdminServiceListenerInfoSequence_var;
typedef TSeqOut< SequenceTmpl< CORBAAdminServiceListenerInfo,MICO_TID_DEF> > CORBAAdminServiceListenerInfoSequence_out;

typedef StringSequenceTmpl<CORBA::String_var> CORBABundleNameSequence;
typedef TSeqVar< StringSequenceTmpl<CORBA::String_var> > CORBABundleNameSequence_var;
typedef TSeqOut< StringSequenceTmpl<CORBA::String_var> > CORBABundleNameSequence_out;


/*
 * Base class and common definitions for interface CORBAAdminService
 */

class CORBAAdminService : 
  virtual public CORBA::Object
{
  public:
    virtual ~CORBAAdminService();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef CORBAAdminService_ptr _ptr_type;
    typedef CORBAAdminService_var _var_type;
    #endif

    static CORBAAdminService_ptr _narrow( CORBA::Object_ptr obj );
    static CORBAAdminService_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static CORBAAdminService_ptr _duplicate( CORBAAdminService_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static CORBAAdminService_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual ::sof::services::admin::remote::corba::generated::CORBABundleNameSequence* getBundleNames() = 0;
    virtual ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getUsedServices( const char* bundleName ) = 0;
    virtual ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getRegisteredServices( const char* bundleName ) = 0;
    virtual ::sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence* getRegisteredServiceListeners( const char* bundleName ) = 0;

  protected:
    CORBAAdminService() {};
  private:
    CORBAAdminService( const CORBAAdminService& );
    void operator=( const CORBAAdminService& );
};

// Stub for interface CORBAAdminService
class CORBAAdminService_stub:
  virtual public CORBAAdminService
{
  public:
    virtual ~CORBAAdminService_stub();
    ::sof::services::admin::remote::corba::generated::CORBABundleNameSequence* getBundleNames();
    ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getUsedServices( const char* bundleName );
    ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getRegisteredServices( const char* bundleName );
    ::sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence* getRegisteredServiceListeners( const char* bundleName );

  private:
    void operator=( const CORBAAdminService_stub& );
};

#ifndef MICO_CONF_NO_POA

class CORBAAdminService_stub_clp :
  virtual public CORBAAdminService_stub,
  virtual public PortableServer::StubBase
{
  public:
    CORBAAdminService_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~CORBAAdminService_stub_clp ();
    ::sof::services::admin::remote::corba::generated::CORBABundleNameSequence* getBundleNames();
    ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getUsedServices( const char* bundleName );
    ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getRegisteredServices( const char* bundleName );
    ::sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence* getRegisteredServiceListeners( const char* bundleName );

  protected:
    CORBAAdminService_stub_clp ();
  private:
    void operator=( const CORBAAdminService_stub_clp & );
};

#endif // MICO_CONF_NO_POA

}
}
}
}
}
}


#ifndef MICO_CONF_NO_POA



namespace POA_sof
{
namespace services
{
namespace admin
{
namespace remote
{
namespace corba
{
namespace generated
{

class CORBAAdminService : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~CORBAAdminService ();
    sof::services::admin::remote::corba::generated::CORBAAdminService_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static CORBAAdminService * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual ::sof::services::admin::remote::corba::generated::CORBABundleNameSequence* getBundleNames() = 0;
    virtual ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getUsedServices( const char* bundleName ) = 0;
    virtual ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* getRegisteredServices( const char* bundleName ) = 0;
    virtual ::sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence* getRegisteredServiceListeners( const char* bundleName ) = 0;

  protected:
    CORBAAdminService () {};

  private:
    CORBAAdminService (const CORBAAdminService &);
    void operator= (const CORBAAdminService &);
};

}
}
}
}
}
}


#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps;

extern CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo;

extern CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo;

extern CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService;

extern CORBA::StaticTypeInfo *_marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo;

extern CORBA::StaticTypeInfo *_marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo;

#endif
