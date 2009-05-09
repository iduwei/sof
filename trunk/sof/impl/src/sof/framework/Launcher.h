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
#include "../util/threading/SingleThreaded.h"

using namespace std;

using namespace sof::config;
using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::logging;
using namespace sof::util::threading;
using namespace sof::services::admin;

namespace sof { namespace framework {

/**
 * The <code>Launcher</code> class is the entry point for
 * running the SOF framework.<br>
 * The main task of this class is to provide methods
 * for starting and stopping bundles.
 */
template<
	class ThreadingModel = SingleThreaded,
	template <class> class CreationPolicy = NullCreator>
class Launcher : public IAdministrationProvider
{
	protected:

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
		IRegistry* registry;		

		/**
		 * The logger instance.
		 */
		static Logger& logger;

		/**
		 * Creates the registry instance.
		 *
		 * @return
		 *		The registry instance.
		 */
		virtual IRegistry* createRegistry();

		/**
		 * Creates the bundle context instances.
		 *
		 * @param bundleName
		 *				The name of the bundle the bundle context object is
	     *				created for.
		 *
		 * @return
		 *				The bundle context instance.
		 */
		virtual IBundleContext* createBundleContext( const string& bundleName );

	public:

		/**
		 * Creates instances of class <code>Launcher</code>.
		 */
		Launcher();

		/**
		 * Destroys the <code>Launcher</code> instance.
		 */
		virtual ~Launcher();

		/**
		 * Sets the log level of the framework. Defines
		 * for example whether only error messages or
		 * also debug messages shall be logged.		 
		 *
		 * @param level
		 *			The log level (trace, debug, error).
		 */
		virtual void setLogLevel( Logger::LogLevel level );

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
		virtual void start( vector<BundleConfiguration> &configuration );

		/**
		 * Stops all bundles which were started.
		 */
		virtual void stop();

		/**
		 * Starts a specific bundle. Can be also called after
		 * a <code>start()</code>.
		 *
		 * @param bundleConfig
		 *				The object containing information which
		 *				bundle must be started.
		 */
		virtual void startBundle( BundleConfiguration bundleConfig );

		/**
		 * Stops a bundle.
		 *
		 * @param bundleName
		 *				The name of the bundle which is stopped.
		 */
		virtual void stopBundle( const string& bundleName );

		/**
		 * Starts the administration bundle (which
		 * provides a console for user inputs).
		 */
		virtual void startAdministrationBundle();

		/**
		 * Returns the names of all started bundles.
		 *
		 * @return
		 *		A vector containing all bundle names.
		 */
		virtual vector<string> getBundleNames();			

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
		virtual string dumpBundleInfo( const string& bundleName );

		/**
		 * Dumps the name of all started bundles.
		 *
		 * @return
		 *			A string containing all bundle names.
		 */
		virtual string dumpAllBundleNames();

		/**
		 * Returns the registry object.
		 *
		 * @return
		 *			The registry object.
		 */
		virtual IRegistry& getRegistry();
};

#include "Launcher.cpp"

}}

#endif