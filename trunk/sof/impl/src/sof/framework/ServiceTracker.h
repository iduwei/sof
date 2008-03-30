#ifndef SERVICE_TRACKER_H
#define SERVICE_TRACKER_H

#include <string>

#include "IBundleContext.h"
#include "IServiceTrackerCustomizer.h"
#include "IServiceListener.h"
#include "ServiceEvent.h"
#include "../util/logging/Logger.h"
#include "../util/logging/LoggerFactory.h"


using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;

namespace sof { namespace framework {

class ServiceTracker : public IServiceListener
{
	private:
		IBundleContext::ConstPtr bundleCtxt;
		IServiceTrackerCustomizer::ConstPtr serviceTracker;
		string serviceName;
		static Logger& logger;

	public:
		ServiceTracker( IBundleContext::ConstPtr bc, const string &servName, 
			IServiceTrackerCustomizer::ConstPtr customizer );
		~ServiceTracker();
		void startTracking();
		void stopTracking();

		void serviceChanged( const ServiceEvent &serviceEvent );
		
};

}}

#endif