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

/**
 * The <code>FaultyServiceListener</code> is responsible for throwing exceptions in the 
 * <code>addingService</code> and <code>removedService</code> methods in order to test the
 * error robustness of the framework.
 */
class FaultyServiceListener : public IServiceTrackerCustomizer
{					
	public:

		/**
		 * The type of the exception which is thrown in the listener methods.
		 */
		enum ExceptionType { STD, NON_STD };

		/**
		 * Listener method notifying about an added service.
		 */
		virtual bool addingService( const ServiceReference& ref );
		
		/** 
		 * Listener method notifying about a removed service.
		 */
		virtual void removedService( const ServiceReference& ref );

		/**
		 * Setter method for the exception type.
		 */
		void setException( ExceptionType type );

	private:

		/**
		 * The exception type which can be configured.
		 */
		ExceptionType excType;
};

bool FaultyServiceListener::addingService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[FaultyServiceListener#addingService] Called." );
	switch( this->excType )
	{
		case FaultyServiceListener::STD:
			UnitTestLogger::getInstance().log( Logger::DEBUG, "[FaultyServiceListener#addingService] Throw std::exception." );
			throw std::exception();
			break;
		case FaultyServiceListener::NON_STD:
			UnitTestLogger::getInstance().log( Logger::DEBUG, "[FaultyServiceListener#addingService] Throw int." );
			throw -1;
			break;
		default:
			; // do nothing
	}	
}

void FaultyServiceListener::removedService( const ServiceReference& ref )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[FaultyServiceListener#removedService] Called." );		
}

void FaultyServiceListener::setException( ExceptionType type )
{
	this->excType = type;
}

/**
 * The bundle activator of the test bundle which is started for checking the
 * error robustness of the framework.
 * The test bundle starts and tracks one service.
 */
class BundleActivatorServiceListenerNotificationError : public IBundleActivator
{
	private:
		ServiceTracker* tracker;
		IBundleContext* context;
		IServiceRegistration* serviceReg;
		IServiceBImpl serviceB;	

	public:		
		virtual ~BundleActivatorServiceListenerNotificationError();
		virtual void start( IBundleContext::ConstPtr context );
		virtual void stop( IBundleContext::ConstPtr context );	
		static FaultyServiceListener& getServiceListener();
};

FaultyServiceListener& BundleActivatorServiceListenerNotificationError::getServiceListener()
{
	static FaultyServiceListener listener;
	return listener;
}

void BundleActivatorServiceListenerNotificationError::start( IBundleContext::ConstPtr ctxt )
{
	this->context = ctxt;
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationError#start] Called." );
	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationError#start] Register ServiceB..." );	

	Properties props;
	props.put( "instance", "1" );
	this->serviceReg = this->context->registerService( "ServiceB", &( this->serviceB ), props );
	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationError#start] ServiceB registered." );	
	
	this->tracker = new ServiceTracker( context, "ServiceB", &(getServiceListener()) );
	this->tracker->startTracking();

	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationError#start] Left." );
}

BundleActivatorServiceListenerNotificationError::~BundleActivatorServiceListenerNotificationError()
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationError#destructor] Called." );		
}

void BundleActivatorServiceListenerNotificationError::stop( IBundleContext::ConstPtr context )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationError#stop] Called." );		
	this->serviceReg->unregister();
	delete this->serviceReg;

	this->tracker->stopTracking();
	delete this->tracker;
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "BundleActivatorServiceListenerNotificationError", BundleActivatorServiceListenerNotificationError )

/**
 * Tests if the SOF framework catches exceptions of type <code>std::exception</code>
 * which are thrown in the service listener methods.
 * If the test runs without termination you may be certain that the exception is caught. 
 */
TEST( StandardException, ServiceListenerNotificationError  )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationErrorTest] *** StandardException" );
			
	BundleActivatorServiceListenerNotificationError::getServiceListener().setException( FaultyServiceListener::STD );
	BundleConfiguration bundleConf( "bundle1", "BundleActivatorServiceListenerNotificationError" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf );
	
	Launcher<SingleThreaded,NullCreator> launcher;
	launcher.start( bundleConfVec );
}

/**
 * Tests if the SOF framework catches non standard C++ exceptions
 * which are thrown in the service listener methods.
 * If the test runs without termination you may be certain that the exception is caught. 
 */
TEST( NonStandardException, ServiceListenerNotificationError  )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivatorServiceListenerNotificationErrorTest] *** NonStandardException" );
			
	BundleActivatorServiceListenerNotificationError::getServiceListener().setException( FaultyServiceListener::NON_STD );
	BundleConfiguration bundleConf( "bundle1", "BundleActivatorServiceListenerNotificationError" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf );
	
	Launcher<SingleThreaded,NullCreator> launcher;
	launcher.start( bundleConfVec );
}