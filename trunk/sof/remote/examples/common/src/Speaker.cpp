/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "Speaker.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class Speaker
 */

Speaker::~Speaker()
{
}

void *
Speaker::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:Speaker:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if ((_p = sof::framework::remote::corba::generated::CORBAService::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

Speaker_ptr
Speaker::_narrow( CORBA::Object_ptr _obj )
{
  Speaker_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:Speaker:1.0" )))
      return _duplicate( (Speaker_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:Speaker:1.0") || _obj->_is_a_remote ("IDL:Speaker:1.0")) {
      _o = new Speaker_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

Speaker_ptr
Speaker::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_Speaker : public ::CORBA::StaticTypeInfo {
    typedef Speaker_ptr _MICO_T;
  public:
    ~_Marshaller_Speaker();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Speaker::~_Marshaller_Speaker()
{
}

::CORBA::StaticValueType _Marshaller_Speaker::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_Speaker::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::Speaker::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_Speaker::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_Speaker::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_Speaker::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::Speaker::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_Speaker::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_Speaker;


/*
 * Stub interface for class Speaker
 */

Speaker_stub::~Speaker_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_Speaker::_narrow_helper (const char * repoid)
{
  void * p;
  if (strcmp (repoid, "IDL:Speaker:1.0") == 0) {
    return (void *) this;
  }
  if ((p = POA_sof::framework::remote::corba::generated::CORBAService::_narrow_helper (repoid)) != NULL) 
  {
    return p;
  }
  return NULL;
}

POA_Speaker *
POA_Speaker::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:Speaker:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_Speaker *) p;
  }
  return NULL;
}

Speaker_stub_clp::Speaker_stub_clp ()
{
}

Speaker_stub_clp::Speaker_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

Speaker_stub_clp::~Speaker_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

void Speaker_stub::sayHello( const char* _par_text )
{
  CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text );
  CORBA::StaticRequest __req( this, "sayHello" );
  __req.add_in_arg( &_sa_text );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
Speaker_stub_clp::sayHello( const char* _par_text )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Speaker * _myserv = POA_Speaker::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->sayHello(_par_text);
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

  Speaker_stub::sayHello(_par_text);
}

#endif // MICO_CONF_NO_POA

struct __tc_init_SPEAKER {
  __tc_init_SPEAKER()
  {
    _marshaller_Speaker = new _Marshaller_Speaker;
  }

  ~__tc_init_SPEAKER()
  {
    delete static_cast<_Marshaller_Speaker*>(_marshaller_Speaker);
  }
};

static __tc_init_SPEAKER __init_SPEAKER;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface Speaker
POA_Speaker::~POA_Speaker()
{
}

::Speaker_ptr
POA_Speaker::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::Speaker::_narrow (obj);
}

CORBA::Boolean
POA_Speaker::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:Speaker:1.0") == 0) {
    return TRUE;
  }
  if (POA_sof::framework::remote::corba::generated::CORBAService::_is_a (repoid)) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_Speaker::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:Speaker:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_Speaker::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:Speaker:1.0");
}

CORBA::Object_ptr
POA_Speaker::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::Speaker_stub_clp (poa, obj);
}

bool
POA_Speaker::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "sayHello" ) == 0 ) {
      CORBA::String_var _par_text;
      CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text._for_demarshal() );

      __req->add_in_arg( &_sa_text );

      if( !__req->read_args() )
        return true;

      sayHello( _par_text.inout() );
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

  if (POA_sof::framework::remote::corba::generated::CORBAService::dispatch (__req)) {
    return true;
  }

  return false;
}

void
POA_Speaker::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

