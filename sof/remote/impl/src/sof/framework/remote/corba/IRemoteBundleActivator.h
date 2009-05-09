#ifndef IREMOTE_BUNDLE_ACTIVATOR_H
#define IREMOTE_BUNDLE_ACTIVATOR_H

#include "IRemoteBundleContext.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace sof::framework::remote::corba;

/**
 * A piece of software can be regarded as software bundle when it
 * implements the <code>BundleActivator</code> interface which is responsible 
 * for starting and stopping the software bundle.<br>
 * The framework not the application developer is responsible creating,
 * starting and stopping the bundle activator instance.
 */
class IRemoteBundleActivator 
{
	public:

		/**
		 * Destroys the bundle activator object.
		 */
		virtual ~IRemoteBundleActivator() {};

		/**
		 * Starts the bundle activator instance and passes a bundle context
		 * object which provides methods for registering services, service listeners
		 * etc.
		 *
		 * @param context
		 *			The bundle context.
		 */
		virtual void start( IRemoteBundleContext::ConstPtr context ) = 0;

		/**
		 * Stops the bundle activator instance.
		 *
		 * @param context
		 *			The bundle context.
		 */
		
		virtual void stop( IRemoteBundleContext::ConstPtr context ) = 0;
};

} } } }

#endif