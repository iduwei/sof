/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "Multiplier.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class Multiplier
 */

Multiplier::~Multiplier()
{
}

void *
Multiplier::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:Multiplier:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if ((_p = sof::framework::remote::corba::generated::CORBAService::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

Multiplier_ptr
Multiplier::_narrow( CORBA::Object_ptr _obj )
{
  Multiplier_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:Multiplier:1.0" )))
      return _duplicate( (Multiplier_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:Multiplier:1.0") || _obj->_is_a_remote ("IDL:Multiplier:1.0")) {
      _o = new Multiplier_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

Multiplier_ptr
Multiplier::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_Multiplier : public ::CORBA::StaticTypeInfo {
    typedef Multiplier_ptr _MICO_T;
  public:
    ~_Marshaller_Multiplier();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Multiplier::~_Marshaller_Multiplier()
{
}

::CORBA::StaticValueType _Marshaller_Multiplier::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_Multiplier::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::Multiplier::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_Multiplier::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_Multiplier::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_Multiplier::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::Multiplier::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_Multiplier::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_Multiplier;


/*
 * Stub interface for class Multiplier
 */

Multiplier_stub::~Multiplier_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_Multiplier::_narrow_helper (const char * repoid)
{
  void * p;
  if (strcmp (repoid, "IDL:Multiplier:1.0") == 0) {
    return (void *) this;
  }
  if ((p = POA_sof::framework::remote::corba::generated::CORBAService::_narrow_helper (repoid)) != NULL) 
  {
    return p;
  }
  return NULL;
}

POA_Multiplier *
POA_Multiplier::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:Multiplier:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_Multiplier *) p;
  }
  return NULL;
}

Multiplier_stub_clp::Multiplier_stub_clp ()
{
}

Multiplier_stub_clp::Multiplier_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

Multiplier_stub_clp::~Multiplier_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

CORBA::Long Multiplier_stub::multiply( CORBA::Long _par_x, CORBA::Long _par_y )
{
  CORBA::StaticAny _sa_x( CORBA::_stc_long, &_par_x );
  CORBA::StaticAny _sa_y( CORBA::_stc_long, &_par_y );
  CORBA::Long _res;
  CORBA::StaticAny __res( CORBA::_stc_long, &_res );

  CORBA::StaticRequest __req( this, "multiply" );
  __req.add_in_arg( &_sa_x );
  __req.add_in_arg( &_sa_y );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifndef MICO_CONF_NO_POA

CORBA::Long
Multiplier_stub_clp::multiply( CORBA::Long _par_x, CORBA::Long _par_y )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Multiplier * _myserv = POA_Multiplier::_narrow (_serv);
    if (_myserv) {
      CORBA::Long __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->multiply(_par_x, _par_y);
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

  return Multiplier_stub::multiply(_par_x, _par_y);
}

#endif // MICO_CONF_NO_POA

struct __tc_init_MULTIPLIER {
  __tc_init_MULTIPLIER()
  {
    _marshaller_Multiplier = new _Marshaller_Multiplier;
  }

  ~__tc_init_MULTIPLIER()
  {
    delete static_cast<_Marshaller_Multiplier*>(_marshaller_Multiplier);
  }
};

static __tc_init_MULTIPLIER __init_MULTIPLIER;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface Multiplier
POA_Multiplier::~POA_Multiplier()
{
}

::Multiplier_ptr
POA_Multiplier::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::Multiplier::_narrow (obj);
}

CORBA::Boolean
POA_Multiplier::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:Multiplier:1.0") == 0) {
    return TRUE;
  }
  if (POA_sof::framework::remote::corba::generated::CORBAService::_is_a (repoid)) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_Multiplier::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:Multiplier:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_Multiplier::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:Multiplier:1.0");
}

CORBA::Object_ptr
POA_Multiplier::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::Multiplier_stub_clp (poa, obj);
}

bool
POA_Multiplier::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "multiply" ) == 0 ) {
      CORBA::Long _par_x;
      CORBA::StaticAny _sa_x( CORBA::_stc_long, &_par_x );
      CORBA::Long _par_y;
      CORBA::StaticAny _sa_y( CORBA::_stc_long, &_par_y );

      CORBA::Long _res;
      CORBA::StaticAny __res( CORBA::_stc_long, &_res );
      __req->add_in_arg( &_sa_x );
      __req->add_in_arg( &_sa_y );
      __req->set_result( &__res );

      if( !__req->read_args() )
        return true;

      _res = multiply( _par_x, _par_y );
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
POA_Multiplier::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

