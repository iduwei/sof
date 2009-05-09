#ifndef SERVICE_TRACKER_H
#define SERVICE_TRACKER_H

#include <string>

#include "IRemoteBundleContext.h"
#include "./generated/CORBAObjects.h"
#include "sof/framework/ServiceEvent.h"
#include "IRemoteServiceTrackerCustomizer.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"



using namespace std;

using namespace sof::framework;
using namespace sof::framework::remote::corba::generated;
using namespace sof::framework::remote::corba;
using namespace sof::util::logging;

namespace sof { namespace framework { namespace remote { namespace corba {

/**
 * The <code>ServiceTracker</code> class implements the
 * <code>IServiceListener</code> interface and listens for
 * registered and unregistered services.<br>
 * The service tracker class simplifies the work of application
 * developers for tracking services.
 */
class RemoteServiceTracker : public POA_sof::framework::remote::corba::generated::CORBAServiceListener
{
	private:

		/**
		 * The bundle context.
		 */
		IRemoteBundleContext::ConstPtr bundleCtxt;

		/**
		 * The customized service tracker which is notified
		 * when a service is registered or deregistered.
		 */
		IRemoteServiceTrackerCustomizer::ConstPtr serviceTracker;

		/**
		 * The name of the service the service tracker listens for.
		 */
		string serviceName;

		/**
		 * The logger instance.
		 */
		static Logger& logger;

	public:

		/**
		 * Creates instances of class <code>ServiceTracker</code>.
		 *
		 * @param bc
		 *			The bundle context.
		 *
		 * @param servName
		 *			The name of the service the service tracker listens for.
		 *
		 * @param customizer
		 *			The service tracker customizer which is notified when
		 *			a service is registered or deregistered.
		 */
		RemoteServiceTracker( IRemoteBundleContext::ConstPtr bc, const string &servName, 
			IRemoteServiceTrackerCustomizer::ConstPtr customizer );

		/**
		 * Destroys the service tracker object.
		 */
		~RemoteServiceTracker();

		/**
		 * Starts tracking for the specified service name. From now on
		 * the <code>IServiceTrackerCustomizer</code> instance is notified
		 * if a service is registered or deregistered.
		 */
		void startTracking();
		
		/**
		 * Stops service tracking. From now on
		 * the <code>IServiceTrackerCustomizer</code> instance 
		 * is no longer notified
		 * if a service is registered or deregistered.
		 */
		void stopTracking();

		/**
		 * Is called by the framework if the lifecycle of a service
		 * changed (registering, deregistering).
		 *
		 * @param serviceEvent
		 *			The event which occurred (registering, deregistering).
		 *
		 * @return True, if the service tracker is interested in the
		 *			changed service, otherwise false.
		 */
		CORBA::Boolean serviceChanged( const CORBAServiceEvent &serviceEvent );
		
};

}}}}

#endif