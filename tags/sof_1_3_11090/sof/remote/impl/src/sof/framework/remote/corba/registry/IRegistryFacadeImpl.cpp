#include "IRegistryFacadeImpl.h"

#include <vector>
#include <iostream>

#include "sof/framework/SOFException.h"
#include "sof/framework/IServiceRegistrationImpl.h"
#include "sof/util/memory/ScopeGuard.h"

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::util::memory;

using namespace sof::framework::remote::corba::registry;

Logger& IRegistryFacadeImpl::logger = LoggerFactory::getLogger( "Framework" );

IRegistryFacadeImpl::IRegistryFacadeImpl( CORBAHelper& corbaHelperObj, IRegistry& reg ) : corbaHelper( corbaHelperObj ), registry( reg )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#ctor] Called." );
	this->init();
}

IRegistryFacadeImpl::~IRegistryFacadeImpl()
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#destructor] Called." );
	this->corbaHelper.deactivateObject( this->remoteRegistryObserver );
	delete( this->regObserver );	
}

void IRegistryFacadeImpl::init()
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#init] Called, finding registry object." );
	list<CORBA::Object_var> objects = this->corbaHelper.findObjects( CORBAHelper::REMOTE_REGISTRY_PATH );
	list<CORBA::Object_var>::iterator pos;
	CORBA::Object_var registryObj = *(objects.begin());
	this->remoteRegistry = CORBARegistry::_narrow( registryObj);
	
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#init] Called, creating registry observer object." );
	this->regObserver = new CORBARegistryObserverImpl( this->registry, this->corbaHelper );
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#init] Called, activating registry observer object." );
	this->remoteRegistryObserver = this->corbaHelper.activateObject( regObserver );	
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#init] Called, registering registry observer object." );
	remoteRegistry->addRegistryObserver( CORBARegistryObserver::_narrow( this->remoteRegistryObserver ) );
}

void IRegistryFacadeImpl::addBundleInfo( BundleInfoBase& bundleInfo )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addBundleInfo] Called, bundle info: %1", bundleInfo.toString() );
	this->registry.addBundleInfo( bundleInfo );
}

BundleInfoBase* IRegistryFacadeImpl::getBundleInfo( const string& bundleName )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#getBundleInfo] Called, bundle name: %1", bundleName );	
	return this->registry.getBundleInfo( bundleName );
}

vector<BundleInfoBase*> IRegistryFacadeImpl::getBundleInfos()
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#getBundleInfos] Called." );	
	return this->registry.getBundleInfos();
}

void IRegistryFacadeImpl::removeBundleInfo( const string& bundleName )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeBundleInfo] Called, bundle name: %1", bundleName );	
	this->registry.removeBundleInfo( bundleName );
}

void IRegistryFacadeImpl::addUsedService( const string& bundleName, ServiceInfoPtr info )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addUsedService] Called, bundle name: %1, service info: %2", 
		bundleName, info->toString() );	
	this->registry.addUsedService( bundleName, info );
}

void IRegistryFacadeImpl::removeUsedService( const string& bundleName, ServiceInfoPtr info )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, info->toString() );	
	this->registry.removeUsedService( bundleName, info );
}

void IRegistryFacadeImpl::removeAllBundleInfos()
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeAllBundleInfos] Called." );	
	this->registry.removeAllBundleInfos();
}

IServiceRegistration::ConstPtr IRegistryFacadeImpl::addServiceInfo( const string& bundleName, ServiceInfoPtr serviceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Called." );
	if ( serviceInfo->getService() == NULL )
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Adding remote service." );
		RemoteServiceInfo* corbaServiceInfo = dynamic_cast<RemoteServiceInfo*> (serviceInfo.GetRawPointer());
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Called, service info object: %1", corbaServiceInfo->toString() );

		CORBAServiceProps props = this->corbaHelper.convertServiceProperties( corbaServiceInfo->getProperties() );

		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Call remote registry." );

		this->remoteRegistry->registerService(
			bundleName.c_str(),
			serviceInfo->getServiceName().c_str(),
			corbaServiceInfo->getRemoteService(),
			props );
	
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Creating service registration object." );

		// Bugfix: [Remote SOF] Services and listeners are not deregistered - ID: 2818458
		// Do pass IRegistryFacadeImpl instead of IRegistryImpl object.
		return new IServiceRegistrationImpl( bundleName, (*this), serviceInfo );
	}
	else
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceInfo] Adding local service." );
		return this->registry.addServiceInfo( bundleName, serviceInfo );
	}
}
		
void IRegistryFacadeImpl::removeServiceInfo( const string& bundleName, ServiceInfoPtr serviceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Called, bundle name: %1, service info: %2",
		bundleName, serviceInfo->toString() );	
	if ( serviceInfo->getService() == NULL )
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Remove remote service." );
		RemoteServiceInfo* corbaServiceInfo = dynamic_cast<RemoteServiceInfo*> (serviceInfo.GetRawPointer());

		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Unregister service at remote registry." );

		this->remoteRegistry->unregisterService(
			bundleName.c_str(),
			serviceInfo->getServiceName().c_str(),
			corbaServiceInfo->getRemoteService(),
			this->corbaHelper.convertServiceProperties( corbaServiceInfo->getProperties() )
			);
	
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Deactivate corba object." );
		this->corbaHelper.deactivateObject( CORBAService::_duplicate( corbaServiceInfo->getRemoteService() ) );
	}
	else
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Remove local service." );
		this->registry.removeServiceInfo( bundleName, serviceInfo );
	}
}

vector<ServiceInfoPtr>* IRegistryFacadeImpl::getServiceInfo( const string &serviceName )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#getServiceInfo] Called, service name: %1",
		serviceName );	
	return this->registry.getServiceInfo( serviceName );
}

void IRegistryFacadeImpl::addServiceListener( const string& bundleName, ServiceListenerInfoPtr listenerInfo )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceListener] Called, bundle name: %1, listener info: %2",
		bundleName, listenerInfo->toString() );	

	if ( listenerInfo->getServiceListenerObj() == NULL )
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Add remote service listener." );
		RemoteServiceListenerInfo* corbaServiceListenerInfo = dynamic_cast<RemoteServiceListenerInfo*> ( listenerInfo.GetRawPointer() );
				this->remoteRegistry->registerServiceListener( bundleName.c_str(), corbaServiceListenerInfo->getServiceName().c_str(),
					corbaServiceListenerInfo->getRemoteServiceListener() );
	}
	else
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Add local service listener." );
		this->registry.addServiceListener( bundleName, listenerInfo );
	}
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#addServiceListener] Left" );	
}
		
void IRegistryFacadeImpl::removeServiceListener( const string& bundleName, ServiceListenerInfoPtr info )
{
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceListener] Called, bundle name: %1, listener info: %1",
		bundleName, info->toString() );	
	
	if ( info->getServiceListenerObj() == NULL )
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Remove remote service listener." );
		ServiceListenerInfo* serviceListenerInfo = const_cast<ServiceListenerInfo*> (info.GetRawPointer());
			RemoteServiceListenerInfo* corbaServiceListenerInfo = dynamic_cast<RemoteServiceListenerInfo*> (serviceListenerInfo);
			this->remoteRegistry->unregisterServiceListener( bundleName.c_str(), info->getServiceName().c_str(),
				corbaServiceListenerInfo->getRemoteServiceListener() );
	}
	else
	{
		logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceInfo] Remove local service listener." );
		this->registry.removeServiceListener( bundleName, info );
	}
	logger.log( Logger::LOG_DEBUG, "[IRegistryFacadeImpl#removeServiceListener] Left" );
}
		
