#include "CORBANamingServiceImpl.h"

using namespace sof::framework::remote::corba::namingservice;


CORBANamingServiceImpl::CORBANamingServiceImpl() {
}

CORBANamingServiceImpl::~CORBANamingServiceImpl() {
	;
}

CORBANamingServiceImpl::CORBANamingServiceImpl( CosNaming::NamingContext_var ctx ) {
	this -> naming_context = ctx;
}

CORBANamingServiceImpl::CORBANamingServiceImpl( CORBA::ORB_var orb ) {
	this -> orb = orb;
	// resolve the naming service
        CORBA::Object_var nsobj =
        	orb->resolve_initial_references ("NameService");
        if ( CORBA::is_nil( nsobj ) ) {
            cerr << "can't resolve NameService\n";
            exit( 1 );
        }

        // narrow the root naming context
        naming_context = CosNaming::NamingContext::_narrow ( nsobj );
	
}

list<CORBA::Object_var> CORBANamingServiceImpl::findObjects( const string& path ) {
	list<CORBA::Object_var> l;
	list<string> names = getPathElements( path );
	CosNaming::NamingContext_var ctx = getNamingContext( names, false );
	CosNaming::BindingIterator_var it;
	CosNaming::BindingList_var bl;
	const CORBA::ULong CHUNK = 100;
	ctx->list( CHUNK, bl, it );

	for( CORBA::ULong i = 0; i < bl->length(); i++ ) {
		CORBA::Object_var obj = ctx->resolve( bl[i].binding_name );
		if ( !( obj->_is_a("IDL:omg.org/CosNaming/NamingContext:1.0") ) ) {
			l.push_back( obj );
		}
		CosNaming::NamingContext_var tempCtx = CosNaming::NamingContext::_narrow( obj );
	}

	return l;
}

void CORBANamingServiceImpl::bindObject( const string& path, const string& objectName,
		CORBA::Object_var object ) {
	list<string> names = getPathElements( path );
	CosNaming::NamingContext_var ctx = getNamingContext( names, true );
	CosNaming::Name name;
	name.length(1);
	CORBA::String_var str = objectName.data();
	name[0].id = str;
	ctx->rebind( name, object );	
}

void CORBANamingServiceImpl::unbindObject( const string& path, const string& objectName ) 
{
	list<string> names = getPathElements( path );
	CosNaming::NamingContext_var ctx = getNamingContext( names, true );
	CosNaming::Name name;
	name.length(1);
	CORBA::String_var str = objectName.data();
	name[0].id = str;
	ctx->unbind( name );	
}


list<string> CORBANamingServiceImpl::getPathElements( const string& path ) {

	list<string> l;
	string temp = path;
	int range = temp.find( "/" );
	while( range >= 0 ) {
		string substr = temp.substr( 0, range ); //end-1 );
		temp.erase( 0, range+1 );
		l.push_back( substr );
		range = temp.find( "/" );
	}

	l.push_back( temp );
	return l;
}

CosNaming::NamingContext_var CORBANamingServiceImpl::getNamingContext( list<string> names, bool force ) {

	list<string>::iterator pos;

	CosNaming::Name name;
	name.length(1);

	CosNaming::NamingContext_var tempContext = naming_context;

	for ( pos = names.begin(); pos != names.end(); pos++ ) {
		CORBA::String_var str = (*pos).c_str();
		name[0].id = str;
		try {
			tempContext = CosNaming::NamingContext::_narrow( tempContext->resolve( name ) );
		} catch( const CosNaming::NamingContext::NotFound & e ) {
			if ( force ) {
				tempContext = tempContext->bind_new_context( name );
			} else {
				throw e;
			}
		}
	}
	return tempContext;
}






