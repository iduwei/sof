#include "ObjectLoadingException.h"

using namespace sof::classloading;

ObjectLoadingException::ObjectLoadingException( const string &msg ) : message( msg )
{

}
const char* ObjectLoadingException::what() const
{
	return this->message.c_str();
}