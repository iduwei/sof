#include "Launcher.h"

#include <iostream>
#include <sstream>

#include "IBundleContextImpl.h"
#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"
#include "../services/admin/AdministrationActivator.h"
#include "BundleInfo.h"

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::services::admin;

Logger& Launcher::logger = LoggerFactory::getLogger( "Framework" );

Launcher::Launcher() 
{
	logger.log( Logger::DEBUG, "[Launcher#ctor] Called." );
}

Registry& Launcher::getRegistry()
{
	return this->registry;
}

void Launcher::setLogLevel( Logger::LogLevel level )
{
	LoggerFactory::setLogLevel( level );
}

void Launcher::start( vector<BundleConfiguration> &configVector )
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

void Launcher::startAdministrationBundle()
{
	logger.log( Logger::DEBUG, "[Launcher#startAdministrationBundle] Called." );
	IBundleActivator* adminBundleActivator = this->objectCreator.createObject( "sof::services::admin::AdministrationActivator" );
	IBundleContextImpl* bundleCtxt = new IBundleContextImpl( "AdministrationBundle", &( this->registry ) );
		
	BundleInfo* bundleInfo = new BundleInfo( "AdministrationBundle", adminBundleActivator, bundleCtxt );		
	this->registry.addBundleInfo( bundleInfo );

	logger.log( Logger::DEBUG, "[Launcher#start] Start bundle." );
		
	AdministrationActivator* adminActivator = static_cast<AdministrationActivator*> (adminBundleActivator);	
	adminActivator->setLauncher( this );
	adminActivator->start( bundleCtxt );
}

void Launcher::stop()
{
	logger.log( Logger::DEBUG, "[Launcher#stop] Called." );	
	this->registry.removeAllBundleInfos();
}

void Launcher::startBundle( BundleConfiguration bundleConfig )
{
	logger.log( Logger::DEBUG, "[Launcher#startBundle] Called, bundle config: %1", bundleConfig.toString() );	
	vector<BundleConfiguration> vec;
	vec.push_back( bundleConfig );
	this->start( vec );
}

void Launcher::stopBundle( const string& bundleName )
{
	logger.log( Logger::DEBUG, "[Launcher#stopBundle] Called, bundle name: %1", bundleName );		
	this->registry.removeBundleInfo( bundleName );
}

vector<string> Launcher::getBundleNames()
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

string Launcher::dumpBundleInfo( const string& bundleName )
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

string Launcher::dumpAllBundleNames()
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