

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
Logger& Launcher<ThreadingModel, CreationPolicy>::logger = LoggerFactory::getLogger( "Framework" );

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
Launcher<ThreadingModel, CreationPolicy>::Launcher() 
{
	logger.log( Logger::DEBUG, "[Launcher#ctor] Called." );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
IRegistry& Launcher<ThreadingModel, CreationPolicy>::getRegistry()
{
	return this->registry;
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void Launcher<ThreadingModel, CreationPolicy>::setLogLevel( Logger::LogLevel level )
{
	LoggerFactory::setLogLevel( level );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void Launcher<ThreadingModel, CreationPolicy>::start( vector<BundleConfiguration> &configVector )
{
	logger.log( Logger::DEBUG, "[Launcher#start] Called." );

	vector<BundleConfiguration>::iterator itVectorData;
	itVectorData = configVector.begin();
	for(itVectorData = configVector.begin(); itVectorData != configVector.end(); itVectorData++)
	{
		BundleConfiguration bundleConfig = *(itVectorData);
		this->objectCreator.setSearchConfiguration( true, 
			bundleConfig.getLibraryPath(), bundleConfig.getLibraryName() );
		
		logger.log( Logger::DEBUG, "[Launcher#start] Reading configuration: Library path: %1, class name: %2",
			bundleConfig.getLibraryPath(), bundleConfig.getClassName() );
		
		logger.log( Logger::DEBUG, "[Launcher#start] Loading bundle activator: Library path: %1, class name: %2",
			bundleConfig.getLibraryPath(), bundleConfig.getClassName() );
		
		IBundleActivator* bundleActivator;
		try
		{
			bundleActivator = this->objectCreator.createObject( bundleConfig.getClassName() );
		}
		catch( ObjectCreationException &exc )
		{
			string msg( exc.what() );
			logger.log( Logger::ERROR_, "[Launcher#start] Error during loading bundle activator, exc: %1", msg );
			continue;
		}

		IBundleContextImpl* bundleCtxt = new IBundleContextImpl( bundleConfig.getBundleName(), &( this->registry ) );
		
		BundleInfo* bundleInfo = new BundleInfo( bundleConfig.getBundleName(), bundleActivator, bundleCtxt );		
		this->registry.addBundleInfo( bundleInfo );

		logger.log( Logger::DEBUG, "[Launcher#start] Start bundle." );
		
		bundleActivator->start( bundleCtxt );
	}	
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void Launcher<ThreadingModel, CreationPolicy>::startAdministrationBundle()
{
	logger.log( Logger::DEBUG, "[Launcher#startAdministrationBundle] Called." );
	IBundleActivator* adminBundleActivator = this->objectCreator.createObject( "sof::services::admin::AdministrationActivator" );
	IBundleContextImpl* bundleCtxt = new IBundleContextImpl( "AdministrationBundle", &( this->registry ) );
		
	BundleInfo* bundleInfo = new BundleInfo( "AdministrationBundle", adminBundleActivator, bundleCtxt );		
	this->registry.addBundleInfo( bundleInfo );

	logger.log( Logger::DEBUG, "[Launcher#start] Start bundle." );
		
	AdministrationActivator* adminActivator = static_cast<AdministrationActivator*> (adminBundleActivator);	
	adminActivator->setAdministrationProvider( this );
	adminActivator->start( bundleCtxt );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void Launcher<ThreadingModel, CreationPolicy>::stop()
{
	logger.log( Logger::DEBUG, "[Launcher#stop] Called." );	
	this->registry.removeAllBundleInfos();
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void Launcher<ThreadingModel, CreationPolicy>::startBundle( BundleConfiguration bundleConfig )
{
	logger.log( Logger::DEBUG, "[Launcher#startBundle] Called, bundle config: %1", bundleConfig.toString() );	
	vector<BundleConfiguration> vec;
	vec.push_back( bundleConfig );
	this->start( vec );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
void Launcher<ThreadingModel, CreationPolicy>::stopBundle( const string& bundleName )
{
	logger.log( Logger::DEBUG, "[Launcher#stopBundle] Called, bundle name: %1", bundleName );		
	this->registry.removeBundleInfo( bundleName );
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
vector<string> Launcher<ThreadingModel, CreationPolicy>::getBundleNames()
{
	vector<string> bundleNameVec;
	vector<BundleInfo*> vec = this->registry.getBundleInfos();
	vector<BundleInfo*>::iterator iter;
	for ( iter = vec.begin(); iter != vec.end(); iter++ )
	{
		bundleNameVec.push_back( (*iter)->getBundleName() );
	}
	return bundleNameVec;
}

template<
	class ThreadingModel,
	template <class> class CreationPolicy>
string Launcher<ThreadingModel, CreationPolicy>::dumpBundleInfo( const string& bundleName )
{
	BundleInfo* bi = this->registry.getBundleInfo( bundleName );
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
string Launcher<ThreadingModel, CreationPolicy>::dumpAllBundleNames()
{
	vector<BundleInfo*> vec = this->registry.getBundleInfos();
	vector<BundleInfo*>::iterator it;
	
	ostringstream stream;
	stream << "*** Started Bundles *** " << endl;

	for ( it = vec.begin(); it != vec.end(); it++ )
	{
		stream << (*it)->getBundleName() << endl;				
	}
	stream << endl;	
	return stream.str();
}