#include "RemoteServiceListenerInfo.h"

#include <sstream>

#include "sof/framework/SOFException.h"

using namespace std;
using namespace sof::framework::remote::corba;
using namespace sof::framework;

RemoteServiceListenerInfo::RemoteServiceListenerInfo( const string& bundleName, const string &servName, CORBAServiceListener_var serviceObj, const string& objIdentifier ) : 
								remoteServiceObject( CORBAServiceListener::_duplicate( serviceObj ) ), objID( objIdentifier ), 
								ServiceListenerInfo( bundleName, servName , NULL )
{
	logger.log( Logger::DEBUG, "[RemoteServiceListenerInfo#ctor] Called." );
}


RemoteServiceListenerInfo::~RemoteServiceListenerInfo()
{
	logger.log( Logger::DEBUG, "[RemoteServiceListenerInfo#destructor] Called." );
}

/*RemoteServiceListenerInfo::RemoteServiceListenerInfo( const RemoteServiceListenerInfo& info )
{
	logger.log( Logger::DEBUG, "[RemoteServiceListenerInfo#copy-ctor] Called." );

	this->bundleName = info.bundleName;
	this->serviceName = info.serviceName;
	this->objID = info.objID;
	this->remoteServiceObject = CORBAServiceListener::_duplicate( info.remoteServiceObject );
}*/

string RemoteServiceListenerInfo::getRemoteServiceListenerID() const
{
	return this->objID;
}

CORBAServiceListener_var RemoteServiceListenerInfo::getRemoteServiceListener()
{
	return this->remoteServiceObject;
}

IServiceListener::ConstPtr RemoteServiceListenerInfo::getServiceListenerObj() const
{
	SOFException exc( "Function not supported by remote SOF." );
	throw exc;
}

string RemoteServiceListenerInfo::toString() const
{	
	ostringstream infoStream;
	infoStream << "serviceListenerInfo={";
	infoStream << "bundleName=" << this->bundleName << ", ";
	infoStream << "serviceName=" << this->serviceName << ", ";
	infoStream << "objectID=" << this->objID;
	infoStream << "}";
	return infoStream.str();
	
}

RemoteServiceListenerInfo& RemoteServiceListenerInfo::operator=( const RemoteServiceListenerInfo &remoteServiceListenerInfo ) 
{
	logger.log( Logger::DEBUG, "[RemoteServiceListenerInfo#operator=] Called." );

	if (this != &remoteServiceListenerInfo) 
    {
		this->bundleName = remoteServiceListenerInfo.bundleName;
		this->serviceName = remoteServiceListenerInfo.serviceName;
		this->objID = remoteServiceListenerInfo.objID;
		this->remoteServiceObject = CORBAServiceListener::_duplicate( remoteServiceListenerInfo.remoteServiceObject );
    }
    return *this; 
}

bool RemoteServiceListenerInfo::operator==( const RemoteServiceListenerInfo& serviceInfo )
{
	return this->equals( serviceInfo, (*this) );
}

bool RemoteServiceListenerInfo::equals( const ServiceListenerInfo& serviceInfo1, const ServiceListenerInfo& serviceInfo2 )
{
	ServiceListenerInfo* remoteServInfo1 = const_cast<ServiceListenerInfo*> (&serviceInfo1);
	RemoteServiceListenerInfo* remoteServiceInfo1 = dynamic_cast<RemoteServiceListenerInfo*> (remoteServInfo1);
	
	ServiceListenerInfo* remoteServInfo2 = const_cast<ServiceListenerInfo*> (&serviceInfo2);
	RemoteServiceListenerInfo* remoteServiceInfo2 = dynamic_cast<RemoteServiceListenerInfo*> (remoteServInfo2);
	
	if ( remoteServiceInfo1->getBundleName() == remoteServiceInfo2->getBundleName() &&
		remoteServiceInfo1->getRemoteServiceListenerID() == remoteServiceInfo2->getRemoteServiceListenerID() &&
		remoteServiceInfo1->getServiceName() == remoteServiceInfo2->getServiceName() )
	{
		return true;
	}
	else
	{
		return false;
	}
}