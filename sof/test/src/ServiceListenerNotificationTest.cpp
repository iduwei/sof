#include <iostream>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "sof/framework/Launcher.h"
#include "sof/framework/IBundleActivator.h"
#include "sof/framework/IServiceTrackerCustomizer.h"
#include "sof/framework/IServiceRegistration.h"
#include "sof/framework/ServiceTracker.h"
#include "sof/framework/IBundleContext.h"
#include "sof/instantiation/NullCreator.h"
#include "sof/util/threading/SingleThreaded.h"

#include "UnitTestLogger.h"
#include "IServiceBImpl.h"

using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::threading;

class DefaultServiceListener : public IServiceTrackerCustomizer
{
	private:
		int callCounter;

	public:
		virtual bool addingService( const ServiceReference& ref );
		virtual void removedService( const ServiceReference& ref );
		int getCounter();
};

bool DefaultServiceListener::addingService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[DefaultServiceListener#addingService] Called." );
	if ( ref.getServiceName() == "ServiceB" )
	{
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[DefaultServiceListener#addingService] ServiceB found." );	
		Properties props = ref.getServiceProperties();
		if ( props.get( "instance" ) == "1" )
		{
			UnitTestLogger::getInstance().log( Logger::DEBUG, "[DefaultServiceListener#addingService] Instance 1 found." );	
			callCounter++;
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

void DefaultServiceListener::removedService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[DefaultServiceListener#removedService] Called." );		
}

int DefaultServiceListener::getCounter()
{
	return this->callCounter;
}

class BundleActivatorServiceListenerNotification : public IBundleActivator
{
	private:
		ServiceTracker* tracker1;
		ServiceTracker* tracker2;
		IBundleContext* context;
		IServiceRegistration* serviceReg;
		IServiceBImpl serviceB;	

	public:		
		virtual ~BundleActivatorServiceListenerNotification();
		virtual void start( IBundleContext::ConstPtr context );
		virtual void stop( IBundleContext::ConstPtr context );	
		static DefaultServiceListener& getServiceListener1();
		static DefaultServiceListener& getServiceListener2();
};

DefaultServiceListener& BundleActivatorServiceListenerNotification::getServiceListener1()
{
	static DefaultServiceListener listener1;
	return listener1;
}

DefaultServiceListener& BundleActivatorServiceListenerNotification::getServiceListener2()
{
	static DefaultServiceListener listener2;
	return listener2;
}

void BundleActivatorServiceListenerNotification::start( IBundleContext::ConstPtr ctxt )
{
	this->context = ctxt;
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotification#start] Called." );
	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotification#start] Register ServiceB..." );	

	Properties props;
	props.put( "instance", "1" );
	this->serviceReg = this->context->registerService( "ServiceB", &( this->serviceB ), props );
	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotification#start] ServiceB registered." );	
	
	this->tracker1 = new ServiceTracker( context, "ServiceB", &(getServiceListener1()) );
	this->tracker1->startTracking();

	this->tracker2 = new ServiceTracker( context, "ServiceB", &(getServiceListener2()) );
	this->tracker2->startTracking();	

	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotification#start] Left." );
}

BundleActivatorServiceListenerNotification::~BundleActivatorServiceListenerNotification()
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotification#destructor] Called." );		
}

void BundleActivatorServiceListenerNotification::stop( IBundleContext::ConstPtr context )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotification#stop] Called." );		
	this->serviceReg->unregister();
	delete this->serviceReg;

	this->tracker1->stopTracking();
	delete this->tracker1;
	
	this->tracker2->stopTracking();
	delete this->tracker2;	
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "BundleActivatorServiceListenerNotification", BundleActivatorServiceListenerNotification )

/**
 * Tests whether the notification of the service listeners works correctly.
 * - At first the service object is registered.
 * - Afterwards the service listener objects are registered.
 * - Both service listener objects have to be notified only once about the registered
 *		service.
 */
TEST( ServiceListener, Notification  )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ServiceListenerNotificationTest] *** Notification Test" );
			
	BundleConfiguration bundleConf( "bundle1", "BundleActivatorServiceListenerNotification" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf );
	
	Launcher<SingleThreaded,NullCreator> launcher;
	launcher.start( bundleConfVec );
	CHECK( BundleActivatorServiceListenerNotification::getServiceListener1().getCounter() == 1 );
	CHECK( BundleActivatorServiceListenerNotification::getServiceListener2().getCounter() == 1 );
}