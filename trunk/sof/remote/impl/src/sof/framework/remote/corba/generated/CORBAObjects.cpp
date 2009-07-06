/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBAObjects.h>


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class CORBAService
 */

sof::framework::remote::corba::generated::CORBAService::~CORBAService()
{
}

void *
sof::framework::remote::corba::generated::CORBAService::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:sof/framework/remote/corba/generated/CORBAService:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

sof::framework::remote::corba::generated::CORBAService_ptr
sof::framework::remote::corba::generated::CORBAService::_narrow( CORBA::Object_ptr _obj )
{
  sof::framework::remote::corba::generated::CORBAService_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:sof/framework/remote/corba/generated/CORBAService:1.0" )))
      return _duplicate( (sof::framework::remote::corba::generated::CORBAService_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:sof/framework/remote/corba/generated/CORBAService:1.0") || _obj->_is_a_remote ("IDL:sof/framework/remote/corba/generated/CORBAService:1.0")) {
      _o = new sof::framework::remote::corba::generated::CORBAService_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

sof::framework::remote::corba::generated::CORBAService_ptr
sof::framework::remote::corba::generated::CORBAService::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_sof_framework_remote_corba_generated_CORBAService : public ::CORBA::StaticTypeInfo {
    typedef sof::framework::remote::corba::generated::CORBAService_ptr _MICO_T;
  public:
    ~_Marshaller_sof_framework_remote_corba_generated_CORBAService();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_framework_remote_corba_generated_CORBAService::~_Marshaller_sof_framework_remote_corba_generated_CORBAService()
{
}

::CORBA::StaticValueType _Marshaller_sof_framework_remote_corba_generated_CORBAService::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAService::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::sof::framework::remote::corba::generated::CORBAService::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAService::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAService::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_sof_framework_remote_corba_generated_CORBAService::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::sof::framework::remote::corba::generated::CORBAService::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAService::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAService;


/*
 * Stub interface for class CORBAService
 */

sof::framework::remote::corba::generated::CORBAService_stub::~CORBAService_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_sof::framework::remote::corba::generated::CORBAService::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBAService:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_sof::framework::remote::corba::generated::CORBAService *
POA_sof::framework::remote::corba::generated::CORBAService::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:sof/framework/remote/corba/generated/CORBAService:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_sof::framework::remote::corba::generated::CORBAService *) p;
  }
  return NULL;
}

sof::framework::remote::corba::generated::CORBAService_stub_clp::CORBAService_stub_clp ()
{
}

sof::framework::remote::corba::generated::CORBAService_stub_clp::CORBAService_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

sof::framework::remote::corba::generated::CORBAService_stub_clp::~CORBAService_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

#ifdef HAVE_EXPLICIT_STRUCT_OPS
sof::framework::remote::corba::generated::CORBAServiceProps::CORBAServiceProps()
{
}

sof::framework::remote::corba::generated::CORBAServiceProps::CORBAServiceProps( const CORBAServiceProps& _s )
{
  keys = ((CORBAServiceProps&)_s).keys;
  values = ((CORBAServiceProps&)_s).values;
}

sof::framework::remote::corba::generated::CORBAServiceProps::~CORBAServiceProps()
{
}

sof::framework::remote::corba::generated::CORBAServiceProps&
sof::framework::remote::corba::generated::CORBAServiceProps::operator=( const CORBAServiceProps& _s )
{
  keys = ((CORBAServiceProps&)_s).keys;
  values = ((CORBAServiceProps&)_s).values;
  return *this;
}
#endif

class _Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps : public ::CORBA::StaticTypeInfo {
    typedef sof::framework::remote::corba::generated::CORBAServiceProps _MICO_T;
  public:
    ~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps::~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps()
{
}

::CORBA::StaticValueType _Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->keys ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->values ) &&
    dc.struct_end();
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->keys );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->values );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceProps;

#ifdef HAVE_EXPLICIT_STRUCT_OPS
sof::framework::remote::corba::generated::CORBAServiceReference::CORBAServiceReference()
{
}

sof::framework::remote::corba::generated::CORBAServiceReference::CORBAServiceReference( const CORBAServiceReference& _s )
{
  serviceName = ((CORBAServiceReference&)_s).serviceName;
  props = ((CORBAServiceReference&)_s).props;
  service = ((CORBAServiceReference&)_s).service;
}

