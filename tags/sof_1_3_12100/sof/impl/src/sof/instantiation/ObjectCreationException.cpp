#include "ObjectCreationException.h"

using namespace sof::instantiation;

ObjectCreationException::ObjectCreationException( const string &msg ) : message( msg )
{
}

ObjectCreationException::~ObjectCreationException( ) throw()
{
}

const char* ObjectCreationException::what() const throw()
{
	return this->message.c_str();
}