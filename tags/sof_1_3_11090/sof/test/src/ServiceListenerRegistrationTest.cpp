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
#include "TestHelper.h"

using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::threading;

class BundleActivatorServiceListenerRegistration : public IBundleActivator, public IServiceTrackerCustomizer
{
	private:
		ServiceTracker* tracker3;

	public:		
		BundleActivatorServiceListenerRegistration();
		virtual ~BundleActivatorServiceListenerRegistration();
		virtual void start( IBundleContext::ConstPtr context );
		virtual void stop( IBundleContext::ConstPtr context );	
		virtual bool addingService( const ServiceReference& ref );
		virtual void removedService( const ServiceReference& ref );
};

BundleActivatorServiceListenerRegistration::BundleActivatorServiceListenerRegistration() : tracker3(0) {}

bool BundleActivatorServiceListenerRegistration::addingService( const ServiceReference& ref ) { return true; }

void BundleActivatorServiceListenerRegistration::removedService( const ServiceReference& ref ){}

void BundleActivatorServiceListenerRegistration::start( IBundleContext::ConstPtr ctxt )
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[BundleActivatorServiceListenerRegistration#start] Called." );
	
	// Service tracking of tracker1 is stopped via destructor
	ServiceTracker tracker1( ctxt, "ServiceB", this );
	tracker1.startTracking();	
	
	ServiceTracker tracker2( ctxt, "ServiceA", this );
	tracker2.startTracking();
	// stop tracking explicitly
	tracker2.stopTracking();

	// tracker3 does not stop tracking, because neither the destructor nor 'stopTracking' is called.
	ServiceTracker* tracker3 = new ServiceTracker( ctxt, "ServiceC", this );
	tracker3->startTracking();

	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[BundleActivatorServiceListenerRegistration#start] Left." );
}

BundleActivatorServiceListenerRegistration::~BundleActivatorServiceListenerRegistration()
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[BundleActivatorServiceListenerRegistration#destructor] Called." );		
}

void BundleActivatorServiceListenerRegistration::stop( IBundleContext::ConstPtr context )
{
	this->tracker3->stopTracking();
	delete this->tracker3;
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[BundleActivatorServiceListenerRegistration#stop] Called." );		
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "BundleActivatorServiceListenerRegistration", BundleActivatorServiceListenerRegistration )

/**
 * Tests whether the registration and deregistration of the service listeners works correctly.
 */
TEST( ServiceListener, RegistrationDeregistration  )
{
	UnitTestLogger::getInstance().log( Logger::LOG_DEBUG, "[ServiceListenerRegistrationTest] *** Registration Test" );
			
	BundleConfiguration bundleConf( "bundle1", "BundleActivatorServiceListenerRegistration" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf );
	
	Launcher<SingleThreaded,NullCreator> launcher;
	launcher.start( bundleConfVec );
	int result = TestHelper::isServiceListenerRegisteredByBundle( launcher.getRegistry(), "bundle1", "ServiceB" );
	CHECK( result == 0 );
	result = TestHelper::isServiceListenerRegisteredByBundle( launcher.getRegistry(), "bundle1", "ServiceA" );
	CHECK( result == 0 );
	result = TestHelper::isServiceListenerRegisteredByBundle( launcher.getRegistry(), "bundle1", "ServiceC" );
	CHECK( result == 1 );
}