#ifndef LOCAL_SERVICE_TRACKER_H
#define LOCAL_SERVICE_TRACKER_H

#include <string>

#include "IRemoteBundleContext.h"
#include "ILocalServiceTrackerCustomizer.h"
#include "sof/framework/ServiceTracker.h"

using namespace std;

using namespace sof::framework;
using namespace sof::framework::remote::corba;

namespace sof { namespace framework { namespace remote { namespace corba {

/**
 * The <code>LocalServiceTracker</code> class provides the same
 * functionality as the <code>ServiceTracker</code> class. The only
 * difference is the class name which makes clear that the
 * <code>LocalServiceTracker</code> class is used for tracking local
 * services at the Remote SOF container.
 *
 * @author magr74
 */
class LocalServiceTracker : public ServiceTracker
{
	public:

		/**
		 * Creates instances of class <code>LocalServiceTracker</code>.
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
		LocalServiceTracker( IRemoteBundleContext::ConstPtr bc, const string &servName,
			ILocalServiceTrackerCustomizer::ConstPtr customizer );

		/**
		 * Destroys the service tracker object.
		 */
		virtual ~LocalServiceTracker();
};

}}}}

#endif
