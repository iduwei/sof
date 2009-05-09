#include "SOFException.h"

using namespace sof::framework;

SOFException::SOFException( const string &msg ) : message( msg )
{

}

const char* SOFException::what() const
{
	return this->message.c_str();
}