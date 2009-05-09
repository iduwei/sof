#ifndef IREMOTE_SERVICE_TRACKER_CUSTOMIZER_H
#define IREMOTE_SERVICE_TRACKER_CUSTOMIZER_H

#include "RemoteServiceReference.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace sof::framework::remote::corba;

/**
 * The <code>IRemoteServiceTrackerCustomizer</code> interface provides methods 
 * which notifiy the implementing class when a service object was 
 * registered (<code>addingService</code>) or deregistered (<code>removedService</code>)
 * with the framework.<br>
 * For using this interface it has to be implemented and an instance of the implementing
 * class has to be passed to a <code>ServiceTracker</code> object.<p>
 * Example:<p>
 * <code>
 * ServiceTracker tracker = new ServiceTracker( bundleContext, "ServiceB", serviceTrackerCustomizer );<br>
 * this->tracker->startTracking();
 * </code><p>
 * Afterwards the service tracker object is started the tracker listens for service object changes
 * (registering, deregistering) and forwards the changes to the service tracker customizer.
 *
 */
class IRemoteServiceTrackerCustomizer
{
	public:

		/**
		 * Defines a constant pointer to the <code>IServiceTrackerCustomizer</code>
		 * object.
		 */
		typedef IRemoteServiceTrackerCustomizer* const ConstPtr;

		/**
		 * Is called when a service was registered with the framework.
		 * 
		 * @param ref
		 *			The <code>ServiceReference</code> which contains the
		 *			name of the service, the service properties etc.
		 *
		 * @return True, if the service tracker is interested in the registered
		 *			service, which means that it wants to use it. Otherwise false
		 *			is returned.
		 */
		virtual bool addingService( const RemoteServiceReference& ref ) = 0;
		
		/**
		 * Is called when a service was deregistered with the framework.
		 * 
		 * @param ref
		 *			The <code>ServiceReference</code> which contains the
		 *			name of the service, the service properties etc.
		 *
		 */		
		virtual void removedService( const RemoteServiceReference& ref ) = 0;
};

}}}}
#endif