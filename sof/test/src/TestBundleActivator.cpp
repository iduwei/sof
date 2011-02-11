#include "TestBundleActivator.h"

#include <iostream>

#include "sof/framework/Properties.h"
#include "sof/instantiation/ObjectCreator.h"

#include "UnitTestLogger.h"

using namespace std;
using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::logging;

IBundleContext* TestBundleActivator::context = 0;
IServiceRegistration* TestBundleActivator::serviceReg = 0;
ServiceTracker* TestBundleActivator::tracker = 0;

void TestBundleActivator::start( IBundleContext::ConstPtr ctxt )
{
	context = ctxt;
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#start] Called." );
	
	tracker = new ServiceTracker( context, "ServiceA", this );
	tracker->startTracking();

	Properties props;
	props.put( "instance", "1" );

	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#start] Register ServiceB..." );	
	serviceReg = context->registerService( "ServiceB", &( this->serviceB ), props );
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#start] ServiceB registered." );	
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#start] Left." );
}

TestBundleActivator::~TestBundleActivator()
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#destructor] Called." );	
}

void TestBundleActivator::stop( IBundleContext::ConstPtr context )
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#stop] Called." );		
	serviceReg->unregister();
	delete serviceReg;

	tracker->stopTracking();
	delete tracker;
}

void TestBundleActivator::unregisterServiceB()
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#unregisterServiceB] Called." );		
	serviceReg->unregister();
	delete serviceReg;
}

void TestBundleActivator::stopServiceListener()
{
	tracker->stopTracking();
}

bool TestBundleActivator::addingService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#addingService] Called." );
	if ( ref.getServiceName() == "ServiceA" )
	{
		UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#addingService] ServiceA found." );	
		Properties props = ref.getServiceProperties();
		if ( props.get( "instance" ) == "1" )
		{
			UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#addingService] Instance 1 found." );	
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

void TestBundleActivator::removedService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[TestBundleActivator#removedService] Called." );		
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "TestBundleActivator", TestBundleActivator )