template<class ThreadingModel>
Logger& IRegistryImpl<ThreadingModel>::logger = LoggerFactory::getLogger( "Framework" );

template<class ThreadingModel>
IRegistryImpl<ThreadingModel>::~IRegistryImpl() 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#destructor] Called." );
}
 
template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::addBundleInfo( BundleInfoBase* bundleInfo ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#addBundleInfo] Called, bundleName: %1", bundleInfo->getBundleName() );
	this->bundleInfoVec.push_back( bundleInfo );
}

template<class ThreadingModel>
BundleInfoBase* IRegistryImpl<ThreadingModel>::getBundleInfo( const string &bundleName )
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#getBundleInfo] Called, bundleName: %1", bundleName );
	vector<BundleInfoBase*>::iterator iter;
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
vector<BundleInfoBase*> IRegistryImpl<ThreadingModel>::getBundleInfos()
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
	vector<BundleInfoBase*>::reverse_iterator iter;
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
	
	BundleInfoBase* bi;
	vector<BundleInfoBase*>::iterator bundleIter;
	for ( bundleIter = this->bundleInfoVec.begin(); bundleIter != this->bundleInfoVec.end(); bundleIter++ )
	{
		if ( (*bundleIter)->getBundleName() == bundleName )
		{
			bi = (*bundleIter);			
			break;
		}
	}
	
	this->stopActivator( bi );	

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
		this->removeServiceListener( bundleName, (*(*listenerIter)) );
	}	
	
	delete (bi->getBundleContext());
	delete bi;
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeBundleInfo] Erase bundle info." );			
	this->bundleInfoVec.erase( bundleIter );
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeBundleInfo] Left" );			
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::stopActivator( BundleInfoBase* bi ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#stopActivator] Called." );	
	BundleInfo* bundleInfo = dynamic_cast<BundleInfo*>( bi );
	IBundleActivator* act = bundleInfo->getBundleActivator();
	act->stop( bi->getBundleContext() );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::deleteActivator( BundleInfoBase* bi ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#deleteActivator] Called." );	
	BundleInfo* bundleInfo = dynamic_cast<BundleInfo*>( bi );
	IBundleActivator* act = bundleInfo->getBundleActivator();
	delete act;
}

template<class ThreadingModel>
IServiceRegistration::ConstPtr IRegistryImpl<ThreadingModel>::addServiceInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{	
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	string serviceName = serviceInfo->getServiceName();
	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceInfo] Called, bundle name: %1, service name: %2", bundleName, serviceName );		

	this->addToServiceInfoVector( serviceName, serviceInfo );

	// adding ServiceInfo object to BundleInfo object
	this->addRegisteredServiceToBundleInfo( bundleName, serviceInfo );	

	// notifying all Listeners about new registered service
	vector<ServiceListenerInfo*>* serviceListenerInfoVec = this->getServiceListenerInfoVector( serviceName );
	this->notifyListenersAboutRegisteredService( bundleName, serviceInfo, serviceListenerInfoVec, serviceName );
	return new IServiceRegistrationImpl( bundleName, this, serviceInfo );
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
	BundleInfoBase* bundleInfo = this->getBundleInfo( bundleName );
	if ( bundleInfo == 0 )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#addRegisteredServiceToBundleInfo] No bundle info available, do nothing." ); 	
	}
	else
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#addRegisteredServiceToBundleInfo] Add registered service to bundle info." ); 	
		bundleInfo->addRegisteredService( serviceInfo );
	}	
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeDeregisteredServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeDeregisteredServiceFromBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfoBase* bundleInfo = this->getBundleInfo( bundleName );
	if ( bundleInfo == 0 )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#removeDeregisteredServiceFromBundleInfo] No bundle info available, do nothing." ); 	
	}
	else
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#removeDeregisteredServiceFromBundleInfo] Remove deregistered service from bundle info." ); 	
		bundleInfo->removeDeregisteredService( serviceInfo );
	}
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::addUsedServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#addUsedServiceToBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfoBase* bundleInfo = this->getBundleInfo( bundleName );
	if ( bundleInfo == 0 )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#addUsedServiceToBundleInfo] BundleInfo object does not exist (null), do nothing." );	
	}
	else
	{
		bundleInfo->addUsedService( serviceInfo );
	}	
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeUsedServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeUsedServiceFromBundleInfo] Called, bundle name: %1, service info: %2", 
		bundleName, serviceInfo->toString() );	
	BundleInfoBase* bundleInfo = this->getBundleInfo( bundleName );
	if ( bundleInfo != 0 )
	{
		bundleInfo->removeUsedService( serviceInfo );
	}
	else
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#removeUsedServiceFromBundleInfo] BundleInfo is null, do nothing." );	
	}
}

