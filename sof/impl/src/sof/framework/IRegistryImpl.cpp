template<class ThreadingModel>
Logger& IRegistryImpl<ThreadingModel>::logger = LoggerFactory::getLogger( "Framework" );

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::addBundleInfo( BundleInfo* bundleInfo ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#addBundleInfo] Called, bundleName: %1", bundleInfo->getBundleName() );
	this->bundleInfoVec.push_back( bundleInfo );
}

template<class ThreadingModel>
BundleInfo* IRegistryImpl<ThreadingModel>::getBundleInfo( const string &bundleName )
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#getBundleInfo] Called, bundleName: %1", bundleName );
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

template<class ThreadingModel>
vector<BundleInfo*> IRegistryImpl<ThreadingModel>::getBundleInfos()
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	return this->bundleInfoVec;
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeAllBundleInfos()
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#removeAllBundleInfos] Called." );

	// At first the name of the bundles have to be cached in a vector
	// in inverted order the bundles were started.
	vector<string> bundleNames;
	vector<BundleInfo*>::reverse_iterator iter;
	for ( iter = this->bundleInfoVec.rbegin(); iter < this->bundleInfoVec.rend(); iter++ )
	{						
		logger.log( Logger::DEBUG, "[IRegistryImpl#removeAllBundleInfos] Add bundle name: %1", (*iter)->getBundleName() );
		bundleNames.push_back( (*iter)->getBundleName() );
	}	

	vector<string>::iterator strIterator;
	for ( strIterator = bundleNames.begin(); strIterator != bundleNames.end(); strIterator++ )
	{
		logger.log( Logger::DEBUG, "[Registry#removeAllBundleInfos] Remove bundle: %1", (*strIterator) );
		this->removeBundleInfo( (*strIterator) );
	}
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeAllBundleInfos] Left." );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeBundleInfo( const string &bundleName ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#removeBundleInfo] Called, bundleName: %1", bundleName );
	
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
		logger.log( Logger::DEBUG, "[IRegistryImpl#removeBundleInfo] Deregister service: %1", (*iter)->getServiceName() );	
		this->removeServiceInfo( bundleName, *iter );
	}

	vector<ServiceListenerInfo*> serviceListenerInfos = bi->getRegisteredListeners();
	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfos.begin(); listenerIter != serviceListenerInfos.end(); listenerIter++ )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#removeBundleInfo] Remove listener: %1", (*listenerIter)->getServiceName() );	
		this->removeServiceListener( bundleName, (*listenerIter)->getServiceListenerObj() );
	}	
	
	delete activator;
	delete (bi->getBundleContext());
	delete bi;
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeBundleInfo] Erase bundle info." );			
	this->bundleInfoVec.erase( bundleIter );
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeBundleInfo] Left" );			
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::addServiceInfo( const string& bundleName, const string &serviceName, ServiceInfo* serviceInfo ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceInfo] Called, bundle name: %1, service name: %2", bundleName, serviceName );	

	this->addToServiceInfoVector( serviceName, serviceInfo );

	// adding ServiceInfo object to BundleInfo object
	this->addRegisteredServiceToBundleInfo( bundleName, serviceInfo );	

	// notifying all Listeners about new registered service
	vector<ServiceListenerInfo*>* serviceListenerInfoVec = this->getServiceListenerInfoVector( serviceName );
	this->notifyListenersAboutRegisteredService( bundleName, serviceInfo, serviceListenerInfoVec, serviceName );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeServiceInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#removeServiceInfo] Called, serviceInfo: %1", 
		serviceInfo->toString() );	
	this->removeFromServiceInfoVector( serviceInfo );
	vector<ServiceListenerInfo*>* serviceListenerInfoVec = this->getServiceListenerInfoVector( serviceInfo->getServiceName() );
	this->notifyListenersAboutDeregisteredService( bundleName, serviceInfo, serviceListenerInfoVec );
	this->removeDeregisteredServiceFromBundleInfo( bundleName, serviceInfo );	
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeServiceInfo] Left." );	
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::addRegisteredServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#addRegisteredServiceToBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->addRegisteredService( serviceInfo );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeDeregisteredServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeDeregisteredServiceFromBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->removeDeregisteredService( serviceInfo );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::addUsedServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#addUsedServiceToBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->addUsedService( serviceInfo );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeUsedServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeUsedServiceFromBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->removeUsedService( serviceInfo );
}

