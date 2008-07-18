#include "ConfigurationException.h"

using namespace sof::config;

ConfigurationException::ConfigurationException( const string &msg ) : message( msg )
{

}
const char* ConfigurationException::what() const
{
	return this->message.c_str();
}