template<class ThreadingModel>
vector<ServiceInfo*>* IRegistryImpl<ThreadingModel>::addToServiceInfoVector( const string& serviceName, ServiceInfo* serviceInfo ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#addToServiceInfoVector] Called, service name: %1", serviceName );	

	vector<ServiceInfo*>* serviceVec = this->getServiceInfo( serviceName );

	serviceVec->push_back( serviceInfo );	

	logger.log( Logger::DEBUG, "[IRegistryImpl#addToServiceInfoVector] Left." );	

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
		// TODO: check why following statement can not be used (ServiceInfo class is called)
		//if ( (*(*iter)) == (*serviceInfo) )

		if ( (*iter)->equals( (*(*iter)), (*serviceInfo) ) )
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
			ServiceReference* serviceRef = this->createServiceReference( *(*serviceIter) );
			ServiceEvent serviceEvent( ServiceEvent::REGISTER, (*serviceRef) );
			
			bool interested = this->callServiceListenerObject( (*(*listenerIter)), serviceEvent );

			delete serviceRef;
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
		ServiceReference* serviceRef = this->createServiceReference( *serviceInfo );
		ServiceEvent serviceEvent( ServiceEvent::REGISTER, (*serviceRef) );
			
		bool interested = this->callServiceListenerObject( (*(*listenerIter)), serviceEvent );
		
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
void IRegistryImpl<ThreadingModel>::notifyListenerAboutRegisteredService( const string& bundleName, vector<ServiceInfo*>* serviceVec, ServiceListenerInfo* serviceListenerInfo, const string& serviceName ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenerAboutRegisteredService] Called." );	

	vector<ServiceInfo*>::iterator serviceIter;
	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenerAboutRegisteredService] Iterate through service info vector." );	
	for ( serviceIter = serviceVec->begin(); serviceIter != serviceVec->end(); serviceIter++ )
	{
		ServiceReference* serviceRef = this->createServiceReference( *(*serviceIter));
		ServiceEvent serviceEvent( ServiceEvent::REGISTER, (*serviceRef) );
		logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenerAboutRegisteredService] Service name: %1",				
			(*serviceIter)->getServiceName() );
		bool interested = this->callServiceListenerObject( (*serviceListenerInfo), serviceEvent );
		delete serviceRef;
		if ( interested )
		{
			logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenerAboutRegisteredService] Service listener is interested in registered service '%1'.",
				(*serviceIter)->getServiceName() );
			this->addUsedServiceToBundleInfo( bundleName, (*serviceIter) );	
		} else
		{
			logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenerAboutRegisteredService] Service listener is NOT interested in registered service '%1'.",
				(*serviceIter)->getServiceName() );
		}
	}
	

	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenerAboutRegisteredService] Left." );	
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::notifyListenersAboutDeregisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec ) 
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#notifyListenersAboutDeregisteredService] Called." );	

	vector<ServiceListenerInfo*>::iterator listenerIter;
	for ( listenerIter = serviceListenerInfoVec->begin(); listenerIter != serviceListenerInfoVec->end(); listenerIter++ )
	{
		ServiceReference* serviceRef = this->createServiceReference( *serviceInfo );
		ServiceEvent serviceEvent( ServiceEvent::UNREGISTER, (*serviceRef) );
			
		bool interested = this->callServiceListenerObject( (*(*listenerIter)), serviceEvent );

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
void IRegistryImpl<ThreadingModel>::addServiceListener( const string& bundleName, ServiceListenerInfo* listenerInfo ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	string serviceName = listenerInfo->getServiceName();
	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceListener] Called, bundle name: %1, service name: %2", bundleName, serviceName );			
	vector<ServiceListenerInfo*>* vec = this->getServiceListenerInfoVector( serviceName );

	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceListener] Add service listener to vector." );	

	vec->push_back( listenerInfo );

	BundleInfoBase* bundleInfo = this->getBundleInfo( bundleName );
	if ( bundleInfo == 0 )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceListener] Bundle info is null, can not add service listener to bundle info." );	
	}
	else
	{
		bundleInfo->addRegisteredListener( listenerInfo );
	}

	vector<ServiceInfo*>* serviceVec = this->getServiceInfo( serviceName );

	this->notifyListenerAboutRegisteredService( bundleName, serviceVec, listenerInfo, serviceName );	
	logger.log( Logger::DEBUG, "[IRegistryImpl#addServiceListener] Left." );				
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeServiceListener( const string& bundleName, const ServiceListenerInfo& serviceListener ) 
{
	// !!! synchronized access !!!
	ThreadingModel::Lock lock;

	logger.log( Logger::DEBUG, "[IRegistryImpl#removeServiceListener] Called, bundle name: %1", bundleName );
	this->removeFromServiceListenerInfoVector( bundleName, serviceListener );
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeServiceListener] Left" );
}

