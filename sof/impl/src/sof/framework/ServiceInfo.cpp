#include "ServiceInfo.h"

Logger& ServiceInfo::logger = LoggerFactory::getLogger( "Framework" );

ServiceInfo::ServiceInfo( const string &servName, IService::ConstPtr service, const Properties &properties ) : serviceName( servName ), props( properties ), service( service )
{
	logger.log( Logger::DEBUG, "[ServiceInfo#ctor] Called." );
}

ServiceInfo::~ServiceInfo()
{
	logger.log( Logger::DEBUG, "[ServiceInfo#destructor] Called." );
}

string ServiceInfo::getServiceName() const
{
	return this->serviceName;
}

Properties ServiceInfo::getProperties() const
{
	return this->props;
}

IService::ConstPtr ServiceInfo::getService() const
{
	return this->service;
}

string ServiceInfo::toString() const
{	
	ostringstream propsStream;
	propsStream << "serviceInfo={";
	propsStream << "serviceName=" << this->serviceName << ", ";
	propsStream << this->props.toString();
	propsStream << "}";
	return propsStream.str();
}

bool ServiceInfo::operator==( const ServiceInfo& serviceInfo1 )
{
	if ( this->serviceName == serviceInfo1.getServiceName() &&
		this->props == serviceInfo1.getProperties() &&
		this->service == serviceInfo1.getService() )
	{
		return true;
	}
	else
	{
		return false;
	}
}