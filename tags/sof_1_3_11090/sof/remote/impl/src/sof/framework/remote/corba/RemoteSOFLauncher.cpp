template<
	class ThreadingModel,
	template <class> class CreationPolicy>
Logger& RemoteSOFLauncher<ThreadingModel, CreationPolicy>::logger = LoggerFactory::getLogger( "Framework" );

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
RemoteSOFLauncher<ThreadingModel, CreationPolicy>::RemoteSOFLauncher( CORBAHelper& cHelper, const string& procName ) : corbaHelper( cHelper ), processName( procName )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#ctor] Called." );
	this->registry = this->createRegistry();
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
RemoteSOFLauncher<ThreadingModel, CreationPolicy>::~RemoteSOFLauncher() 
{
	logger.log( Logger::LOG_DEBUG, "[Launcher#destructor] Called." );
	delete (this->registry);
}


template<
	class ThreadingModel,
	template <class> class CreationPolicy>
IRegistry& RemoteSOFLauncher<ThreadingModel, CreationPolicy>::getRegistry()
{
	return (*(this->registry));
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void RemoteSOFLauncher<ThreadingModel, CreationPolicy>::setLogLevel( Logger::LogLevel level )
{
	LoggerFactory::setLogLevel( level );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
IRegistry* RemoteSOFLauncher<ThreadingModel, CreationPolicy>::createRegistry()
{
	// TODO: create IRegistryFacadeImpl
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#createRegistry] Called." );
	// TODO: memory leak, fix it!
	this->registry =  new IRemoteRegistryImpl<ThreadingModel>( this->corbaHelper );
	return new IRegistryFacadeImpl( this->corbaHelper, (*registry) );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
IBundleContext* RemoteSOFLauncher<ThreadingModel, CreationPolicy>::createBundleContext( const string& bundleName )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#createBundleContext] Called." );
	return new IRemoteBundleContextImpl( bundleName, (*(this->registry)), this->corbaHelper );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void RemoteSOFLauncher<ThreadingModel, CreationPolicy>::start( vector<BundleConfiguration> &configVector )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Called." );

	vector<BundleConfiguration>::iterator itVectorData;
	itVectorData = configVector.begin();
	for(itVectorData = configVector.begin(); itVectorData != configVector.end(); itVectorData++)
	{
		BundleConfiguration bundleConfig = *(itVectorData);
		this->objectCreator.setSearchConfiguration( true, 
			bundleConfig.getLibraryPath(), bundleConfig.getLibraryName() );
		
		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Reading configuration: Library path: %1, class name: %2",
			bundleConfig.getLibraryPath(), bundleConfig.getClassName() );
		
		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Loading bundle activator: Library path: %1, class name: %2",
			bundleConfig.getLibraryPath(), bundleConfig.getClassName() );
		
		IRemoteBundleActivator* bundleActivator;
		try
		{
			bundleActivator = this->objectCreator.createObject( bundleConfig.getClassName() );
		}
		catch( ObjectCreationException &exc )
		{
			string msg( exc.what() );
			logger.log( Logger::LOG_ERROR, "[RemoteSOFLauncher#start] Error during loading bundle activator, exc: %1", msg );
			continue;
		}

		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Create bundle context." );
		IBundleContext* bundleCtxt = this->createBundleContext( bundleConfig.getBundleName() );
		
		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Create bundle info." );		
		RemoteBundleInfo* bundleInfo = new RemoteBundleInfo( bundleConfig.getBundleName(), false, bundleActivator, bundleCtxt );		

		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Add bundle info object to registry." );	
		this->registry->addBundleInfo( *bundleInfo );

		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Start bundle." );
		
		IRemoteBundleContext* bc = dynamic_cast<IRemoteBundleContext*>( bundleCtxt );

		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Start activator" );
		bundleActivator->start( bc );
		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Activator started." );
	}	
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void RemoteSOFLauncher<ThreadingModel, CreationPolicy>::startAdministrationBundle()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#startAdministrationBundle] Called." );
	
	this->startRemoteAdminService();

	IRemoteBundleActivator* adminBundleActivator = this->objectCreator.createObject( "sof::services::admin::remote::RemoteAdministrationActivator" );
	IBundleContext* bundleCtxt = this->createBundleContext( "RemoteAdministrationBundle" );
	
	IRemoteBundleContext* bc = dynamic_cast<IRemoteBundleContext*>( bundleCtxt );

	BundleInfoBase* bundleInfo = new RemoteBundleInfo( "RemoteAdministrationBundle", true, adminBundleActivator, bundleCtxt );		
	this->registry->addBundleInfo( *bundleInfo );

	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#start] Start bundle." );
		
	RemoteAdministrationActivator* adminActivator = static_cast<RemoteAdministrationActivator*> (adminBundleActivator);	
	adminActivator->setAdministrationProvider( this );
	adminActivator->start( bc );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void RemoteSOFLauncher<ThreadingModel, CreationPolicy>::stop()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#stop] Called." );	
	this->registry->removeAllBundleInfos();
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void RemoteSOFLauncher<ThreadingModel, CreationPolicy>::startBundle( BundleConfiguration bundleConfig )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#startBundle] Called, bundle config: %1", bundleConfig.toString() );	
	vector<BundleConfiguration> vec;
	vec.push_back( bundleConfig );
	this->start( vec );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void RemoteSOFLauncher<ThreadingModel, CreationPolicy>::stopBundle( const string& bundleName )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#stopBundle] Called, bundle name: %1", bundleName );		
	this->registry->removeBundleInfo( bundleName );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
vector<string> RemoteSOFLauncher<ThreadingModel, CreationPolicy>::getBundleNames()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#getBundleNames] Called." );		
	vector<string> bundleNameVec;
	vector<BundleInfoBase*> vec = this->registry->getBundleInfos();
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#getBundleNames] Iterate through BundleInfoBase vector." );		
	vector<BundleInfoBase*>::iterator iter;
	for ( iter = vec.begin(); iter != vec.end(); iter++ )
	{
		logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#getBundleNames] Name: %1", (*iter)->getBundleName() );	
		bundleNameVec.push_back( (*iter)->getBundleName() );
	}
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#getBundleNames] Return bundle name vector." );		
	return bundleNameVec;
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
string RemoteSOFLauncher<ThreadingModel, CreationPolicy>::dumpBundleInfo( const string& bundleName )
{
	BundleInfoBase* bi = this->registry->getBundleInfo( bundleName );
	if ( bi == 0 )
	{
		return "Bundle not available!";
	}
	else
	{
		return bi->toString();
	}
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
string RemoteSOFLauncher<ThreadingModel, CreationPolicy>::dumpAllBundleNames()
{
	vector<BundleInfoBase*> vec = this->registry->getBundleInfos();
	vector<BundleInfoBase*>::iterator it;
	
	ostringstream stream;
	stream << "*** Started Bundles *** " << endl;

	for ( it = vec.begin(); it != vec.end(); it++ )
	{
		stream << (*it)->getBundleName() << endl;				
	}
	stream << endl;	
	return stream.str();
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
BundleInfoBase& RemoteSOFLauncher<ThreadingModel, CreationPolicy>::getBundleInfo( const string& bundleName )
{
	return ( * ( this->registry->getBundleInfo( bundleName ) ) );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void RemoteSOFLauncher<ThreadingModel, CreationPolicy>::startRemoteAdminService()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteSOFLauncher#startRemoteAdminService] Called." );		
	
	CORBAAdminServiceImpl* adminService = new CORBAAdminServiceImpl( ( *this ) );
	CORBA::Object_var obj = this->corbaHelper.activateObject( adminService );
	this->corbaHelper.registerObject( obj, CORBAHelper::REMOTE_ADMIN_PATH, this->processName );
}
