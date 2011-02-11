template<class ThreadingModel>
IRemoteRegistryImpl<ThreadingModel>::IRemoteRegistryImpl( CORBAHelper& helper ) : corbaHelper( helper ) 
{
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#ctor] Called." );
}

template<class ThreadingModel>
IRemoteRegistryImpl<ThreadingModel>::~IRemoteRegistryImpl() 
{
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#destructor] Called." );
}


template<class ThreadingModel>
void IRemoteRegistryImpl<ThreadingModel>::stopActivator( const BundleInfoBase& bi ) 
{
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#stopActivator] Called." );	
	BundleInfoBase* bInfo = const_cast<BundleInfoBase*>( &bi );
	RemoteBundleInfo* bundleInfo = dynamic_cast<RemoteBundleInfo*>( bInfo );
	IRemoteBundleContext* bundleContext = dynamic_cast<IRemoteBundleContext*>( bundleInfo->getBundleContext() );
	bundleInfo->getRemoteBundleActivator()->stop( bundleContext );
}

template<class ThreadingModel>
void IRemoteRegistryImpl<ThreadingModel>::deleteActivator( const BundleInfoBase& bi ) 
{
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#deleteActivator] Called." );	
	BundleInfoBase* bInfo = const_cast<BundleInfoBase*>( &bi );
	RemoteBundleInfo* bundleInfo = dynamic_cast<RemoteBundleInfo*>( bInfo );
	delete ( bundleInfo->getRemoteBundleActivator() );
}

template<class ThreadingModel>
bool IRemoteRegistryImpl<ThreadingModel>::callServiceListenerObject( ServiceListenerInfoPtr info, ServiceInfoPtr serviceInfo, const ServiceEvent::EventType& eventType )
{
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, 
		"[IRemoteRegistryImpl#callServiceListenerObject] Called, listenerInfo: %1", 
		info->toString() );
			
	RemoteServiceListenerInfo* corbaListenerInfo = dynamic_cast<RemoteServiceListenerInfo*>( info.GetRawPointer() );
	
	RemoteServiceInfo* corbaServiceInfo = dynamic_cast<RemoteServiceInfo*> (serviceInfo.GetRawPointer());

	RemoteServiceReference remoteServiceRef( corbaServiceInfo->getServiceName(), 
			corbaServiceInfo->getProperties(), 
			corbaServiceInfo->getRemoteService(), 
			corbaServiceInfo->getRemoteServiceID() );

	RemoteServiceEvent serviceEvent( eventType, remoteServiceRef );

	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, 
		"[IRemoteRegistryImpl#callServiceListenerObject] Getting remote service listener." );
	
	CORBAServiceListener_var remoteListener = CORBAServiceListener::_duplicate( corbaListenerInfo->getRemoteServiceListener() );

	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, 
		"[IRemoteRegistryImpl#callServiceListenerObject] Converting service event to remote service event." );
	
	CORBAServiceEvent servEvent = this->corbaHelper.convertEvent( serviceEvent );
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#callServiceListenerObject] Call service listener object." );		
	CORBA::Boolean result =  remoteListener->serviceChanged( servEvent );
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#callServiceListenerObject] Service listener object called." );			
	return result;
}

template<class ThreadingModel>
bool IRemoteRegistryImpl<ThreadingModel>::areServiceListenerObjectsEqual( ServiceListenerInfoPtr info1, ServiceListenerInfoPtr info2 )
{
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, 
		"[IRemoteRegistryImpl#areServiceListenerObjectsEqual] Called, info1: %1, info2: %2", info1->toString(), info2->toString() );

	RemoteServiceListenerInfo* corbaServiceListenerInfo1 = dynamic_cast<RemoteServiceListenerInfo*> (info1.GetRawPointer());
	
	RemoteServiceListenerInfo* corbaServiceListenerInfo2 = dynamic_cast<RemoteServiceListenerInfo*> (info2.GetRawPointer());
	
	if ( corbaServiceListenerInfo1->getRemoteServiceListenerID() == corbaServiceListenerInfo2->getRemoteServiceListenerID() )
	{
		IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#areServiceListenerObjectsEqual] Objects are equal." );	
		return true;
	}
	else
	{
		IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRemoteRegistryImpl#areServiceListenerObjectsEqual] Objects are NOT equal." );	
		return false;
	}	
}

template<class ThreadingModel>
IServiceRegistration::ConstPtr IRemoteRegistryImpl<ThreadingModel>::createServiceRegistrationObject( const string& bundleName, ServiceInfoPtr serviceInfo ) 
{
	IRegistryImpl<ThreadingModel>::logger.log( Logger::LOG_DEBUG, "[IRegistryImpl#createServiceRegistrationObject] Called, return null" );	
	return NULL;
}