template<class ThreadingModel>
vector<ServiceInfo*>* IRegistryImpl<ThreadingModel>::addToServiceInfoVector( const string& serviceName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#getServiceInfoVector] Called, service name: %1", serviceName );	

	vector<ServiceInfo*>* serviceVec = this->getServiceInfo( serviceName );

	serviceVec->push_back( serviceInfo );	

	logger.log( Logger::DEBUG, "[IRegistryImpl#getServiceInfoVector] Left." );	

	return serviceVec;
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeFromServiceInfoVector( ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceInfoVector] Called, service name: %1", serviceInfo->getServiceName() );	

	vector<ServiceInfo*>* vec = this->getServiceInfo( serviceInfo->getServiceName() );
	
	vector<ServiceInfo*>::iterator iter;	

	for ( iter = vec->begin(); iter != vec->end(); iter++ )
	{
		if ( (*(*iter)) == (*serviceInfo) )
		{
			logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceInfoVector] Service was found in ServiceInfo vector." );	
			iter = vec->erase( iter );
			break;
		}	
	}
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceInfoVector] Left." );	
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::notifyListenersAboutRegisteredService( const string& bundleName, vector<ServiceInfo*>* serviceVec, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Called." );	

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
				logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Service listener is interested in registered service '%1'.",
					(*serviceIter)->getServiceName() );
				this->addUsedServiceToBundleInfo( bundleName, (*serviceIter) );	
			} else
			{
				logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Service listener is NOT interested in registered service '%1'.",
					(*serviceIter)->getServiceName() );
			}
		}
	}	

	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Left." );	
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::notifyListenersAboutRegisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Called." );	

	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfoVec->begin(); listenerIter != serviceListenerInfoVec->end(); listenerIter++ )
	{
		ServiceReference serviceRef( serviceInfo->getServiceName(), serviceInfo->getProperties(), serviceInfo->getService() );
		ServiceEvent serviceEvent( ServiceEvent::REGISTER, serviceRef );
		bool interested = (*listenerIter)->getServiceListenerObj()->serviceChanged( serviceEvent );
		if ( interested )
		{
			logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Service listener is interested in registered service '%1'.",
				serviceInfo->getServiceName() );
			this->addUsedServiceToBundleInfo( (*listenerIter)->getBundleName(), serviceInfo );		
		} else
		{
			logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Service listener is NOT interested in registered service '%1'.",
				serviceInfo->getServiceName() );
		}
	}	

	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutRegisteredService] Left." );	
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::notifyListenersAboutDeregisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutDeregisteredService] Called." );	

	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfoVec->begin(); listenerIter != serviceListenerInfoVec->end(); listenerIter++ )
	{
		ServiceReference serviceRef( serviceInfo->getServiceName(), serviceInfo->getProperties(), serviceInfo->getService() );
		ServiceEvent serviceEvent( ServiceEvent::UNREGISTER, serviceRef );
		bool interested = (*listenerIter)->getServiceListenerObj()->serviceChanged( serviceEvent );	
		if ( interested )
		{
			logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutDeregisteredService] Listener is interested in deregistered service '%1'.", serviceInfo->getServiceName() );	
			this->removeUsedServiceFromBundleInfo( (*listenerIter)->getBundleName(), serviceInfo );		
		} else
		{
			logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutDeregisteredService] Listener is NOT interested in deregistered service '%1'.", serviceInfo->getServiceName() );	
		}

	}	

	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutDeregisteredService] Left." );	
}

template<class ThreadingModel>
vector<ServiceInfo*>* IRegistryImpl<ThreadingModel>::getServiceInfo( const string& serviceName ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#getServiceInfo] Called, service name: %1", serviceName );	
	vector<ServiceInfo*>* vec = this->serviceInfoMap[serviceName];
	if ( vec == 0 )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#getServiceInfo] ServiceInfo vector is null, create one." );		
		vec = new vector<ServiceInfo*>;
		this->serviceInfoMap[serviceName] = vec;
	}
	logger.log( Logger::DEBUG, "[IRegistryImpl#getServiceInfo] Left." );		
	return vec;
}

template<class ThreadingModel>
vector<ServiceListenerInfo*>* IRegistryImpl<ThreadingModel>::getServiceListenerInfoVector( const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#getServiceListenerInfoVector] Called, service name: %1", serviceName );	
	vector<ServiceListenerInfo*>* vec = this->serviceListenerMap[serviceName];
	if ( vec == 0 )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#getServiceListenerInfoVector] ServiceListenerInfo vector is null, create one." );				
		vec = new vector<ServiceListenerInfo*>;
		this->serviceListenerMap[serviceName] = vec;
	}
	logger.log( Logger::DEBUG, "[IRegistryImpl#ServiceListenerInfo] Left." );	
	return vec;
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::addServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener, const string &serviceName ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceListener] Called, bundle name: %1, service name: %2", bundleName, serviceName );			
	vector<ServiceListenerInfo*>* vec = this->getServiceListenerInfoVector( serviceName );

	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceListener] Add service listener to vector." );	

	ServiceListenerInfo* listenerInfo = new ServiceListenerInfo( bundleName, serviceName, serviceListener );
	vec->push_back( listenerInfo );

	BundleInfo* bundleInfo = this->getBundleInfo( bundleName );
	bundleInfo->addRegisteredListener( listenerInfo );

	vector<ServiceInfo*>* serviceVec = this->getServiceInfo( serviceName );

	this->notifyListenersAboutRegisteredService( bundleName, serviceVec, this->getServiceListenerInfoVector( serviceName ), serviceName );	
	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceListener] Left." );				
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#removeServiceListener] Called, bundle name: %1", bundleName );
	this->removeFromServiceListenerInfoVector( bundleName, serviceListener );
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeServiceListener] Left" );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeFromServiceListenerInfoVector( const string& bundleName, IServiceListener::ConstPtr serviceListener )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] Called." );
	map<string, vector<ServiceListenerInfo*>* >::iterator iter;   
	for( iter = this->serviceListenerMap.begin(); iter != this->serviceListenerMap.end(); iter++ ) {
		vector<ServiceListenerInfo*>* vec = iter->second;
		vector<ServiceListenerInfo*>::iterator vecIterator;
		for ( vecIterator = vec->begin(); vecIterator != vec->end(); vecIterator++ )
		{
			if ( (*vecIterator)->getServiceListenerObj() == serviceListener )
			{				
				logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] Removed." );
				
				BundleInfo* bundleInfo = this->getBundleInfo( bundleName );						
				bundleInfo->removeUsedService( (*vecIterator)->getServiceName() );
				bundleInfo->removeRegisteredListener( (*vecIterator) );		
				vec->erase( vecIterator );
				break;
			}
		}
	}	
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] Left." );
}