template<class ThreadingModel>
IRemoteRegistryImpl<ThreadingModel>::IRemoteRegistryImpl( CORBAHelper& helper ) : corbaHelper( helper ) 
{
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#ctor] Called." );
}

template<class ThreadingModel>
IRemoteRegistryImpl<ThreadingModel>::~IRemoteRegistryImpl() 
{
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#destructor] Called." );
}


template<class ThreadingModel>
void IRemoteRegistryImpl<ThreadingModel>::stopActivator( BundleInfoBase* bi ) 
{
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#stopActivator] Called." );	
	RemoteBundleInfo* bundleInfo = dynamic_cast<RemoteBundleInfo*>( bi );
	IRemoteBundleContext* bundleContext = dynamic_cast<IRemoteBundleContext*>( bundleInfo->getBundleContext() );
	bundleInfo->getRemoteBundleActivator()->stop( bundleContext );
}

template<class ThreadingModel>
void IRemoteRegistryImpl<ThreadingModel>::deleteActivator( BundleInfoBase* bi ) 
{
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#deleteActivator] Called." );	
	RemoteBundleInfo* bundleInfo = dynamic_cast<RemoteBundleInfo*>( bi );
	delete ( bundleInfo->getRemoteBundleActivator() );
}

template<class ThreadingModel>
bool IRemoteRegistryImpl<ThreadingModel>::callServiceListenerObject( const ServiceListenerInfo& info, const ServiceEvent& serviceEvent )
{
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#callServiceListenerObject] Called, listenerInfo: %1, event: %2", 
		info.toString(), serviceEvent.toString() );
		
	ServiceListenerInfo* serviceListenerInfo = const_cast<ServiceListenerInfo*>( &info );
	RemoteServiceListenerInfo* corbaListenerInfo = dynamic_cast<RemoteServiceListenerInfo*>( serviceListenerInfo );
	
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#callServiceListenerObject] Getting remote service listener." );
	
	CORBAServiceListener_var remoteListener = CORBAServiceListener::_duplicate( corbaListenerInfo->getRemoteServiceListener() );

	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#callServiceListenerObject] Converting service event to remote service event." );
	
	CORBAServiceEvent servEvent = this->corbaHelper.convertEvent( serviceEvent );
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#callServiceListenerObject] Call service listener object." );		
	CORBA::Boolean result =  remoteListener->serviceChanged( servEvent );
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#callServiceListenerObject] Service listener object called." );			
	return result;
}

template<class ThreadingModel>
ServiceReference* IRemoteRegistryImpl<ThreadingModel>::createServiceReference( const ServiceInfo& serviceInfo )
{
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#createServiceReference] Called, serviceInfo: %1", 
		serviceInfo.toString() );
	
	ServiceInfo* tempServiceInfo = const_cast<ServiceInfo*>( &serviceInfo );
	RemoteServiceInfo* corbaServiceInfo = dynamic_cast<RemoteServiceInfo*> (tempServiceInfo);
	return new RemoteServiceReference( corbaServiceInfo->getServiceName(), corbaServiceInfo->getProperties(), corbaServiceInfo->getRemoteService(), corbaServiceInfo->getRemoteServiceID() );
}

template<class ThreadingModel>
bool IRemoteRegistryImpl<ThreadingModel>::areServiceListenerObjectsEqual( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 )
{
	logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#areServiceListenerObjectsEqual] Called, info1: %1, info2: %2", info1.toString(), info2.toString() );

	ServiceListenerInfo* serviceListenerInfo1 = const_cast<ServiceListenerInfo*> (&info1);
	RemoteServiceListenerInfo* corbaServiceListenerInfo1 = dynamic_cast<RemoteServiceListenerInfo*> (serviceListenerInfo1);
	
	ServiceListenerInfo* serviceListenerInfo2 = const_cast<ServiceListenerInfo*> (&info2);
	RemoteServiceListenerInfo* corbaServiceListenerInfo2 = dynamic_cast<RemoteServiceListenerInfo*> (serviceListenerInfo2);
	
	if ( corbaServiceListenerInfo1->getRemoteServiceListenerID() == corbaServiceListenerInfo2->getRemoteServiceListenerID() )
	{
		logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#areServiceListenerObjectsEqual] Objects are equal." );	
		return true;
	}
	else
	{
		logger.log( Logger::DEBUG, "[IRemoteRegistryImpl#areServiceListenerObjectsEqual] Objects are NOT equal." );	
		return false;
	}	
}