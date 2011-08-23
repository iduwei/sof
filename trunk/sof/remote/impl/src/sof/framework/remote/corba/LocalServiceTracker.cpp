#include "LocalServiceTracker.h"

using namespace sof::framework;
using namespace sof::framework::remote::corba;
using namespace sof::util::logging;

LocalServiceTracker::LocalServiceTracker( IRemoteBundleContext::ConstPtr bc, const string &servName,
							   ILocalServiceTrackerCustomizer::ConstPtr customizer ) : ServiceTracker( bc, servName, customizer )
{
	logger.log( Logger::LOG_DEBUG, "[LocalServiceTracker#ctor] Called, service name: %1", servName );
}

LocalServiceTracker::~LocalServiceTracker()
{
	logger.log( Logger::LOG_DEBUG, "[LocalServiceTracker#destructor] Called." );
}

