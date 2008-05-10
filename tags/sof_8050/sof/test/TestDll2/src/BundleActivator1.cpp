#include "BundleActivator1.h"

#include <iostream>

#include "sof/classloading/Object.h"

#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/framework/Properties.h"
#include "sof/framework/IService.h"

#include "IServiceAImpl.h"

using namespace std;

using namespace sof::classloading;
using namespace sof::framework;

void BundleActivator1::start( IBundleContext::ConstPtr context )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator1#start] Called." );
	this->tracker = new ServiceTracker( context, "ServiceB", this );
	this->tracker->startTracking();

	Properties props;
	context->registerService( "ServiceA", new IServiceAImpl(), props );
}

BundleActivator1::~BundleActivator1()
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator1#destructor] Called." );
}

void BundleActivator1::stop( IBundleContext::ConstPtr context )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator1#stop] Called." );
}

void BundleActivator1::addingService( const ServiceReference& ref )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator1#addingService] Called, service name: %1", ref.getServiceName() );
}

void BundleActivator1::removedService( const ServiceReference& ref )
{
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[BundleActivator1#removedService] Called, service name: %1", ref.getServiceName() );
}

REGISTER_CLASS("BundleActivator1",IBundleActivator,BundleActivator1)