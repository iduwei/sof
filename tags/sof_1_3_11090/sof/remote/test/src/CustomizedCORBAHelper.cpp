#include "CustomizedCORBAHelper.h"

CustomizedCORBAHelper::CustomizedCORBAHelper( const vector<string>& args ) : CORBAHelper( args )
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[CustomizedCORBAHelper#ctor] Called." );
}

list<CORBA::Object_var> CustomizedCORBAHelper::findObjects( const string& path)
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[CustomizedCORBAHelper#findObjects] Called." );
	list<CORBA::Object_var> list;
	CORBA::Object_var obj = this->activateObject( &(this->registry) );
	list.push_back( CORBA::Object::_duplicate( obj ) );
	return list;
}
