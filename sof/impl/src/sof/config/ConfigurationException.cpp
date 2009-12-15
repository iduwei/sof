#include "ConfigurationException.h"

using namespace sof::config;
using namespace sof::framework;

ConfigurationException::ConfigurationException( const string &msg ) : SOFException( msg )
{

}

ConfigurationException::~ConfigurationException() throw()
{

}