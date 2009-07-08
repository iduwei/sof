#include "RemoteServiceReference.h"

using namespace sof::framework::remote::corba;

RemoteServiceReference::RemoteServiceReference( const string &name, const Properties &properties, CORBAService_var serviceObj, const string& objID ) :
								remoteService( serviceObj ), remoteObjectID( objID ), 
								ServiceReference( name, properties, NULL )
{
}

RemoteServiceReference::RemoteServiceReference( const RemoteServiceReference& serviceRef ) : ServiceReference( serviceRef )
{
	this->remoteObjectID = serviceRef.remoteObjectID;
	this->remoteService = CORBAService::_duplicate( serviceRef.remoteService );
}

RemoteServiceReference& RemoteServiceReference::operator=( const RemoteServiceReference &serviceRef ) 
{
	if (this != &serviceRef) 
    {
		this->serviceName = serviceRef.serviceName;
		this->props = serviceRef.props;
		this->remoteService = CORBAService::_duplicate( serviceRef.remoteService );
		this->remoteObjectID = serviceRef.remoteObjectID;
    }
    return *this; 
}

RemoteServiceReference:: ~RemoteServiceReference()
{
}

string RemoteServiceReference::getRemoteServiceID() const
{
	return this->remoteObjectID;
}

CORBAService_var RemoteServiceReference::getRemoteService() const
{
	return this->remoteService;
}

bool RemoteServiceReference::operator==( const RemoteServiceReference& serviceReference )
{
	if ( this->serviceName == serviceReference.getServiceName() &&
		this->props == serviceReference.getServiceProperties() &&
		this->remoteObjectID == serviceReference.getRemoteServiceID() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

string RemoteServiceReference::toString() const
{
	ostringstream propsStream;
	propsStream << "serviceReference={";
	propsStream << "serviceName=" << this->serviceName << ", ";
	propsStream << this->props.toString() << ", ";
	propsStream << "objectID=" << this->remoteObjectID;
	propsStream << "}";
	return propsStream.str();
}

IService::ConstPtr RemoteServiceReference::getService() const
{
	SOFException exc( "Function not supported by remote SOF!" );
	throw exc;
}