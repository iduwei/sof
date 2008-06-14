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

class BundleActivatorServiceListenerNotification : public IBundleActivator, public IServiceTrackerCustomizer
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
		virtual bool addingService( const ServiceReference& ref );
		virtual void removedService( const ServiceReference& ref );

		static int callCounter;
};

int BundleActivatorServiceListenerNotification::callCounter = 0;

void BundleActivatorServiceListenerNotification::start( IBundleContext::ConstPtr ctxt )
{
	this->context = ctxt;
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] Called." );
	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] Register ServiceB..." );	

	Properties props;
	props.put( "instance", "1" );
	this->serviceReg = this->context->registerService( "ServiceB", &( this->serviceB ), props );
	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] ServiceB registered." );	
	
	this->tracker1 = new ServiceTracker( context, "ServiceB", this );
	this->tracker1->startTracking();

	this->tracker2 = new ServiceTracker( context, "ServiceB", this );
	this->tracker2->startTracking();	

	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] Left." );
}

BundleActivatorServiceListenerNotification::~BundleActivatorServiceListenerNotification()
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#destructor] Called." );		
}

void BundleActivatorServiceListenerNotification::stop( IBundleContext::ConstPtr context )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#stop] Called." );		
	this->serviceReg->unregister();
	delete this->serviceReg;

	this->tracker1->stopTracking();
	delete this->tracker1;
	
	this->tracker2->stopTracking();
	delete this->tracker2;	
}

bool BundleActivatorServiceListenerNotification::addingService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#addingService] Called." );
	if ( ref.getServiceName() == "ServiceB" )
	{
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#addingService] ServiceB found." );	
		Properties props = ref.getServiceProperties();
		if ( props.get( "instance" ) == "1" )
		{
			UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#addingService] Instance 1 found." );	
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

void BundleActivatorServiceListenerNotification::removedService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#removedService] Called." );		
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "BundleActivatorServiceListenerNotification", BundleActivatorServiceListenerNotification )

/**
 * Tests whether it is possible to load bundles locally and from DLL.
 */
TEST( ServiceListener, Notification  )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** ServiceListener-Notification Test" );
			
	BundleConfiguration bundleConf( "bundle1", "BundleActivatorServiceListenerNotification" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf );
	
	Launcher<SingleThreaded,NullCreator> launcher;
	launcher.start( bundleConfVec );
	CHECK( BundleActivatorServiceListenerNotification::callCounter == 2 );
}