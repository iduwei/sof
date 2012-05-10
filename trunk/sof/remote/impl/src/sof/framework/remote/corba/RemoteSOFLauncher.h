#ifndef REMOTE_SOF_LAUNCHER_H
#define REMOTE_SOF_LAUNCHER_H

#include "sof/framework/Launcher.h"
#include "sof/framework/BundleInfoBase.h"

#include "./registry/IRegistryFacadeImpl.h"
#include "./registry/IRemoteRegistryImpl.h"
#include "../../../services/admin/remote/RemoteAdministrationActivator.h"
#include "IRemoteBundleActivator.h"
#include "IRemoteBundleContextImpl.h"
#include "RemoteBundleInfo.h"
#include "CORBAHelper.h"
#include "../../../services/admin/remote/corba/CORBAAdminServiceImpl.h"

using namespace std;

using namespace sof::framework;
using namespace sof::framework::remote::corba::registry;
using namespace sof::framework::remote::corba;
using namespace sof::services::admin::remote;
using namespace sof::services::admin::remote::corba;

namespace sof { namespace framework { namespace remote { namespace corba {

/**
 * The <code>Launcher</code> class is the entry point for
 * running the SOF framework.<br>
 * The main task of this class is to provide methods
 * for starting and stopping bundles.
 *
 * @author magr74
 */
template<
	class ThreadingModel = SingleThreaded,
	template <class> class CreationPolicy = NullCreator>
class RemoteSOFLauncher : public IAdministrationProvider
{
	protected:

		/**
		 * Provides CORBA relevant helper functions.
		 */
		CORBAHelper& corbaHelper;

		/**
		 * The name of the SOF process used for registering an administration/diagnosis
		 * component at naming service.
		 */
		string processName;

		/**
		 * The IP address where the <code>CORBARegistry</code> object is reachable.
		 */
		string ipAddress;

		/**
		 * The <code>ObjectCreator</code> instance which is used
		 * for instantiating the <code>IBundleActivator</code>
		 * objects.
		 */
		ObjectCreator<IRemoteBundleActivator,CreationPolicy> objectCreator;

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
		 * @param ip
		 * 			The IP address of the <code>CORBARegistry</code> object.
		 *
		 * @return
		 *		The registry instance.
		 */
		virtual IRegistry* createRegistry( const string& ip );

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


		/**
		 * Starts the remote admin service which allows external CORBA clients to 
		 * call administration and diagnosis functions.
		 */
		virtual void startRemoteAdminService();

	public:

		/**
		 * Creates instances of class <code>Launcher</code>.
		 *
		 * @param corbaHelper
		 *				Provides CORBA related helper functions.
	     * 
		 * @param procName
		 *				The name of the SOF process.
		 *
		 * @param ip
		 * 			The IP address of the <code>CORBARegistry</code> object.
		 */
		RemoteSOFLauncher( CORBAHelper& corbaHelper, const string& procName, const string& ip );

		/**
		 * Destroys the <code>Launcher</code> instance.
		 */
		virtual ~RemoteSOFLauncher();

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
		 * Returns the bundle info object for the given bundle name.
		 *
		 * @param bundleName
		 *				The bundle name.
		 *
		 * @return
		 *				The bundle info object.
		 */
		virtual BundleInfoBase& getBundleInfo( const string& bundleName );

		/**
		 * Returns the registry object.
		 *
		 * @return
		 *			The registry object.
		 */
		virtual IRegistry& getRegistry();
		
};
#include "RemoteSOFLauncher.cpp"

}}}}

#endif
