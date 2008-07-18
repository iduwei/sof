#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <vector>
#include <iostream>
#include <sstream>

#include "IBundleActivator.h"
#include "IRegistry.h"
#include "IRegistryImpl.h"
#include "BundleInfo.h"
#include "IBundleContextImpl.h"

#include "../services/admin/AdministrationActivator.h"
#include "../services/admin/IAdministrationProvider.h"
#include "../config/BundleConfiguration.h"
#include "../instantiation/ObjectCreator.h"
#include "../util/logging/Logger.h"
#include "../util/logging/LoggerFactory.h"

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
template<
	class ThreadingModel,
	template <class> class CreationPolicy = NullCreator>
class Launcher : public IAdministrationProvider
{
	private:

		/**
		 * The <code>ObjectCreator</code> instance which is used
		 * for instantiating the <code>IBundleActivator</code>
		 * objects.
		 */
		ObjectCreator<IBundleActivator,CreationPolicy> objectCreator;

		/**
		 * The registry object which holds all relevant data of
		 * all bundles. It is the central administration object.
		 */
		IRegistryImpl<ThreadingModel> registry;

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
		IRegistry& getRegistry();
};

#include "Launcher.cpp"

}}

#endif