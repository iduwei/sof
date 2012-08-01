#include "RemoteServiceInfo.h"

#include <typeinfo>
#include "sof/framework/SOFException.h"

using namespace sof::framework;
using namespace sof::framework::remote::corba;

RemoteServiceInfo::RemoteServiceInfo( const string &servName, CORBAService_var serviceObj, const string& objIdentifier,
								   const Properties &properties ) : ServiceInfo( servName, NULL, properties ),
								   remoteServiceObject( CORBAService::_duplicate( serviceObj ) ), objID( objIdentifier )
								
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#ctor] Called." );
}

RemoteServiceInfo::RemoteServiceInfo( const RemoteServiceInfo& remoteServiceInfo ) : ServiceInfo( remoteServiceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#copy-ctor] Called." );
	this->objID = remoteServiceInfo.objID;
	this->remoteServiceObject = CORBAService::_duplicate( remoteServiceInfo.getRemoteService() );
}

RemoteServiceInfo::~RemoteServiceInfo()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#destructor] Called." );
}

string RemoteServiceInfo::getRemoteServiceID() const
{
	return this->objID;
}

CORBAService_var RemoteServiceInfo::getRemoteService() const
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
	return this->service;
}

bool RemoteServiceInfo::operator==( const RemoteServiceInfo& serviceInfo )
{
	return this->equals( (*this), serviceInfo );
}

RemoteServiceInfo& RemoteServiceInfo::operator=( const RemoteServiceInfo &remoteServiceInfo ) 
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#operator=] Called." );

	if (this != &remoteServiceInfo) 
    {
		this->serviceName = remoteServiceInfo.serviceName;
		this->props = remoteServiceInfo.props;
		this->objID = remoteServiceInfo.objID;
		this->remoteServiceObject = CORBAService::_duplicate( remoteServiceInfo.getRemoteService() );		
    }
    return *this; 
}

bool RemoteServiceInfo::equals( const ServiceInfo& info1, const ServiceInfo& info2 )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#equals] Called." );
	if ( typeid(info1) == typeid( info2 ) )
	{
		logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#equals] Same types, compare." );

		const RemoteServiceInfo* remoteInfo1 = dynamic_cast<const RemoteServiceInfo*>( &info1 );
		const RemoteServiceInfo* remoteInfo2 = dynamic_cast<const RemoteServiceInfo*>( &info2 );
	
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
	else
	{
		logger.log( Logger::LOG_DEBUG, "[RemoteServiceInfo#equals] Different types, return false." );
		return false;
	}
}
