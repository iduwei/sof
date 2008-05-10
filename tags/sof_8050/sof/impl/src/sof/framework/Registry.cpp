#include "Registry.h"

#include "ServiceEvent.h"
#include "ServiceReference.h"
#include "ServiceInfo.h"

#include "../util/logging/LoggerFactory.h"

using namespace sof::framework;
using namespace sof::util::logging;

Logger& Registry::logger = LoggerFactory::getLogger( "Framework" );

void Registry::addBundleInfo( BundleInfo* bundleInfo ) 
{
	logger.log( Logger::DEBUG, "[Registry#addBundleInfo] Called, bundleName: %1", bundleInfo->getBundleName() );
	this->bundleInfoVec.push_back( bundleInfo );
}

BundleInfo* Registry::getBundleInfo( const string &bundleName )
{
	logger.log( Logger::DEBUG, "[Registry#getBundleInfo] Called, bundleName: %1", bundleName );
	vector<BundleInfo*>::iterator iter;
	for ( iter = this->bundleInfoVec.begin(); iter != this->bundleInfoVec.end(); iter++ )
	{
		if ( (*iter)->getBundleName() == bundleName )
		{
			return (*iter);
		}
	}
	return 0;
}

vector<BundleInfo*> Registry::getBundleInfos()
{
	return this->bundleInfoVec;
}

void Registry::removeAllBundleInfos()
{
	logger.log( Logger::DEBUG, "[Registry#removeAllBundleInfos] Called." );

	// At first the name of the bundles have to be cached in a vector
	// in inverted order the bundles were started.
	vector<string> bundleNames;
	vector<BundleInfo*>::reverse_iterator iter;
	for ( iter = this->bundleInfoVec.rbegin(); iter < this->bundleInfoVec.rend(); iter++ )
	{						
		logger.log( Logger::DEBUG, "[Registry#removeAllBundleInfos] Add bundle name: %1", (*iter)->getBundleName() );
		bundleNames.push_back( (*iter)->getBundleName() );
	}	

	vector<string>::iterator strIterator;
	for ( strIterator = bundleNames.begin(); strIterator != bundleNames.end(); strIterator++ )
	{
		logger.log( Logger::DEBUG, "[Registry#removeAllBundleInfos] Remove bundle: %1", (*strIterator) );
		this->removeBundleInfo( (*strIterator) );
	}
	logger.log( Logger::DEBUG, "[Registry#removeAllBundleInfos] Left." );
}

void Registry::removeBundleInfo( const string &bundleName ) 
{
	logger.log( Logger::DEBUG, "[Registry#removeBundleInfo] Called, bundleName: %1", bundleName );
	
	BundleInfo* bi;
	vector<BundleInfo*>::iterator bundleIter;
	for ( bundleIter = this->bundleInfoVec.begin(); bundleIter != this->bundleInfoVec.end(); bundleIter++ )
	{
		if ( (*bundleIter)->getBundleName() == bundleName )
		{
			bi = (*bundleIter);			
			break;
		}
	}

	IBundleActivator* activator = bi->getBundleActivator();
	activator->stop( bi->getBundleContext() );	

	bi->removeAllUsedServices();

	vector<ServiceInfo*> serviceInfos = bi->getRegisteredServices();
	vector<ServiceInfo*>::iterator iter;
	for ( iter = serviceInfos.begin(); iter != serviceInfos.end(); iter++ )
	{
		logger.log( Logger::DEBUG, "[Registry#removeBundleInfo] Deregister service: %1", (*iter)->getServiceName() );	
		this->removeServiceInfo( bundleName, *iter );
	}

	vector<ServiceListenerInfo*> serviceListenerInfos = bi->getRegisteredListeners();
	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfos.begin(); listenerIter != serviceListenerInfos.end(); listenerIter++ )
	{
		logger.log( Logger::DEBUG, "[Registry#removeBundleInfo] Remove listener: %1", (*listenerIter)->getServiceName() );	
		this->removeServiceListener( bundleName, (*listenerIter)->getServiceListenerObj() );
	}	
	
	delete activator;
	delete (bi->getBundleContext());
	delete bi;
	logger.log( Logger::DEBUG, "[Registry#removeBundleInfo] Erase bundle info." );			
	this->bundleInfoVec.erase( bundleIter );
	logger.log( Logger::DEBUG, "[Registry#removeBundleInfo] Left" );			
}


