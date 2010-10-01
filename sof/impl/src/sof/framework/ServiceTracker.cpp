#include "ServiceTracker.h"
#include "IServiceTrackerCustomizer.h"
#include "IBundleContext.h"

using namespace sof::framework;
using namespace sof::util::logging;

Logger& ServiceTracker::logger = LoggerFactory::getLogger( "Framework" );

ServiceTracker::ServiceTracker( IBundleContext::ConstPtr bc, const string &servName, 
							   IServiceTrackerCustomizer::ConstPtr customizer ) : bundleCtxt( bc ), serviceName( servName ), serviceTracker( customizer ), isTrackingActive( false )
{
	logger.log( Logger::LOG_DEBUG, "[ServiceTracker#ctor] Called, service name: %1", servName );
}

ServiceTracker::~ServiceTracker()
{
	logger.log( Logger::LOG_DEBUG, "[ServiceTracker#destructor] Called." );
	// Bugfix for ID 3000086: ServiceTracker destructor should call stopTracking
	if ( this->isTrackingActive )
	{
		logger.log( Logger::LOG_DEBUG, "[ServiceTracker#destructor] Service tracking is active, stop tracking." );
		this->stopTracking();
	}
}

void ServiceTracker::startTracking()
{
	logger.log( Logger::LOG_DEBUG, "[ServiceTracker#startTracking] Called." );
	this->bundleCtxt->addServiceListener( this, this->serviceName );
	this->isTrackingActive = true;
}

void ServiceTracker::stopTracking()
{
	logger.log( Logger::LOG_DEBUG, "[ServiceTracker#stopTracking] Called." );
	this->bundleCtxt->removeServiceListener( this );
	this->isTrackingActive = false;
}

bool ServiceTracker::serviceChanged( const ServiceEvent &serviceEvent )
{
	logger.log( Logger::LOG_DEBUG, "[ServiceTracker#serviceChanged] Called, service event: %1", serviceEvent.toString() );
	bool retVal = false;
	try
	{
		if ( serviceEvent.getType() == ServiceEvent::REGISTER )
		{
			logger.log( Logger::LOG_DEBUG, "[ServiceTracker#serviceChanged] Service is registered, service name: %1", serviceEvent.getReference().getServiceName() );
			retVal = this->serviceTracker->addingService( serviceEvent.getReference() );		
		}
		else if ( serviceEvent.getType() == ServiceEvent::UNREGISTER )
		{
			logger.log( Logger::LOG_DEBUG, "[ServiceTracker#serviceChanged] Service is unregistered, service name: %1", serviceEvent.getReference().getServiceName() );		
			this->serviceTracker->removedService( serviceEvent.getReference() );
			retVal = true;
		}
		else
		{
			logger.log( Logger::LOG_DEBUG, "[ServiceTracker#serviceChanged] Unhandled event, service name: %1", serviceEvent.getReference().getServiceName() );				
			retVal = false;
		}
	}
	catch( std::exception exc )
	{
		logger.log( Logger::LOG_ERROR, "[ServiceTracker#serviceChanged] Error occurred during adding/removing service: %1", string( exc.what() ) );			
	}
	// To play it safe, catch all exceptions which are not standard c++ exceptions.
	catch( ... )
	{
		logger.log( Logger::LOG_ERROR, "[ServiceTracker#serviceChanged] Error occurred during adding/removing service." );		
	}
	return retVal;
}