sof::framework::remote::corba::generated::CORBAServiceReference::~CORBAServiceReference()
{
}

sof::framework::remote::corba::generated::CORBAServiceReference&
sof::framework::remote::corba::generated::CORBAServiceReference::operator=( const CORBAServiceReference& _s )
{
  serviceName = ((CORBAServiceReference&)_s).serviceName;
  props = ((CORBAServiceReference&)_s).props;
  service = ((CORBAServiceReference&)_s).service;
  return *this;
}
#endif

class _Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference : public ::CORBA::StaticTypeInfo {
    typedef sof::framework::remote::corba::generated::CORBAServiceReference _MICO_T;
  public:
    ~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference::~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference()
{
}

::CORBA::StaticValueType _Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->serviceName._for_demarshal() ) &&
    _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps->demarshal( dc, &((_MICO_T*)v)->props ) &&
    _marshaller_sof_framework_remote_corba_generated_CORBAService->demarshal( dc, &((_MICO_T*)v)->service._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->serviceName.inout() );
  _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps->marshal( ec, &((_MICO_T*)v)->props );
  _marshaller_sof_framework_remote_corba_generated_CORBAService->marshal( ec, &((_MICO_T*)v)->service.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceReference;

#ifdef HAVE_EXPLICIT_STRUCT_OPS
sof::framework::remote::corba::generated::CORBAServiceEvent::CORBAServiceEvent()
{
}

sof::framework::remote::corba::generated::CORBAServiceEvent::CORBAServiceEvent( const CORBAServiceEvent& _s )
{
  serviceType = ((CORBAServiceEvent&)_s).serviceType;
  serviceRef = ((CORBAServiceEvent&)_s).serviceRef;
}

sof::framework::remote::corba::generated::CORBAServiceEvent::~CORBAServiceEvent()
{
}

sof::framework::remote::corba::generated::CORBAServiceEvent&
sof::framework::remote::corba::generated::CORBAServiceEvent::operator=( const CORBAServiceEvent& _s )
{
  serviceType = ((CORBAServiceEvent&)_s).serviceType;
  serviceRef = ((CORBAServiceEvent&)_s).serviceRef;
  return *this;
}
#endif

class _Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent : public ::CORBA::StaticTypeInfo {
    typedef sof::framework::remote::corba::generated::CORBAServiceEvent _MICO_T;
  public:
    ~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent::~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent()
{
}

::CORBA::StaticValueType _Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_short->demarshal( dc, &((_MICO_T*)v)->serviceType ) &&
    _marshaller_sof_framework_remote_corba_generated_CORBAServiceReference->demarshal( dc, &((_MICO_T*)v)->serviceRef ) &&
    dc.struct_end();
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_short->marshal( ec, &((_MICO_T*)v)->serviceType );
  _marshaller_sof_framework_remote_corba_generated_CORBAServiceReference->marshal( ec, &((_MICO_T*)v)->serviceRef );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent;


/*
 * Base interface for class CORBAServiceListener
 */

sof::framework::remote::corba::generated::CORBAServiceListener::~CORBAServiceListener()
{
}

void *
sof::framework::remote::corba::generated::CORBAServiceListener::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

sof::framework::remote::corba::generated::CORBAServiceListener_ptr
sof::framework::remote::corba::generated::CORBAServiceListener::_narrow( CORBA::Object_ptr _obj )
{
  sof::framework::remote::corba::generated::CORBAServiceListener_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0" )))
      return _duplicate( (sof::framework::remote::corba::generated::CORBAServiceListener_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0") || _obj->_is_a_remote ("IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0")) {
      _o = new sof::framework::remote::corba::generated::CORBAServiceListener_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

sof::framework::remote::corba::generated::CORBAServiceListener_ptr
sof::framework::remote::corba::generated::CORBAServiceListener::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener : public ::CORBA::StaticTypeInfo {
    typedef sof::framework::remote::corba::generated::CORBAServiceListener_ptr _MICO_T;
  public:
    ~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener::~_Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener()
{
}

::CORBA::StaticValueType _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::sof::framework::remote::corba::generated::CORBAServiceListener::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::sof::framework::remote::corba::generated::CORBAServiceListener::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBAServiceListener;


/*
 * Stub interface for class CORBAServiceListener
 */

sof::framework::remote::corba::generated::CORBAServiceListener_stub::~CORBAServiceListener_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_sof::framework::remote::corba::generated::CORBAServiceListener::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_sof::framework::remote::corba::generated::CORBAServiceListener *
POA_sof::framework::remote::corba::generated::CORBAServiceListener::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_sof::framework::remote::corba::generated::CORBAServiceListener *) p;
  }
  return NULL;
}

sof::framework::remote::corba::generated::CORBAServiceListener_stub_clp::CORBAServiceListener_stub_clp ()
{
}

sof::framework::remote::corba::generated::CORBAServiceListener_stub_clp::CORBAServiceListener_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

sof::framework::remote::corba::generated::CORBAServiceListener_stub_clp::~CORBAServiceListener_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

CORBA::Boolean sof::framework::remote::corba::generated::CORBAServiceListener_stub::serviceChanged( const sof::framework::remote::corba::generated::CORBAServiceEvent& _par_serviceEvent )
{
  CORBA::StaticAny _sa_serviceEvent( _marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent, &_par_serviceEvent );
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "serviceChanged" );
  __req.add_in_arg( &_sa_serviceEvent );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifndef MICO_CONF_NO_POA

CORBA::Boolean
sof::framework::remote::corba::generated::CORBAServiceListener_stub_clp::serviceChanged( const sof::framework::remote::corba::generated::CORBAServiceEvent& _par_serviceEvent )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBAServiceListener * _myserv = POA_sof::framework::remote::corba::generated::CORBAServiceListener::_narrow (_serv);
    if (_myserv) {
      CORBA::Boolean __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->serviceChanged(_par_serviceEvent);
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

  return sof::framework::remote::corba::generated::CORBAServiceListener_stub::serviceChanged(_par_serviceEvent);
}

#endif // MICO_CONF_NO_POA


/*
 * Base interface for class CORBARegistryObserver
 */

sof::framework::remote::corba::generated::CORBARegistryObserver::~CORBARegistryObserver()
{
}

void *
sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

sof::framework::remote::corba::generated::CORBARegistryObserver_ptr
sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow( CORBA::Object_ptr _obj )
{
  sof::framework::remote::corba::generated::CORBARegistryObserver_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0" )))
      return _duplicate( (sof::framework::remote::corba::generated::CORBARegistryObserver_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0") || _obj->_is_a_remote ("IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0")) {
      _o = new sof::framework::remote::corba::generated::CORBARegistryObserver_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

sof::framework::remote::corba::generated::CORBARegistryObserver_ptr
sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver : public ::CORBA::StaticTypeInfo {
    typedef sof::framework::remote::corba::generated::CORBARegistryObserver_ptr _MICO_T;
  public:
    ~_Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver::~_Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver()
{
}

::CORBA::StaticValueType _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::sof::framework::remote::corba::generated::CORBARegistryObserver::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver;


/*
 * Stub interface for class CORBARegistryObserver
 */

sof::framework::remote::corba::generated::CORBARegistryObserver_stub::~CORBARegistryObserver_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_sof::framework::remote::corba::generated::CORBARegistryObserver *
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_sof::framework::remote::corba::generated::CORBARegistryObserver *) p;
  }
  return NULL;
}

sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::CORBARegistryObserver_stub_clp ()
{
}

sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::CORBARegistryObserver_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::~CORBARegistryObserver_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistryObserver_stub::ping()
{
  CORBA::StaticRequest __req( this, "ping" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::ping()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistryObserver * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->ping();
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistryObserver_stub::ping();
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistryObserver_stub::registerService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service );
  CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );
  CORBA::StaticRequest __req( this, "registerService" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_service );
  __req.add_in_arg( &_sa_props );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::registerService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistryObserver * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->registerService(_par_bundleName, _par_serviceName, _par_service, _par_props);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistryObserver_stub::registerService(_par_bundleName, _par_serviceName, _par_service, _par_props);
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistryObserver_stub::registerServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener );
  CORBA::StaticRequest __req( this, "registerServiceListener" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_listener );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::registerServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistryObserver * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->registerServiceListener(_par_bundleName, _par_serviceName, _par_listener);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistryObserver_stub::registerServiceListener(_par_bundleName, _par_serviceName, _par_listener);
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistryObserver_stub::unregisterService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service );
  CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );
  CORBA::StaticRequest __req( this, "unregisterService" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_service );
  __req.add_in_arg( &_sa_props );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::unregisterService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistryObserver * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->unregisterService(_par_bundleName, _par_serviceName, _par_service, _par_props);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistryObserver_stub::unregisterService(_par_bundleName, _par_serviceName, _par_service, _par_props);
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistryObserver_stub::unregisterServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener );
  CORBA::StaticRequest __req( this, "unregisterServiceListener" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_listener );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp::unregisterServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistryObserver * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->unregisterServiceListener(_par_bundleName, _par_serviceName, _par_listener);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistryObserver_stub::unregisterServiceListener(_par_bundleName, _par_serviceName, _par_listener);
}

