#include "RemoteServiceTracker.h"

using namespace sof::framework::remote::corba;
using namespace sof::framework;
using namespace sof::util::logging;

Logger& RemoteServiceTracker::logger = LoggerFactory::getLogger( "Framework" );

RemoteServiceTracker::RemoteServiceTracker( IRemoteBundleContext::ConstPtr bc, const string &servName, 
							   IRemoteServiceTrackerCustomizer::ConstPtr customizer ) : bundleCtxt( bc ), serviceName( servName ), serviceTracker( customizer )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#ctor] Called, service name: %1", servName );
}

RemoteServiceTracker::~RemoteServiceTracker()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#destructor] Called." );
}

void RemoteServiceTracker::startTracking()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#startTracking] Called." );
	this->bundleCtxt->addRemoteServiceListener( this, this->serviceName );
}

void RemoteServiceTracker::stopTracking()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#stopTracking] Called." );
	this->bundleCtxt->removeRemoteServiceListener( this );
}

CORBA::Boolean RemoteServiceTracker::serviceChanged( const CORBAServiceEvent &remoteServiceEvent )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#serviceChanged] Called." );
	ServiceEvent serviceEvent = this->bundleCtxt->getCORBAHelper().convertEvent( remoteServiceEvent );
	bool flag = false;

	ServiceReference* tempRef = const_cast<ServiceReference*>( &serviceEvent.getReference() );
	RemoteServiceReference* remoteServiceReference = dynamic_cast<RemoteServiceReference*>( tempRef );			

	if ( serviceEvent.getType() == ServiceEvent::REGISTER )
	{
		logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#serviceChanged] Service is registered, service name: %1", serviceEvent.getReference().getServiceName() );

		// Creating the remote service info dynamically for storing in vector
		RemoteServiceInfo* info = new RemoteServiceInfo( remoteServiceReference->getServiceName(), 
			CORBAService::_duplicate( remoteServiceReference->getRemoteService() ), 
			remoteServiceReference->getRemoteServiceID(), 
			remoteServiceReference->getServiceProperties() );	

		flag = this->serviceTracker->addingService( (*remoteServiceReference) );
		if ( flag )
		{
			// Bugfix: [Remote SOF] Services 'in use' are not available - ID: 2818461
			// Note: only store a service as used service if return flag of 'addingService' call is true
			logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#serviceChanged] Service is used, cache used service." );
			this->bundleCtxt->addUsedService( this->bundleCtxt->getBundleName(), (*info) );
		}
		else
		{
			logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#serviceChanged] Service is NOT used." );
		}
	}
	else if ( serviceEvent.getType() == ServiceEvent::UNREGISTER )
	{
		logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#serviceChanged] Service is unregistered, service name: %1", serviceEvent.getReference().getServiceName() );		

		// creating the remote service info on stack 
		RemoteServiceInfo info( remoteServiceReference->getServiceName(), 
			CORBAService::_duplicate( remoteServiceReference->getRemoteService() ), 
			remoteServiceReference->getRemoteServiceID(), 
			remoteServiceReference->getServiceProperties() );
		
		// Bugfix: [Remote SOF] Services 'in use' are not available - ID: 2818461
		this->serviceTracker->removedService( (*remoteServiceReference) );
		this->bundleCtxt->removeUsedService( this->bundleCtxt->getBundleName(), info );
		flag = true;
	}
	else
	{
		logger.log( Logger::LOG_DEBUG, "[RemoteServiceTracker#serviceChanged] Unhandled event, service name: %1", serviceEvent.getReference().getServiceName() );						
		flag = false;
	}
	delete ( &(serviceEvent.getReference()) );
	return flag;
}
