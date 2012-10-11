#include "RemoteServiceReference.h"

using namespace sof::framework::remote::corba;

RemoteServiceReference::RemoteServiceReference( const string &name, const Properties &properties, CORBAService_var serviceObj, const string& objID ) :
								remoteService( serviceObj ), remoteObjectID( objID ), 
								ServiceReference( name, properties, NULL )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceReference#ctor] Called." );
}

RemoteServiceReference::RemoteServiceReference( const RemoteServiceReference& serviceRef ) : ServiceReference( serviceRef )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceReference#copy-ctor] Called." );
	this->serviceName = serviceRef.serviceName;
	this->props = serviceRef.props;	
	this->service = serviceRef.service;
	this->remoteObjectID = serviceRef.remoteObjectID;
	this->remoteService = CORBAService::_duplicate( serviceRef.getRemoteService() );
}

RemoteServiceReference& RemoteServiceReference::operator=( const RemoteServiceReference &serviceRef ) 
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceReference#operator=] Called." );
	if (this != &serviceRef) 
    {
		this->serviceName = serviceRef.serviceName;
		this->props = serviceRef.props;
		this->remoteService = CORBAService::_duplicate( serviceRef.getRemoteService() );
		this->remoteObjectID = serviceRef.remoteObjectID;
    }
    return *this; 
}

RemoteServiceReference:: ~RemoteServiceReference()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceReference#destructor] Called." );
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
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceReference#operator==] Called." );
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
	propsStream << "RemoteServiceReference={";
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
