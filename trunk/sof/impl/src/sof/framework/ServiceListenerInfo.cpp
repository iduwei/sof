#include "ServiceListenerInfo.h"

#include <sstream>

using namespace std;

using namespace sof::framework;

Logger& ServiceListenerInfo::logger = LoggerFactory::getLogger( "Framework" );

ServiceListenerInfo::ServiceListenerInfo( const string& bdleName, const string& servName, IServiceListener::ConstPtr serviceListener ) : bundleName( bdleName ), serviceName( servName ), serviceListenerObj( serviceListener )
{
	logger.log( Logger::DEBUG, "[ServiceListenerInfo#ctor] Called." );
}

ServiceListenerInfo::~ServiceListenerInfo()
{
	logger.log( Logger::DEBUG, "[ServiceListenerInfo#destructor] Called." );
}
 
string ServiceListenerInfo::getBundleName() const
{
	return this->bundleName;
}

string ServiceListenerInfo::getServiceName() const
{
	return this->serviceName;
}

IServiceListener::ConstPtr ServiceListenerInfo::getServiceListenerObj() const
{
	return this->serviceListenerObj;
}

bool ServiceListenerInfo::operator==( const ServiceListenerInfo& info1 ) 
{
	return this->equals( info1, (*this) );
}

bool ServiceListenerInfo::equals( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 ) 
{
	if ( info2.getBundleName() == info1.getBundleName() &&
		info2.getServiceListenerObj() == info1.getServiceListenerObj() &&
		info2.getServiceName() == info1.getServiceName() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

string ServiceListenerInfo::toString() const
{
	ostringstream infoStream;
	infoStream << "serviceListenerInfo={";
	infoStream << "bundleName=" << this->bundleName << ", ";
	infoStream << "serviceName=" << this->serviceName;
	infoStream << "}";
	return infoStream.str();
}