#endif // MICO_CONF_NO_POA


/*
 * Base interface for class CORBARegistry
 */

sof::framework::remote::corba::generated::CORBARegistry::~CORBARegistry()
{
}

void *
sof::framework::remote::corba::generated::CORBARegistry::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

sof::framework::remote::corba::generated::CORBARegistry_ptr
sof::framework::remote::corba::generated::CORBARegistry::_narrow( CORBA::Object_ptr _obj )
{
  sof::framework::remote::corba::generated::CORBARegistry_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0" )))
      return _duplicate( (sof::framework::remote::corba::generated::CORBARegistry_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0") || _obj->_is_a_remote ("IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0")) {
      _o = new sof::framework::remote::corba::generated::CORBARegistry_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

sof::framework::remote::corba::generated::CORBARegistry_ptr
sof::framework::remote::corba::generated::CORBARegistry::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_sof_framework_remote_corba_generated_CORBARegistry : public ::CORBA::StaticTypeInfo {
    typedef sof::framework::remote::corba::generated::CORBARegistry_ptr _MICO_T;
  public:
    ~_Marshaller_sof_framework_remote_corba_generated_CORBARegistry();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_sof_framework_remote_corba_generated_CORBARegistry::~_Marshaller_sof_framework_remote_corba_generated_CORBARegistry()
{
}

::CORBA::StaticValueType _Marshaller_sof_framework_remote_corba_generated_CORBARegistry::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistry::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::sof::framework::remote::corba::generated::CORBARegistry::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistry::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistry::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_sof_framework_remote_corba_generated_CORBARegistry::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::sof::framework::remote::corba::generated::CORBARegistry::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_sof_framework_remote_corba_generated_CORBARegistry::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_sof_framework_remote_corba_generated_CORBARegistry;


/*
 * Stub interface for class CORBARegistry
 */

sof::framework::remote::corba::generated::CORBARegistry_stub::~CORBARegistry_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_sof::framework::remote::corba::generated::CORBARegistry::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_sof::framework::remote::corba::generated::CORBARegistry *
POA_sof::framework::remote::corba::generated::CORBARegistry::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_sof::framework::remote::corba::generated::CORBARegistry *) p;
  }
  return NULL;
}

sof::framework::remote::corba::generated::CORBARegistry_stub_clp::CORBARegistry_stub_clp ()
{
}

sof::framework::remote::corba::generated::CORBARegistry_stub_clp::CORBARegistry_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

sof::framework::remote::corba::generated::CORBARegistry_stub_clp::~CORBARegistry_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistry_stub::addRegistryObserver( sof::framework::remote::corba::generated::CORBARegistryObserver_ptr _par_observer )
{
  CORBA::StaticAny _sa_observer( _marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver, &_par_observer );
  CORBA::StaticRequest __req( this, "addRegistryObserver" );
  __req.add_in_arg( &_sa_observer );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistry_stub_clp::addRegistryObserver( sof::framework::remote::corba::generated::CORBARegistryObserver_ptr _par_observer )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistry * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistry::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->addRegistryObserver(_par_observer);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistry_stub::addRegistryObserver(_par_observer);
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistry_stub::registerService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service );
  CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );
  CORBA::StaticRequest __req( this, "registerService" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_service );
  __req.add_in_arg( &_sa_props );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistry_stub_clp::registerService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistry * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistry::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->registerService(_par_bundleName, _par_serviceName, _par_service, _par_props);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistry_stub::registerService(_par_bundleName, _par_serviceName, _par_service, _par_props);
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistry_stub::registerServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener );
  CORBA::StaticRequest __req( this, "registerServiceListener" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_listener );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistry_stub_clp::registerServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistry * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistry::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->registerServiceListener(_par_bundleName, _par_serviceName, _par_listener);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistry_stub::registerServiceListener(_par_bundleName, _par_serviceName, _par_listener);
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistry_stub::unregisterService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service );
  CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );
  CORBA::StaticRequest __req( this, "unregisterService" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_service );
  __req.add_in_arg( &_sa_props );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistry_stub_clp::unregisterService( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAService_ptr _par_service, const sof::framework::remote::corba::generated::CORBAServiceProps& _par_props )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistry * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistry::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->unregisterService(_par_bundleName, _par_serviceName, _par_service, _par_props);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistry_stub::unregisterService(_par_bundleName, _par_serviceName, _par_service, _par_props);
}

