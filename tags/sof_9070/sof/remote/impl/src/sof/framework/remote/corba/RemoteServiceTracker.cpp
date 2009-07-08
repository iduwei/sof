#include "RemoteServiceTracker.h"

using namespace sof::framework::remote::corba;
using namespace sof::framework;
using namespace sof::util::logging;

Logger& RemoteServiceTracker::logger = LoggerFactory::getLogger( "Framework" );

RemoteServiceTracker::RemoteServiceTracker( IRemoteBundleContext::ConstPtr bc, const string &servName, 
							   IRemoteServiceTrackerCustomizer::ConstPtr customizer ) : bundleCtxt( bc ), serviceName( servName ), serviceTracker( customizer )
{
	logger.log( Logger::DEBUG, "[RemoteServiceTracker#ctor] Called, service name: %1", servName );
}

RemoteServiceTracker::~RemoteServiceTracker()
{
	logger.log( Logger::DEBUG, "[RemoteServiceTracker#destructor] Called." );
}

void RemoteServiceTracker::startTracking()
{
	logger.log( Logger::DEBUG, "[RemoteServiceTracker#startTracking] Called." );
	this->bundleCtxt->addRemoteServiceListener( this, this->serviceName );
}

void RemoteServiceTracker::stopTracking()
{
	logger.log( Logger::DEBUG, "[RemoteServiceTracker#stopTracking] Called." );
	this->bundleCtxt->removeRemoteServiceListener( this );
}

CORBA::Boolean RemoteServiceTracker::serviceChanged( const CORBAServiceEvent &remoteServiceEvent )
{
	logger.log( Logger::DEBUG, "[RemoteServiceTracker#serviceChanged] Called." );
	ServiceEvent serviceEvent = this->bundleCtxt->getCORBAHelper().convertEvent( remoteServiceEvent );
	bool flag = false;

	ServiceReference* tempRef = const_cast<ServiceReference*>( &serviceEvent.getReference() );
	RemoteServiceReference* remoteServiceReference = dynamic_cast<RemoteServiceReference*>( tempRef );
		
	if ( serviceEvent.getType() == ServiceEvent::REGISTER )
	{
		logger.log( Logger::DEBUG, "[RemoteServiceTracker#serviceChanged] Service is registered, service name: %1", serviceEvent.getReference().getServiceName() );
		flag = this->serviceTracker->addingService( (*remoteServiceReference) );
	}
	else if ( serviceEvent.getType() == ServiceEvent::UNREGISTER )
	{
		logger.log( Logger::DEBUG, "[RemoteServiceTracker#serviceChanged] Service is unregistered, service name: %1", serviceEvent.getReference().getServiceName() );		
		this->serviceTracker->removedService( (*remoteServiceReference) );
		flag = true;
	}
	else
	{
		logger.log( Logger::DEBUG, "[RemoteServiceTracker#serviceChanged] Unhandled event, service name: %1", serviceEvent.getReference().getServiceName() );						
		flag = false;
	}
	delete ( &(serviceEvent.getReference()) );
	return flag;
}