void Registry::addServiceInfo( const string& bundleName, const string &serviceName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[Registry#addServiceInfo] Called, bundle name: %1, service name: %2", bundleName, serviceName );	

	this->addToServiceInfoVector( serviceName, serviceInfo );

	// adding ServiceInfo object to BundleInfo object
	this->addRegisteredServiceToBundleInfo( bundleName, serviceInfo );	

	// notifying all Listeners about new registered service
	vector<ServiceListenerInfo*>* serviceListenerInfoVec = this->getServiceListenerInfoVector( serviceName );
	this->notifyListenersAboutRegisteredService( bundleName, serviceInfo, serviceListenerInfoVec, serviceName );
}

void Registry::removeServiceInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[Registry#removeServiceInfo] Called, serviceInfo: %1", 
		serviceInfo->toString() );	
	this->removeFromServiceInfoVector( serviceInfo );
	vector<ServiceListenerInfo*>* serviceListenerInfoVec = this->getServiceListenerInfoVector( serviceInfo->getServiceName() );
	this->notifyListenersAboutDeregisteredService( bundleName, serviceInfo, serviceListenerInfoVec );
	this->removeDeregisteredServiceFromBundleInfo( bundleName, serviceInfo );	
	logger.log( Logger::DEBUG, "[Registry#removeServiceInfo] Left." );	
}

void Registry::addRegisteredServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[Registry#addRegisteredServiceToBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->addRegisteredService( serviceInfo );
}

void Registry::removeDeregisteredServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[Registry#removeDeregisteredServiceFromBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->removeDeregisteredService( serviceInfo );
}

void Registry::addUsedServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[Registry#addUsedServiceToBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->addUsedService( serviceInfo );
}

void Registry::removeUsedServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[Registry#removeUsedServiceFromBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->removeUsedService( serviceInfo );
}

vector<ServiceInfo*>* Registry::addToServiceInfoVector( const string& serviceName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[Registry#getServiceInfoVector] Called, service name: %1", serviceName );	

	vector<ServiceInfo*>* serviceVec = this->getServiceInfo( serviceName );

	serviceVec->push_back( serviceInfo );	

	logger.log( Logger::DEBUG, "[Registry#getServiceInfoVector] Left." );	

	return serviceVec;
}


void Registry::removeFromServiceInfoVector( ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[Registry#removeFromServiceInfoVector] Called, service name: %1", serviceInfo->getServiceName() );	

	vector<ServiceInfo*>* vec = this->getServiceInfo( serviceInfo->getServiceName() );
	
	vector<ServiceInfo*>::iterator iter;	

	for ( iter = vec->begin(); iter != vec->end(); iter++ )
	{
		if ( (*(*iter)) == (*serviceInfo) )
		{
			logger.log( Logger::DEBUG, "[Registry#removeFromServiceInfoVector] Service was found in ServiceInfo vector." );	
			iter = vec->erase( iter );
			break;
		}	
	}
	logger.log( Logger::DEBUG, "[Registry#removeFromServiceInfoVector] Left." );	
}

void Registry::notifyListenersAboutRegisteredService( const string& bundleName, vector<ServiceInfo*>* serviceVec, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Called." );	

	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfoVec->begin(); listenerIter != serviceListenerInfoVec->end(); listenerIter++ )
	{
		vector<ServiceInfo*>::iterator serviceIter;
		for ( serviceIter = serviceVec->begin(); serviceIter != serviceVec->end(); serviceIter++ )
		{
			ServiceReference serviceRef( (*serviceIter)->getServiceName(), (*serviceIter)->getProperties(), (*serviceIter)->getService() );
			ServiceEvent serviceEvent( ServiceEvent::REGISTER, serviceRef );
			bool interested = (*listenerIter)->getServiceListenerObj()->serviceChanged( serviceEvent );
			if ( interested )
			{
				logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Service listener is interested in registered service '%1'.",
					(*serviceIter)->getServiceName() );
				this->addUsedServiceToBundleInfo( bundleName, (*serviceIter) );	
			} else
			{
				logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Service listener is NOT interested in registered service '%1'.",
					(*serviceIter)->getServiceName() );
			}
		}
	}	

	logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Left." );	
}

void Registry::notifyListenersAboutRegisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Called." );	

	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfoVec->begin(); listenerIter != serviceListenerInfoVec->end(); listenerIter++ )
	{
		ServiceReference serviceRef( serviceInfo->getServiceName(), serviceInfo->getProperties(), serviceInfo->getService() );
		ServiceEvent serviceEvent( ServiceEvent::REGISTER, serviceRef );
		bool interested = (*listenerIter)->getServiceListenerObj()->serviceChanged( serviceEvent );
		if ( interested )
		{
			logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Service listener is interested in registered service '%1'.",
				serviceInfo->getServiceName() );
			this->addUsedServiceToBundleInfo( (*listenerIter)->getBundleName(), serviceInfo );		
		} else
		{
			logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Service listener is NOT interested in registered service '%1'.",
				serviceInfo->getServiceName() );
		}
	}	

	logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutRegisteredService] Left." );	
}

void Registry::notifyListenersAboutDeregisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec ) 
{
	logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutDeregisteredService] Called." );	

	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfoVec->begin(); listenerIter != serviceListenerInfoVec->end(); listenerIter++ )
	{
		ServiceReference serviceRef( serviceInfo->getServiceName(), serviceInfo->getProperties(), serviceInfo->getService() );
		ServiceEvent serviceEvent( ServiceEvent::UNREGISTER, serviceRef );
		bool interested = (*listenerIter)->getServiceListenerObj()->serviceChanged( serviceEvent );	
		if ( interested )
		{
			logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutDeregisteredService] Listener is interested in deregistered service '%1'.", serviceInfo->getServiceName() );	
			this->removeUsedServiceFromBundleInfo( (*listenerIter)->getBundleName(), serviceInfo );		
		} else
		{
			logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutDeregisteredService] Listener is NOT interested in deregistered service '%1'.", serviceInfo->getServiceName() );	
		}

	}	

	logger.log( Logger::DEBUG, "[Registry#notifyListenersAboutDeregisteredService] Left." );	
}

vector<ServiceInfo*>* Registry::getServiceInfo( const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[Registry#getServiceInfo] Called, service name: %1", serviceName );	
	vector<ServiceInfo*>* vec = this->serviceInfoMap[serviceName];
	if ( vec == 0 )
	{
		logger.log( Logger::DEBUG, "[Registry#getServiceInfo] ServiceInfo vector is null, create one." );		
		vec = new vector<ServiceInfo*>;
		this->serviceInfoMap[serviceName] = vec;
	}
	logger.log( Logger::DEBUG, "[Registry#getServiceInfo] Left." );		
	return vec;
}

vector<ServiceListenerInfo*>* Registry::getServiceListenerInfoVector( const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[Registry#getServiceListenerInfoVector] Called, service name: %1", serviceName );	
	vector<ServiceListenerInfo*>* vec = this->serviceListenerMap[serviceName];
	if ( vec == 0 )
	{
		logger.log( Logger::DEBUG, "[Registry#getServiceListenerInfoVector] ServiceListenerInfo vector is null, create one." );				
		vec = new vector<ServiceListenerInfo*>;
		this->serviceListenerMap[serviceName] = vec;
	}
	logger.log( Logger::DEBUG, "[Registry#ServiceListenerInfo] Left." );	
	return vec;
}

void Registry::addServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener, const string &serviceName ) 
{
	logger.log( Logger::DEBUG, "[Registry#addServiceListener] Called, bundle name: %1, service name: %2", bundleName, serviceName );			
	vector<ServiceListenerInfo*>* vec = this->getServiceListenerInfoVector( serviceName );

	logger.log( Logger::DEBUG, "[Registry#addServiceListener] Add service listener to vector." );	

	ServiceListenerInfo* listenerInfo = new ServiceListenerInfo( bundleName, serviceName, serviceListener );
	vec->push_back( listenerInfo );

	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->addRegisteredListener( listenerInfo );

	vector<ServiceInfo*>* serviceVec = this->getServiceInfo( serviceName );

	this->notifyListenersAboutRegisteredService( bundleName, serviceVec, this->getServiceListenerInfoVector( serviceName ), serviceName );	
	logger.log( Logger::DEBUG, "[Registry#addServiceListener] Left." );				
}

void Registry::removeServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener ) 
{
	logger.log( Logger::DEBUG, "[Registry#removeServiceListener] Called, bundle name: %1", bundleName );
	this->removeFromServiceListenerInfoVector( bundleName, serviceListener );
	logger.log( Logger::DEBUG, "[Registry#removeServiceListener] Left" );
}

void Registry::removeFromServiceListenerInfoVector( const string& bundleName, IServiceListener::ConstPtr serviceListener )
{
	logger.log( Logger::DEBUG, "[Registry#removeFromServiceListenerInfoVector] Called." );
	map<string, vector<ServiceListenerInfo*>* >::iterator iter;   
	for( iter = this->serviceListenerMap.begin(); iter != this->serviceListenerMap.end(); iter++ ) {
		vector<ServiceListenerInfo*>* vec = iter->second;
		vector<ServiceListenerInfo*>::iterator vecIterator;
		for ( vecIterator = vec->begin(); vecIterator != vec->end(); vecIterator++ )
		{
			if ( (*vecIterator)->getServiceListenerObj() == serviceListener )
			{				
				logger.log( Logger::DEBUG, "[Registry#removeFromServiceListenerInfoVector] Removed." );
				
				BundleInfo* bundleInfo = this->getBundleInfo( bundleName );						
				bundleInfo->removeUsedService( (*vecIterator)->getServiceName() );
				bundleInfo->removeRegisteredListener( (*vecIterator) );		
				vec->erase( vecIterator );
				break;
			}
		}
	}	
	logger.log( Logger::DEBUG, "[Registry#removeFromServiceListenerInfoVector] Left." );
}