#endif // MICO_CONF_NO_POA

void sof::framework::remote::corba::generated::CORBARegistry_stub::unregisterServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName );
  CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName );
  CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener );
  CORBA::StaticRequest __req( this, "unregisterServiceListener" );
  __req.add_in_arg( &_sa_bundleName );
  __req.add_in_arg( &_sa_serviceName );
  __req.add_in_arg( &_sa_listener );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
sof::framework::remote::corba::generated::CORBARegistry_stub_clp::unregisterServiceListener( const char* _par_bundleName, const char* _par_serviceName, sof::framework::remote::corba::generated::CORBAServiceListener_ptr _par_listener )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_sof::framework::remote::corba::generated::CORBARegistry * _myserv = POA_sof::framework::remote::corba::generated::CORBARegistry::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->unregisterServiceListener(_par_bundleName, _par_serviceName, _par_listener);
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
      return;
    }
    _postinvoke ();
  }

  sof::framework::remote::corba::generated::CORBARegistry_stub::unregisterServiceListener(_par_bundleName, _par_serviceName, _par_listener);
}

#endif // MICO_CONF_NO_POA

struct __tc_init_CORBAOBJECTS {
  __tc_init_CORBAOBJECTS()
  {
    _marshaller_sof_framework_remote_corba_generated_CORBAService = new _Marshaller_sof_framework_remote_corba_generated_CORBAService;
    _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps = new _Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps;
    _marshaller_sof_framework_remote_corba_generated_CORBAServiceReference = new _Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference;
    _marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent = new _Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent;
    _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener = new _Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener;
    _marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver = new _Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver;
    _marshaller_sof_framework_remote_corba_generated_CORBARegistry = new _Marshaller_sof_framework_remote_corba_generated_CORBARegistry;
  }

