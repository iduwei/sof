#include "BundleActivator2.h"

#include <iostream>

#include "sof/instantiation/ObjectCreator.h"
#include "sof/instantiation/win/WinDllCreator.h"

#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/framework/Properties.h"
#include "sof/framework/IService.h"

#include "IServiceAImpl.h"

using namespace std;

using namespace sof::instantiation;
using namespace sof::instantiation::win;
using namespace sof::framework;


BundleActivator2::BundleActivator2()
{
}

void BundleActivator2::start( IBundleContext::ConstPtr context )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#start] Called." );
	this->tracker = new ServiceTracker( context, "ServiceB", this );
	this->tracker->startTracking();

	this->service1 = new IServiceAImpl();
	
	Properties props1;
	props1.put( "instance", "1" );
	this->serviceReg1 = context->registerService( "ServiceA", this->service1, props1 );

	this->service2 = new IServiceAImpl();

	Properties props2;
	props2.put( "instance", "2" );
	this->serviceReg2 = context->registerService( "ServiceA", this->service2, props2 );
}

BundleActivator2::~BundleActivator2()
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#destructor] Called." );
}

void BundleActivator2::stop( IBundleContext::ConstPtr context )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#stop] Called." );
	this->tracker->stopTracking();
	delete this->tracker;

	this->serviceReg1->unregister();
	this->serviceReg2->unregister();
	delete this->serviceReg1;
	delete this->serviceReg2;
}


bool BundleActivator2::addingService( const ServiceReference& ref )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#addingService] Called, service name: %1", ref.getServiceName() );
	if ( ref.getServiceName() == "ServiceB" )
	{
		LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#addingService] ServiceB found." );
		Properties props = ref.getServiceProperties();
		if ( props.get( "instance" ) == "1" )
		{
			LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#addingService] Instance 1 found." );
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void BundleActivator2::removedService( const ServiceReference& ref )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#removedService] Called, service name: %1", ref.getServiceName() );
}

REGISTER_BUNDLE_ACTIVATOR_CLASS("BundleActivator2",BundleActivator2)
