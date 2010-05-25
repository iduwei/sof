#include "RemoteServiceInfo.h"

#include "sof/framework/SOFException.h"

using namespace sof::framework;
using namespace sof::framework::remote::corba;

RemoteServiceInfo::RemoteServiceInfo( const string &servName, CORBAService_var serviceObj, const string& objIdentifier,
								   const Properties &properties ) : ServiceInfo( servName, NULL, properties ),
								   remoteServiceObject( CORBAService::_duplicate( serviceObj ) ), objID( objIdentifier )
								
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#ctor] Called." );
}

RemoteServiceInfo::~RemoteServiceInfo()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#destructor] Called." );
}

string RemoteServiceInfo::getRemoteServiceID() const
{
	return this->objID;
}

CORBAService_var RemoteServiceInfo::getRemoteService()
{
	return this->remoteServiceObject;
}

string RemoteServiceInfo::toString() const
{	
	ostringstream propsStream;
	propsStream << "serviceInfo={";
	propsStream << "serviceName=" << this->serviceName << ", ";
	propsStream << this->props.toString() << ", ";
	propsStream << "objectID=" << this->objID;
	propsStream << "}";
	return propsStream.str();
}

IService::ConstPtr RemoteServiceInfo::getService() const
{
	SOFException exc( "Function not supported by remote SOF!" );
	throw exc;
}

bool RemoteServiceInfo::operator==( const RemoteServiceInfo& serviceInfo )
{
	return this->equals( (*this), serviceInfo );
}

bool RemoteServiceInfo::equals( const ServiceInfo& info1, const ServiceInfo& info2 )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#equals] Called." );	
	ServiceInfo* servInfo1 = const_cast<ServiceInfo*> (&info1);
	ServiceInfo* servInfo2 = const_cast<ServiceInfo*> (&info2);
	
	RemoteServiceInfo* remoteInfo1 = dynamic_cast<RemoteServiceInfo*>( servInfo1 );
	RemoteServiceInfo* remoteInfo2 = dynamic_cast<RemoteServiceInfo*>( servInfo2 );

	if ( remoteInfo1->getServiceName() == remoteInfo2->getServiceName() &&
		remoteInfo1->getProperties() == remoteInfo2->getProperties() &&
		remoteInfo1->getRemoteServiceID() == remoteInfo2->getRemoteServiceID() )
	{
		return true;
	}
	else
	{
		return false;
	}
}