  ~__tc_init_CORBAOBJECTS()
  {
    delete static_cast<_Marshaller_sof_framework_remote_corba_generated_CORBAService*>(_marshaller_sof_framework_remote_corba_generated_CORBAService);
    delete static_cast<_Marshaller_sof_framework_remote_corba_generated_CORBAServiceProps*>(_marshaller_sof_framework_remote_corba_generated_CORBAServiceProps);
    delete static_cast<_Marshaller_sof_framework_remote_corba_generated_CORBAServiceReference*>(_marshaller_sof_framework_remote_corba_generated_CORBAServiceReference);
    delete static_cast<_Marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent*>(_marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent);
    delete static_cast<_Marshaller_sof_framework_remote_corba_generated_CORBAServiceListener*>(_marshaller_sof_framework_remote_corba_generated_CORBAServiceListener);
    delete static_cast<_Marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver*>(_marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver);
    delete static_cast<_Marshaller_sof_framework_remote_corba_generated_CORBARegistry*>(_marshaller_sof_framework_remote_corba_generated_CORBARegistry);
  }
};

static __tc_init_CORBAOBJECTS __init_CORBAOBJECTS;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface sof::framework::remote::corba::generated::CORBAService
POA_sof::framework::remote::corba::generated::CORBAService::~CORBAService()
{
}

::sof::framework::remote::corba::generated::CORBAService_ptr
POA_sof::framework::remote::corba::generated::CORBAService::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::sof::framework::remote::corba::generated::CORBAService::_narrow (obj);
}

