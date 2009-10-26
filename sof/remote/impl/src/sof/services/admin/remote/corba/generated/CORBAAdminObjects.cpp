/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "CORBAAdminObjects.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------


#ifdef HAVE_EXPLICIT_STRUCT_OPS
sof::services::admin::remote::corba::generated::CORBAAdminServiceProps::CORBAAdminServiceProps()
{
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceProps::CORBAAdminServiceProps( const CORBAAdminServiceProps& _s )
{
  keys = ((CORBAAdminServiceProps&)_s).keys;
  values = ((CORBAAdminServiceProps&)_s).values;
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceProps::~CORBAAdminServiceProps()
{
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceProps&
sof::services::admin::remote::corba::generated::CORBAAdminServiceProps::operator=( const CORBAAdminServiceProps& _s )
{
  keys = ((CORBAAdminServiceProps&)_s).keys;
  values = ((CORBAAdminServiceProps&)_s).values;
  return *this;
}
#endif

class _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps : public ::CORBA::StaticTypeInfo {
    typedef sof::services::admin::remote::corba::generated::CORBAAdminServiceProps _MICO_T;
  public:
    ~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps::~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps()
{
}

::CORBA::StaticValueType _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->keys ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->values ) &&
    dc.struct_end();
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->keys );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->values );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps;

#ifdef HAVE_EXPLICIT_STRUCT_OPS
sof::services::admin::remote::corba::generated::CORBAAdminServiceInfo::CORBAAdminServiceInfo()
{
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceInfo::CORBAAdminServiceInfo( const CORBAAdminServiceInfo& _s )
{
  serviceName = ((CORBAAdminServiceInfo&)_s).serviceName;
  properties = ((CORBAAdminServiceInfo&)_s).properties;
  objID = ((CORBAAdminServiceInfo&)_s).objID;
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceInfo::~CORBAAdminServiceInfo()
{
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceInfo&
sof::services::admin::remote::corba::generated::CORBAAdminServiceInfo::operator=( const CORBAAdminServiceInfo& _s )
{
  serviceName = ((CORBAAdminServiceInfo&)_s).serviceName;
  properties = ((CORBAAdminServiceInfo&)_s).properties;
  objID = ((CORBAAdminServiceInfo&)_s).objID;
  return *this;
}
#endif

class _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo : public ::CORBA::StaticTypeInfo {
    typedef sof::services::admin::remote::corba::generated::CORBAAdminServiceInfo _MICO_T;
  public:
    ~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo()
{
}

::CORBA::StaticValueType _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->serviceName._for_demarshal() ) &&
    _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps->demarshal( dc, &((_MICO_T*)v)->properties ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->objID._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->serviceName.inout() );
  _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps->marshal( ec, &((_MICO_T*)v)->properties );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->objID.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo;

#ifdef HAVE_EXPLICIT_STRUCT_OPS
sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfo::CORBAAdminServiceListenerInfo()
{
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfo::CORBAAdminServiceListenerInfo( const CORBAAdminServiceListenerInfo& _s )
{
  serviceName = ((CORBAAdminServiceListenerInfo&)_s).serviceName;
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfo::~CORBAAdminServiceListenerInfo()
{
}

sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfo&
sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfo::operator=( const CORBAAdminServiceListenerInfo& _s )
{
  serviceName = ((CORBAAdminServiceListenerInfo&)_s).serviceName;
  return *this;
}
#endif

class _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo : public ::CORBA::StaticTypeInfo {
    typedef sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfo _MICO_T;
  public:
    ~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo()
{
}

::CORBA::StaticValueType _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->serviceName._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->serviceName.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo;





/*
 * Base interface for class CORBAAdminService
 */

sof::services::admin::remote::corba::generated::CORBAAdminService::~CORBAAdminService()
{
}

void *
sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

sof::services::admin::remote::corba::generated::CORBAAdminService_ptr
sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow( CORBA::Object_ptr _obj )
{
  sof::services::admin::remote::corba::generated::CORBAAdminService_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0" )))
      return _duplicate( (sof::services::admin::remote::corba::generated::CORBAAdminService_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0") || _obj->_is_a_remote ("IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0")) {
      _o = new sof::services::admin::remote::corba::generated::CORBAAdminService_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

sof::services::admin::remote::corba::generated::CORBAAdminService_ptr
sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService : public ::CORBA::StaticTypeInfo {
    typedef sof::services::admin::remote::corba::generated::CORBAAdminService_ptr _MICO_T;
  public:
    ~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService::~_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService()
{
}

::CORBA::StaticValueType _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::sof::services::admin::remote::corba::generated::CORBAAdminService::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService;


/*
 * Stub interface for class CORBAAdminService
 */

sof::services::admin::remote::corba::generated::CORBAAdminService_stub::~CORBAAdminService_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_sof::services::admin::remote::corba::generated::CORBAAdminService *
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_sof::services::admin::remote::corba::generated::CORBAAdminService *) p;
  }
  return NULL;
}

sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp::CORBAAdminService_stub_clp ()
{
}

sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp::CORBAAdminService_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp::~CORBAAdminService_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBABundleNameSequence* sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getBundleNames()
{
  CORBA::StaticAny __res( CORBA::_stcseq_string );

  CORBA::StaticRequest __req( this, "getBundleNames" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (sof::services::admin::remote::corba::generated::CORBABundleNameSequence*) __res._retn();
}


#ifndef MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBABundleNameSequence*
sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp::getBundleNames()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::services::admin::remote::corba::generated::CORBAAdminService * _myserv = POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow (_serv);
    if (_myserv) {
      sof::services::admin::remote::corba::generated::CORBABundleNameSequence* __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->getBundleNames();
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getBundleNames();
}

#endif // MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getUsedServices( const char* _par_bundleName )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny __res( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo );

  CORBA::StaticRequest __req( this, "getUsedServices" );
  __req.add_in_arg( &_sa_bundleName );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence*) __res._retn();
}


#ifndef MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence*
sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp::getUsedServices( const char* _par_bundleName )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::services::admin::remote::corba::generated::CORBAAdminService * _myserv = POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow (_serv);
    if (_myserv) {
      sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->getUsedServices(_par_bundleName);
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getUsedServices(_par_bundleName);
}

#endif // MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getRegisteredServices( const char* _par_bundleName )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny __res( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo );

  CORBA::StaticRequest __req( this, "getRegisteredServices" );
  __req.add_in_arg( &_sa_bundleName );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence*) __res._retn();
}


#ifndef MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence*
sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp::getRegisteredServices( const char* _par_bundleName )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::services::admin::remote::corba::generated::CORBAAdminService * _myserv = POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow (_serv);
    if (_myserv) {
      sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->getRegisteredServices(_par_bundleName);
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getRegisteredServices(_par_bundleName);
}

#endif // MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence* sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getRegisteredServiceListeners( const char* _par_bundleName )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny __res( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo );

  CORBA::StaticRequest __req( this, "getRegisteredServiceListeners" );
  __req.add_in_arg( &_sa_bundleName );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence*) __res._retn();
}


#ifndef MICO_CONF_NO_POA

sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence*
sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp::getRegisteredServiceListeners( const char* _par_bundleName )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::services::admin::remote::corba::generated::CORBAAdminService * _myserv = POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow (_serv);
    if (_myserv) {
      sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence* __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->getRegisteredServiceListeners(_par_bundleName);
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return sof::services::admin::remote::corba::generated::CORBAAdminService_stub::getRegisteredServiceListeners(_par_bundleName);
}

#endif // MICO_CONF_NO_POA

class _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< sof::services::admin::remote::corba::generated::CORBAAdminServiceInfo,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::~_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo()
{
}

::CORBA::StaticValueType _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo;

class _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfo,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::~_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo()
{
}

::CORBA::StaticValueType _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo;

struct __tc_init_CORBAADMINOBJECTS {
  __tc_init_CORBAADMINOBJECTS()
  {
    _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps = new _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps;
    _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo = new _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo;
    _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo = new _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo;
    _marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService = new _Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService;
    _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo = new _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo;
    _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo = new _Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo;
  }

  ~__tc_init_CORBAADMINOBJECTS()
  {
    delete static_cast<_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps*>(_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceProps);
    delete static_cast<_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo*>(_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo);
    delete static_cast<_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo*>(_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo);
    delete static_cast<_Marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService*>(_marshaller_sof_services_admin_remote_corba_generated_CORBAAdminService);
    delete static_cast<_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo*>(_marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo);
    delete static_cast<_Marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo*>(_marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo);
  }
};

static __tc_init_CORBAADMINOBJECTS __init_CORBAADMINOBJECTS;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface sof::services::admin::remote::corba::generated::CORBAAdminService
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::~CORBAAdminService()
{
}

::sof::services::admin::remote::corba::generated::CORBAAdminService_ptr
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::sof::services::admin::remote::corba::generated::CORBAAdminService::_narrow (obj);
}

CORBA::Boolean
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0");
}

CORBA::Object_ptr
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::sof::services::admin::remote::corba::generated::CORBAAdminService_stub_clp (poa, obj);
}

