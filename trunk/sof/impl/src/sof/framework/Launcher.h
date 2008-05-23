#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <vector>
#include <iostream>
#include <sstream>

#include "IBundleActivator.h"
#include "Registry.h"
#include "../services/admin/AdministrationActivator.h"
#include "../services/admin/IAdministrationProvider.h"
#include "../config/BundleConfiguration.h"
#include "../instantiation/ObjectCreator.h"
#include "../util/logging/Logger.h"
#include "../util/logging/LoggerFactory.h"
#include "BundleInfo.h"
#include "IBundleContextImpl.h"

using namespace std;

using namespace sof::config;
using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::logging;
using namespace sof::services::admin;

namespace sof { namespace framework {

/**
 * The <code>Launcher</code> class is the entry point for
 * running the SOF framework.<br>
 * The main task of this class is to provide methods
 * for starting and stopping bundles.
 */
class Launcher : public IAdministrationProvider
{
	private:

		/**
		 * The <code>ObjectCreator</code> instance which is used
		 * for instantiating the <code>IBundleActivator</code>
		 * objects.
		 */
		ObjectCreator<IBundleActivator> objectCreator;

		/**
		 * The registry object which holds all relevant data of
		 * all bundles. It is the central administration object.
		 */
		Registry registry;

		/**
		 * The logger instance.
		 */
		static Logger& logger;

	public:

		/**
		 * Creates instances of class <code>Launcher</code>.
		 */
		Launcher();

		/**
		 * Sets the log level of the framework. Defines
		 * for example whether only error messages or
		 * also debug messages shall be logged.		 
		 *
		 * @param level
		 *			The log level (trace, debug, error).
		 */
		void setLogLevel( Logger::LogLevel level );

		/**
		 * Starts bundles. The bundles which are started are
		 * defined in a vector of <code>BundleConfiguration</code>
		 * objects.
		 *
		 * @param configuration
		 *				The vector of <code>BundleConfiguration</code>
		 *				objects whereas each object describes what
		 *				bundle shall be started.
		 */
		void start( vector<BundleConfiguration> &configuration );

		/**
		 * Stops all bundles which were started.
		 */
		void stop();

		/**
		 * Starts a specific bundle. Can be also called after
		 * a <code>start()</code>.
		 *
		 * @param bundleConfig
		 *				The object containing information which
		 *				bundle must be started.
		 */
		void startBundle( BundleConfiguration bundleConfig );

		/**
		 * Stops a bundle.
		 *
		 * @param bundleName
		 *				The name of the bundle which is stopped.
		 */
		void stopBundle( const string& bundleName );

		/**
		 * Starts the administration bundle (which
		 * provides a console for user inputs).
		 */
		void startAdministrationBundle();

		/**
		 * Returns the names of all started bundles.
		 *
		 * @return
		 *		A vector containing all bundle names.
		 */
		vector<string> getBundleNames();			

		/**
		 * Dumps all information (registered services,
		 * registered service listeners, services in use)
		 * of a bundle.
		 *
		 * @param bundleName
		 *				The name of the bundle.
		 *
		 * @return
		 *				A string containing all information
		 *				about a bundle.
		 */
		string dumpBundleInfo( const string& bundleName );

		/**
		 * Dumps the name of all started bundles.
		 *
		 * @return
		 *			A string containing all bundle names.
		 */
		string dumpAllBundleNames();

		/**
		 * Returns the registry object.
		 *
		 * @return
		 *			The registry object.
		 */
		Registry& getRegistry();
};

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
	adminActivator->setAdministrationProvider( this );
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

}}

#endif