CORBA::Boolean
POA_sof::framework::remote::corba::generated::CORBAService::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBAService:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_sof::framework::remote::corba::generated::CORBAService::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:sof/framework/remote/corba/generated/CORBAService:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_sof::framework::remote::corba::generated::CORBAService::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:sof/framework/remote/corba/generated/CORBAService:1.0");
}

CORBA::Object_ptr
POA_sof::framework::remote::corba::generated::CORBAService::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::sof::framework::remote::corba::generated::CORBAService_stub_clp (poa, obj);
}

bool
POA_sof::framework::remote::corba::generated::CORBAService::dispatch (CORBA::StaticServerRequest_ptr __req)
{

  return false;
}

void
POA_sof::framework::remote::corba::generated::CORBAService::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}


// PortableServer Skeleton Class for interface sof::framework::remote::corba::generated::CORBAServiceListener
POA_sof::framework::remote::corba::generated::CORBAServiceListener::~CORBAServiceListener()
{
}

::sof::framework::remote::corba::generated::CORBAServiceListener_ptr
POA_sof::framework::remote::corba::generated::CORBAServiceListener::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::sof::framework::remote::corba::generated::CORBAServiceListener::_narrow (obj);
}

CORBA::Boolean
POA_sof::framework::remote::corba::generated::CORBAServiceListener::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_sof::framework::remote::corba::generated::CORBAServiceListener::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_sof::framework::remote::corba::generated::CORBAServiceListener::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:sof/framework/remote/corba/generated/CORBAServiceListener:1.0");
}

CORBA::Object_ptr
POA_sof::framework::remote::corba::generated::CORBAServiceListener::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::sof::framework::remote::corba::generated::CORBAServiceListener_stub_clp (poa, obj);
}

bool
POA_sof::framework::remote::corba::generated::CORBAServiceListener::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "serviceChanged" ) == 0 ) {
      ::sof::framework::remote::corba::generated::CORBAServiceEvent _par_serviceEvent;
      CORBA::StaticAny _sa_serviceEvent( _marshaller_sof_framework_remote_corba_generated_CORBAServiceEvent, &_par_serviceEvent );

      CORBA::Boolean _res;
      CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
      __req->add_in_arg( &_sa_serviceEvent );
      __req->set_result( &__res );

      if( !__req->read_args() )
        return true;

      _res = serviceChanged( _par_serviceEvent );
      __req->write_results();
      return true;
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
POA_sof::framework::remote::corba::generated::CORBAServiceListener::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}


// PortableServer Skeleton Class for interface sof::framework::remote::corba::generated::CORBARegistryObserver
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::~CORBARegistryObserver()
{
}

::sof::framework::remote::corba::generated::CORBARegistryObserver_ptr
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::sof::framework::remote::corba::generated::CORBARegistryObserver::_narrow (obj);
}

CORBA::Boolean
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:sof/framework/remote/corba/generated/CORBARegistryObserver:1.0");
}

CORBA::Object_ptr
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::sof::framework::remote::corba::generated::CORBARegistryObserver_stub_clp (poa, obj);
}

bool
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    switch (mico_string_hash (__req->op_name(), 7)) {
    case 0:
      if( strcmp( __req->op_name(), "unregisterServiceListener" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceListener_var _par_listener;
        CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener._for_demarshal() );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_listener );

        if( !__req->read_args() )
          return true;

        unregisterServiceListener( _par_bundleName.inout(), _par_serviceName.inout(), _par_listener.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 1:
      if( strcmp( __req->op_name(), "ping" ) == 0 ) {

        if( !__req->read_args() )
          return true;

        ping();
        __req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( __req->op_name(), "registerService" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAService_var _par_service;
        CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceProps _par_props;
        CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_service );
        __req->add_in_arg( &_sa_props );

        if( !__req->read_args() )
          return true;

        registerService( _par_bundleName.inout(), _par_serviceName.inout(), _par_service.inout(), _par_props );
        __req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( __req->op_name(), "unregisterService" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAService_var _par_service;
        CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceProps _par_props;
        CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_service );
        __req->add_in_arg( &_sa_props );

        if( !__req->read_args() )
          return true;

        unregisterService( _par_bundleName.inout(), _par_serviceName.inout(), _par_service.inout(), _par_props );
        __req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( __req->op_name(), "registerServiceListener" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceListener_var _par_listener;
        CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener._for_demarshal() );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_listener );

        if( !__req->read_args() )
          return true;

        registerServiceListener( _par_bundleName.inout(), _par_serviceName.inout(), _par_listener.inout() );
        __req->write_results();
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
POA_sof::framework::remote::corba::generated::CORBARegistryObserver::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}


// PortableServer Skeleton Class for interface sof::framework::remote::corba::generated::CORBARegistry
POA_sof::framework::remote::corba::generated::CORBARegistry::~CORBARegistry()
{
}

::sof::framework::remote::corba::generated::CORBARegistry_ptr
POA_sof::framework::remote::corba::generated::CORBARegistry::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::sof::framework::remote::corba::generated::CORBARegistry::_narrow (obj);
}

