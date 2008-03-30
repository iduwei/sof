#ifndef BUNDLE_INFO_H
#define BUNDLE_INFO_H

#include <vector>
#include <string>

#include "IBundleActivator.h"
#include "IBundleContext.h"
#include "ServiceInfo.h"
#include "ServiceListenerInfo.h"

#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"

namespace sof { namespace framework {

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;

/**
 * The <code>BundleInfo</code> class contains all the relevant information
 * of a specific bundle:
 * <ul>
 *		<li>The name of the bundle.
 *		<li>The bundle activator.
 *		<li>The bundle context.
 *		<li>The list of services which were registered by the bundle.
 *		<li>The list of services which are used by the bundle.
 *		<li>The list of service listeners.<br>
 * </ul>
 */
class BundleInfo
{
	private:

		/**
		 * The name of the bundle.
		 */
		string bundleName;

		/**
		 * The bundle activator instance.
		 */
		IBundleActivator* activator;

		/**
		 * The bundle context.
		 */
		IBundleContext::ConstPtr bundleContext;

		/**
		 * Contains <code>ServiceInfo</code> objects of all registered services.
		 */
		vector<ServiceInfo*> registeredServices;

		/**
		 * Contains <code>ServiceInfo</code> objects of all used services.
		 */
		vector<ServiceInfo*> usedServices;
		
		/**
		 * Contains the registered service listeners.
		 */
		vector<ServiceListenerInfo*> registeredListeners;

		/**
		 * The logger instance.
		 */
		static Logger& logger;

	public:

		/**
		 * Creates instances of class <code>BundleInfo</code>.
		 *
		 * @param bundleName
		 *			The name of the bundle.
		 * @param act
		 *			The bundle activator instance.
		 * @param bundleCtxt
		 *			The bundle context.
		 */
		BundleInfo( const string& bundleName, IBundleActivator* act, IBundleContext::ConstPtr bundleCtxt );

		/**
		 * The destructor for cleaning resources.
		 */
		~BundleInfo();

		/**
		 * Returns the pointer to the bundle activator instance.
		 * 
		 * @return
		 *		The pointer to bundle activator instance.
		 */
		IBundleActivator* getBundleActivator();
		IBundleContext::ConstPtr getBundleContext();
		
		void addRegisteredService( ServiceInfo* serviceInfo );
		void removeDeregisteredService( ServiceInfo* serviceInfo );

		void addUsedService( ServiceInfo* serviceInfo );
		void removeUsedService( ServiceInfo* serviceInfo );
		void removeUsedService( const string& serviceName );
		void removeAllUsedServices();
		
		void addRegisteredListener( ServiceListenerInfo* listenerInfo );
		void removeRegisteredListener( ServiceListenerInfo* listenerInfo );

		string getBundleName();
		vector<ServiceInfo*> getRegisteredServices();
		vector<ServiceInfo*> getUsedServices();
		vector<ServiceListenerInfo*> getRegisteredListeners();
		
		string toString();
};

}}
#endif