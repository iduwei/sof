#include "IRegistryFacadeImpl.h"

#include <vector>
#include <iostream>

#include "sof/framework/SOFException.h"
#include "sof/framework/IServiceRegistrationImpl.h"


using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;

using namespace sof::framework::remote::corba::registry;

Logger& IRegistryFacadeImpl::logger = LoggerFactory::getLogger( "Framework" );

IRegistryFacadeImpl::IRegistryFacadeImpl( CORBAHelper& corbaHelperObj, IRegistry& reg ) : corbaHelper( corbaHelperObj ), registry( reg )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#ctor] Called." );
	this->init();
}

IRegistryFacadeImpl::~IRegistryFacadeImpl()
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#destructor] Called." );
	this->corbaHelper.deactivateObject( this->remoteRegistryObserver );
	delete( this->regObserver );	
}

void IRegistryFacadeImpl::init()
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#init] Called, finding registry object." );
	list<CORBA::Object_var> objects = this->corbaHelper.findObjects( CORBAHelper::REMOTE_REGISTRY_PATH );
	list<CORBA::Object_var>::iterator pos;
	CORBA::Object_var registryObj = *(objects.begin());
	this->remoteRegistry = CORBARegistry::_narrow( registryObj);
	
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#init] Called, creating registry observer object." );
	this->regObserver = new CORBARegistryObserverImpl( this->registry, this->corbaHelper );
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#init] Called, activating registry observer object." );
	this->remoteRegistryObserver = this->corbaHelper.activateObject( regObserver );	
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#init] Called, registering registry observer object." );
	remoteRegistry->addRegistryObserver( CORBARegistryObserver::_narrow( this->remoteRegistryObserver ) );
}

void IRegistryFacadeImpl::addBundleInfo( BundleInfoBase* bundleInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#addBundleInfo] Called, bundle info: %1", bundleInfo->toString() );
	this->registry.addBundleInfo( bundleInfo );
}

BundleInfoBase* IRegistryFacadeImpl::getBundleInfo( const string& bundleName )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#getBundleInfo] Called, bundle name: %1", bundleName );	
	return this->registry.getBundleInfo( bundleName );
}

vector<BundleInfoBase*> IRegistryFacadeImpl::getBundleInfos()
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#getBundleInfos] Called." );	
	return this->registry.getBundleInfos();
}

void IRegistryFacadeImpl::removeBundleInfo( const string& bundleName )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#removeBundleInfo] Called, bundle name: %1", bundleName );	
	this->registry.removeBundleInfo( bundleName );
}

void IRegistryFacadeImpl::addUsedService( const string& bundleName, const ServiceInfo& info )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#addUsedService] Called, bundle name: %1, service info: %2", 
		bundleName, info.toString() );	
	this->registry.addUsedService( bundleName, info );
}

void IRegistryFacadeImpl::removeUsedService( const string& bundleName, const ServiceInfo& info )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#removeBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, info.toString() );	
	this->registry.removeUsedService( bundleName, info );
}

void IRegistryFacadeImpl::removeAllBundleInfos()
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#removeAllBundleInfos] Called." );	
	this->registry.removeAllBundleInfos();
}

IServiceRegistration::ConstPtr IRegistryFacadeImpl::addServiceInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Called." );
	RemoteServiceInfo* corbaServiceInfo = dynamic_cast<RemoteServiceInfo*> (serviceInfo);
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Called, service info object: %1", corbaServiceInfo->toString() );

	CORBAServiceProps props = this->corbaHelper.convertServiceProperties( corbaServiceInfo->getProperties() );

	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Call remote registry." );

	this->remoteRegistry->registerService( 
		bundleName.c_str(), 
		serviceInfo->getServiceName().c_str(), 
		corbaServiceInfo->getRemoteService(),
		props );

	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Creating service registration object." );
	
	// Bugfix: [Remote SOF] Services and listeners are not deregistered - ID: 2818458
	// Do pass IRegistryFacadeImpl instead of IRegistryImpl object.
	return new IServiceRegistrationImpl( bundleName, this, serviceInfo );
}
		
void IRegistryFacadeImpl::removeServiceInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Called, bundle name: %1, service info: %2",
		bundleName, serviceInfo->toString() );	
	RemoteServiceInfo* corbaServiceInfo = dynamic_cast<RemoteServiceInfo*> (serviceInfo);
	
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Unregister service at remote registry." );	
	
	this->remoteRegistry->unregisterService( 
		bundleName.c_str(), 
		serviceInfo->getServiceName().c_str(), 
		corbaServiceInfo->getRemoteService(),
		this->corbaHelper.convertServiceProperties( corbaServiceInfo->getProperties() ) 
		);

	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Deactivate corba object." );	

	this->corbaHelper.deactivateObject( CORBAService::_duplicate( corbaServiceInfo->getRemoteService() ) );
}

vector<ServiceInfo*>* IRegistryFacadeImpl::getServiceInfo( const string &serviceName )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#getServiceInfo] Called, service name: %1",
		serviceName );	
	return this->registry.getServiceInfo( serviceName );
}

void IRegistryFacadeImpl::addServiceListener( const string& bundleName, ServiceListenerInfo* listenerInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#addServiceListener] Called, bundle name: %1, listener info: %2",
		bundleName, listenerInfo->toString() );	
	RemoteServiceListenerInfo* corbaServiceListenerInfo = dynamic_cast<RemoteServiceListenerInfo*> (listenerInfo);
	this->remoteRegistry->registerServiceListener( bundleName.c_str(), corbaServiceListenerInfo->getServiceName().c_str(),
		corbaServiceListenerInfo->getRemoteServiceListener() );
}
		
void IRegistryFacadeImpl::removeServiceListener( const string& bundleName, const ServiceListenerInfo& info )
{
	logger.log( Logger::DEBUG, "[IRegistryFacadeImpl#removeServiceListener] Called, bundle name: %1, listener info: %1",
		bundleName, info.toString() );	
	
	ServiceListenerInfo* serviceListenerInfo = const_cast<ServiceListenerInfo*> (&info);
	RemoteServiceListenerInfo* corbaServiceListenerInfo = dynamic_cast<RemoteServiceListenerInfo*> (serviceListenerInfo);
	this->remoteRegistry->unregisterServiceListener( bundleName.c_str(), info.getServiceName().c_str(),
		corbaServiceListenerInfo->getRemoteServiceListener() );
}
		