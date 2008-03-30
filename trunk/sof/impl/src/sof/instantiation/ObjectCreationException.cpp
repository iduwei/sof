#include "ObjectCreationException.h"

using namespace sof::instantiation;

ObjectCreationException::ObjectCreationException( const string &msg ) : message( msg )
{

}
const char* ObjectCreationException::what() const
{
	return this->message.c_str();
}