#include "SOFException.h"

using namespace sof::framework;

SOFException::SOFException( const string &msg ) : message( msg )
{

}

SOFException::~SOFException( ) throw()
{
}

const char* SOFException::what() const throw()
{
	return this->message.c_str();
}

