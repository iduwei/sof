#include "BundleActivator2.h"

#include <iostream>

#include "sof/instantiation/ObjectCreator.h"

#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/framework/Properties.h"
#include "sof/framework/IService.h"

#include "IServiceAImpl.h"

using namespace std;

using namespace sof::instantiation;
using namespace sof::framework;

void BundleActivator2::start( IBundleContext::ConstPtr context )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#start] Called." );
	this->tracker = new ServiceTracker( context, "ServiceB", this );
	this->tracker->startTracking();

	Properties props;
	context->registerService( "ServiceA", new IServiceAImpl(), props );
}

BundleActivator2::~BundleActivator2()
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#destructor] Called." );
}

void BundleActivator2::stop( IBundleContext::ConstPtr context )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#stop] Called." );
}

void BundleActivator2::addingService( const ServiceReference& ref )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#addingService] Called, service name: %1", ref.getServiceName() );
}

void BundleActivator2::removedService( const ServiceReference& ref )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator2#removedService] Called, service name: %1", ref.getServiceName() );
}

REGISTER_CLASS("BundleActivator2",IBundleActivator,BundleActivator2)