template<class ThreadingModel>
void IRegistryImpl<ThreadingModel>::removeFromServiceListenerInfoVector( const string& bundleName, const ServiceListenerInfo& serviceListener )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] Called." );
	map<string, vector<ServiceListenerInfo*>* >::iterator iter;   
	for( iter = this->serviceListenerMap.begin(); iter != this->serviceListenerMap.end(); iter++ ) {
		vector<ServiceListenerInfo*>* vec = iter->second;
		vector<ServiceListenerInfo*>::iterator vecIterator;
		for ( vecIterator = vec->begin(); vecIterator != vec->end(); vecIterator++ )
		{
			if ( this->areServiceListenerObjectsEqual( (*(*vecIterator)), serviceListener ) )
			{											
				BundleInfoBase* bundleInfo  = this->getBundleInfo( bundleName );
				if ( bundleInfo == 0 )
				{
					logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] BundleInfo object does not exist (null), do nothing." );	
				}
				else
				{
					logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] BundleInfo object exists, remove from vector." );	
					bundleInfo->removeUsedService( (*vecIterator)->getServiceName() );
					bundleInfo->removeRegisteredListener( (*vecIterator) );												
				}	

				logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] Removed." );				
				vec->erase( vecIterator );
				break;
			}
		}
	}	
	logger.log( Logger::DEBUG, "[IRegistryImpl#removeFromServiceListenerInfoVector] Left." );
}

template<class ThreadingModel>
bool IRegistryImpl<ThreadingModel>::areServiceListenerObjectsEqual( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#areServiceListenerObjectsEqual] Called, info1: %1, info2: %2", info1.toString(), info2.toString() );
	if ( info1.getServiceListenerObj() == info2.getServiceListenerObj() )
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#areServiceListenerObjectsEqual] Objects are equal." );	
		return true;
	}
	else
	{
		logger.log( Logger::DEBUG, "[IRegistryImpl#areServiceListenerObjectsEqual] Objects are NOT equal." );	
		return false;
	}	
}

template<class ThreadingModel>
bool IRegistryImpl<ThreadingModel>::callServiceListenerObject( const ServiceListenerInfo& info, const ServiceEvent& serviceEvent )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#callServiceListenerObject] Called, listenerInfo: %1, event: %2", 
		info.toString(), serviceEvent.toString() );
	return info.getServiceListenerObj()->serviceChanged( serviceEvent );
}

template<class ThreadingModel>
ServiceReference* IRegistryImpl<ThreadingModel>::createServiceReference( const ServiceInfo& serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRegistryImpl#createServiceReference] Called, serviceInfo: %1", 
		serviceInfo.toString() );
			
	return new ServiceReference( serviceInfo.getServiceName(), serviceInfo.getProperties(), serviceInfo.getService() );	
}