#include "ServiceTracker.h"
#include "IServiceTrackerCustomizer.h"
#include "IBundleContext.h"

using namespace sof::framework;
using namespace sof::util::logging;

Logger& ServiceTracker::logger = LoggerFactory::getLogger( "Framework" );

ServiceTracker::ServiceTracker( IBundleContext::ConstPtr bc, const string &servName, 
							   IServiceTrackerCustomizer::ConstPtr customizer ) : bundleCtxt( bc ), serviceName( servName ), serviceTracker( customizer )
{
	logger.log( Logger::DEBUG, "[ServiceTracker#ctor] Called, service name: %1", servName );
}

ServiceTracker::~ServiceTracker()
{
	logger.log( Logger::DEBUG, "[ServiceTracker#destructor] Called." );
}

void ServiceTracker::startTracking()
{
	logger.log( Logger::DEBUG, "[ServiceTracker#startTracking] Called." );
	this->bundleCtxt->addServiceListener( this, this->serviceName );
}

void ServiceTracker::stopTracking()
{
	logger.log( Logger::DEBUG, "[ServiceTracker#stopTracking] Called." );
	this->bundleCtxt->removeServiceListener( this );
}

void ServiceTracker::serviceChanged( const ServiceEvent &serviceEvent )
{
	if ( serviceEvent.getType() == ServiceEvent::REGISTER )
	{
		logger.log( Logger::DEBUG, "[ServiceTracker#serviceChanged] Service is registered, service name: %1", serviceEvent.getReference().getServiceName() );
		this->serviceTracker->addingService( serviceEvent.getReference() );
	}
	else if ( serviceEvent.getType() == ServiceEvent::UNREGISTER )
	{
		logger.log( Logger::DEBUG, "[ServiceTracker#serviceChanged] Service is unregistered, service name: %1", serviceEvent.getReference().getServiceName() );		
		this->serviceTracker->removedService( serviceEvent.getReference() );
	}
	else
	{
		logger.log( Logger::DEBUG, "[ServiceTracker#serviceChanged] Unhandled event, service name: %1", serviceEvent.getReference().getServiceName() );				
	}
}