CORBA::Boolean
POA_sof::framework::remote::corba::generated::CORBARegistry::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_sof::framework::remote::corba::generated::CORBARegistry::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_sof::framework::remote::corba::generated::CORBARegistry::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:sof/framework/remote/corba/generated/CORBARegistry:1.0");
}

CORBA::Object_ptr
POA_sof::framework::remote::corba::generated::CORBARegistry::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::sof::framework::remote::corba::generated::CORBARegistry_stub_clp (poa, obj);
}

bool
POA_sof::framework::remote::corba::generated::CORBARegistry::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    switch (mico_string_hash (__req->op_name(), 7)) {
    case 0:
      if( strcmp( __req->op_name(), "unregisterServiceListener" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceListener_var _par_listener;
        CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener._for_demarshal() );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_listener );

        if( !__req->read_args() )
          return true;

        unregisterServiceListener( _par_bundleName.inout(), _par_serviceName.inout(), _par_listener.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( __req->op_name(), "addRegistryObserver" ) == 0 ) {
        ::sof::framework::remote::corba::generated::CORBARegistryObserver_var _par_observer;
        CORBA::StaticAny _sa_observer( _marshaller_sof_framework_remote_corba_generated_CORBARegistryObserver, &_par_observer._for_demarshal() );

        __req->add_in_arg( &_sa_observer );

        if( !__req->read_args() )
          return true;

        addRegistryObserver( _par_observer.inout() );
        __req->write_results();
        return true;
      }
      if( strcmp( __req->op_name(), "registerService" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAService_var _par_service;
        CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceProps _par_props;
        CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_service );
        __req->add_in_arg( &_sa_props );

        if( !__req->read_args() )
          return true;

        registerService( _par_bundleName.inout(), _par_serviceName.inout(), _par_service.inout(), _par_props );
        __req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( __req->op_name(), "unregisterService" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAService_var _par_service;
        CORBA::StaticAny _sa_service( _marshaller_sof_framework_remote_corba_generated_CORBAService, &_par_service._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceProps _par_props;
        CORBA::StaticAny _sa_props( _marshaller_sof_framework_remote_corba_generated_CORBAServiceProps, &_par_props );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_service );
        __req->add_in_arg( &_sa_props );

        if( !__req->read_args() )
          return true;

        unregisterService( _par_bundleName.inout(), _par_serviceName.inout(), _par_service.inout(), _par_props );
        __req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( __req->op_name(), "registerServiceListener" ) == 0 ) {
        CORBA::String_var _par_bundleName;
        CORBA::StaticAny _sa_bundleName( CORBA::_stc_string, &_par_bundleName._for_demarshal() );
        CORBA::String_var _par_serviceName;
        CORBA::StaticAny _sa_serviceName( CORBA::_stc_string, &_par_serviceName._for_demarshal() );
        ::sof::framework::remote::corba::generated::CORBAServiceListener_var _par_listener;
        CORBA::StaticAny _sa_listener( _marshaller_sof_framework_remote_corba_generated_CORBAServiceListener, &_par_listener._for_demarshal() );

        __req->add_in_arg( &_sa_bundleName );
        __req->add_in_arg( &_sa_serviceName );
        __req->add_in_arg( &_sa_listener );

        if( !__req->read_args() )
          return true;

        registerServiceListener( _par_bundleName.inout(), _par_serviceName.inout(), _par_listener.inout() );
        __req->write_results();
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
POA_sof::framework::remote::corba::generated::CORBARegistry::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

