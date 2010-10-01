#include "IRemoteBundleContextImpl.h"

#include "sof/framework/SOFException.h"

#include "RemoteServiceInfo.h"
#include "RemoteServiceListenerInfo.h"

using namespace sof::framework::remote::corba;
using namespace sof::framework;
using namespace sof::util::logging;


Logger& IRemoteBundleContextImpl::logger = LoggerFactory::getLogger( "Framework" );

IRemoteBundleContextImpl::IRemoteBundleContextImpl( const string& bdleName, IRegistry& reg,CORBAHelper& corbaHelp ) : 
	bundleName( bdleName ), registry( reg ), corbaHelper( corbaHelp )
{
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#ctor] Called, bundle name: %1", bdleName );
}

IRemoteBundleContextImpl::~IRemoteBundleContextImpl()
{
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#destructor] Called." );
}

string IRemoteBundleContextImpl::getBundleName()
{
	return this->bundleName;
}

IServiceRegistration* IRemoteBundleContextImpl::registerRemoteService( const string &className, POA_sof::framework::remote::corba::generated::CORBAService* remoteService, 
																   const Properties &dict )
{
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#registerRemoteService] Called, bundle name: %1, service name: %2", this->bundleName, className );
	CORBA::Object_var object = this->corbaHelper.activateObject( remoteService );
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#registerRemoteService] Create service info object." );	
	RemoteServiceInfo* serviceInfo = new RemoteServiceInfo( className, CORBAService::_narrow( object ),
		this->corbaHelper.objectToString( object ), dict );
	
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#registerRemoteService] Add service info object to registry." );	
	
	return this->registry.addServiceInfo( this->bundleName, *serviceInfo );
}

void IRemoteBundleContextImpl::addRemoteServiceListener( POA_sof::framework::remote::corba::generated::CORBAServiceListener* remoteServiceListener, const string &serviceName )
{
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#addRemoteServiceListener] Called, bundle name: %1, service name: %2", this->bundleName, serviceName );
	CORBA::Object_var object = this->corbaHelper.activateObject( remoteServiceListener );
	RemoteServiceListenerInfo* serviceListenerInfo = new RemoteServiceListenerInfo( this->bundleName, serviceName, 
		CORBAServiceListener::_narrow( object ),
		this->corbaHelper.objectToString( object ) );
	
	this->listenerMap[remoteServiceListener] = object;
	return this->registry.addServiceListener( this->bundleName, *serviceListenerInfo );
}

void IRemoteBundleContextImpl::removeRemoteServiceListener( POA_sof::framework::remote::corba::generated::CORBAServiceListener* remoteServiceListener )
{
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#removeServiceListener] Called, bundle name: %1", this->bundleName );	
	CORBA::Object_var object = this->listenerMap[remoteServiceListener];

	RemoteServiceListenerInfo info( this->bundleName, "", CORBAServiceListener::_narrow( object ),
		this->corbaHelper.objectToString( object ) );

	map<POA_sof::framework::remote::corba::generated::CORBAServiceListener*,
		CORBA::Object_var>::iterator iter = this->listenerMap.find( remoteServiceListener );

	this->listenerMap.erase( iter );

	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#removeServiceListener] Call registry for removing service listener." );	
	
	this->registry.removeServiceListener( this->bundleName, info );

	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#removeServiceListener] Deactivate corba object of service listener." );	

	this->corbaHelper.deactivateObject( object );
}

IServiceRegistration* IRemoteBundleContextImpl::registerService( const string &className, IService::ConstPtr service, const Properties &dict )
{
	SOFException exc( "registerService: Not supported function!" );
	throw exc;
}

void IRemoteBundleContextImpl::addServiceListener( IServiceListener::ConstPtr serviceListener, const string &serviceName )
{
	SOFException exc( "addServiceListener: Not supported function!" );
	throw exc;
}

void IRemoteBundleContextImpl::removeServiceListener( IServiceListener::ConstPtr serviceListener )
{
	SOFException exc( "removeServiceListener: Not supported function!" );
	throw exc;
}

CORBAHelper& IRemoteBundleContextImpl::getCORBAHelper()
{
	return this->corbaHelper;
}

void IRemoteBundleContextImpl::addUsedService( const string& bundleName, ServiceInfo& serviceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#addUsedService] Called, bundle name: %1, service info: %2",
		bundleName, serviceInfo.toString() );	
	this->registry.addUsedService( bundleName, serviceInfo );	
}

void IRemoteBundleContextImpl::removeUsedService( const string& bundleName, const ServiceInfo& serviceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[IRemoteBundleContextImpl#removeUsedService] Called, bundle name: %1, service info: %2",
		bundleName, serviceInfo.toString() );	
	this->registry.removeUsedService( bundleName, serviceInfo );	
}