bool
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    switch (mico_string_hash (__req->op_name(), 7)) {
    case 0:
      if( strcmp( __req->op_name(), "getRegisteredServiceListeners" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );

        ::sof::services::admin::remote::corba::generated::CORBAAdminServiceListenerInfoSequence* _res;
        CORBA::StaticAny __res( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo );
        __req->add_in_arg( &_sa_bundleName );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = getRegisteredServiceListeners( _par_bundleName.inout() );
        __res.value( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceListenerInfo, _res );
        __req->write_results();
        delete _res;
        return true;
      }
      break;
    case 5:
      if( strcmp( __req->op_name(), "getBundleNames" ) == 0 ) {
        ::sof::services::admin::remote::corba::generated::CORBABundleNameSequence* _res;
        CORBA::StaticAny __res( CORBA::_stcseq_string );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = getBundleNames();
        __res.value( CORBA::_stcseq_string, _res );
        __req->write_results();
        delete _res;
        return true;
      }
      if( strcmp( __req->op_name(), "getUsedServices" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );

        ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* _res;
        CORBA::StaticAny __res( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo );
        __req->add_in_arg( &_sa_bundleName );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = getUsedServices( _par_bundleName.inout() );
        __res.value( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo, _res );
        __req->write_results();
        delete _res;
        return true;
      }
      if( strcmp( __req->op_name(), "getRegisteredServices" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );

        ::sof::services::admin::remote::corba::generated::CORBAAdminServiceInfoSequence* _res;
        CORBA::StaticAny __res( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo );
        __req->add_in_arg( &_sa_bundleName );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = getRegisteredServices( _par_bundleName.inout() );
        __res.value( _marshaller__seq_sof_services_admin_remote_corba_generated_CORBAAdminServiceInfo, _res );
        __req->write_results();
        delete _res;
        return true;
      }
      break;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    __req->set_exception( _ex->_clone() );
    __req->write_results();
    return true;
  } catch( ... ) {
    CORBA::UNKNOWN _ex (CORBA::OMGVMCID | 1, CORBA::COMPLETED_MAYBE);
    __req->set_exception (_ex->_clone());
    __req->write_results ();
    return true;
  }
  #endif

  return false;
}

void
POA_sof::services::admin::remote::corba::generated::CORBAAdminService::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

