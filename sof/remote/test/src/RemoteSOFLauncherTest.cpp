// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "UnitTestLogger.h"
#include "CustomizedCORBAHelper.h"

#include "sof/framework/remote/corba/CORBAHelper.h"
#include "sof/framework/remote/corba/RemoteSOFLauncher.h"
#include "sof/framework/BundleInfoBase.h"
#include "sof/framework/IRegistry.h"
#include "sof/config/BundleConfiguration.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/util/threading/SingleThreaded.h"

// Standard namespaces
using namespace std;

using namespace sof::framework::remote::corba;

/**
 * Helper class for verifying test results.
 */
class TestHelper
{
	public:

		/**
		 * Checks if the specified service is registered by the given bundle.
		 */
		static int isServiceRegisteredByBundle( IRegistry& reg, const string& bundleName, const string& serviceName, int propsSize );
		
		/**  
		 * Checks if the specified service is used by the given bundle.
		 */
		static int isServiceUsedByBundle( IRegistry& reg, const string& bundleName, const string& serviceName, int propsSize );

		/**
		 * Checks if the specified service listener is registered by the given bundle.
		 */
		static int isServiceListenerRegisteredByBundle( IRegistry& reg, const string& bundleName, const string& serviceName );
		
		/**
		 * Checks if a service is registered by the given bundle.
		 */
		static int isServiceRegisteredByBundle( IRegistry& reg, const string& bundleName );
		
		/**
		 * Checks if a service is used by the given bundle.
		 */
		static int isServiceUsedByBundle( IRegistry& reg, const string& bundleName );
		
		/**
		 * Checks if a service listener is registered by the given bundle.
		 */
		static int isServiceListenerRegisteredByBundle( IRegistry& reg, const string& bundleName );

		/**
		 * Checks if the specified bundle is started.
		 */
		static bool isBundleStarted( IRegistry& reg, const string& bundleName );
};

int TestHelper::isServiceListenerRegisteredByBundle( IRegistry& reg, const string& bundleName, const string& serviceName )
{
	BundleInfoBase* bi = reg.getBundleInfo( bundleName );	
	vector<ServiceListenerInfo*> serviceListenerInfos = bi->getRegisteredListeners();
	vector<ServiceListenerInfo*>::iterator iter;
	int counter = 0;
	for ( iter = serviceListenerInfos.begin(); iter != serviceListenerInfos.end(); ++iter )
	{
		if ( (*iter)->getBundleName() == bundleName &&
			(*iter)->getServiceName() == serviceName )
		{
			counter++;
		}
	}
	return counter;
}

int TestHelper::isServiceRegisteredByBundle( IRegistry& registry, const string& bundleName, const string& serviceName, int propsSize )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getRegisteredServices();
	vector<ServiceInfo*>::iterator iter;
	int foundCounter = 0;
	for ( iter = serviceInfos.begin(); iter != serviceInfos.end(); ++iter )
	{
		if ( (*iter)->getServiceName() == serviceName &&
			(*iter)->getProperties().getSize() == propsSize )
		{
			foundCounter++;
		}
	}
	return foundCounter;
}

int TestHelper::isServiceUsedByBundle( IRegistry& registry, const string& bundleName, const string& serviceName, int propsSize )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getUsedServices();
	vector<ServiceInfo*>::iterator iter;
	int foundCounter = 0;
	for ( iter = serviceInfos.begin(); iter != serviceInfos.end(); ++iter )
	{
		if ( (*iter)->getServiceName() == serviceName &&
			(*iter)->getProperties().getSize() == propsSize )
		{
			foundCounter++;
		}
	}
	return foundCounter;
}

int TestHelper::isServiceListenerRegisteredByBundle( IRegistry& reg, const string& bundleName )
{
	BundleInfoBase* bi = reg.getBundleInfo( bundleName );	
	vector<ServiceListenerInfo*> serviceListenerInfos = bi->getRegisteredListeners();
	return serviceListenerInfos.size();
}

bool TestHelper::isBundleStarted( IRegistry& reg, const string& bundleName )
{
	BundleInfoBase* bi = reg.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return false;
	} 
	else
	{
		return true;
	}
}

int TestHelper::isServiceRegisteredByBundle( IRegistry& registry, const string& bundleName )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getRegisteredServices();
	return serviceInfos.size();
}

int TestHelper::isServiceUsedByBundle( IRegistry& registry, const string& bundleName )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getUsedServices();
	return serviceInfos.size();
}

/** 
 * Tests the registering and tracking of services.
 */
TEST( Services, RemoteSOFLauncherTest )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[RemoteSOFLauncherTest] *** Services Test" );
			
	// Registers two instances of multiplier service
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator1" );

	// Tracks multiplier services
	BundleConfiguration bundleConf2( "bundle2", "BundleActivator2" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	vector<string> args;

	// Simulate program name 
	args.push_back( "program" );
	
	args.push_back( "-ORBNamingAddr" );
	args.push_back( "inet:localhost:5000" );
	CustomizedCORBAHelper corbaHelper( args );
	corbaHelper.start();

	RemoteSOFLauncher<> launcher( corbaHelper, "foo" );
	launcher.start( bundleConfVec );		

	IRegistry& registry = launcher.getRegistry();

	int result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle1", "Multiplier" );
	CHECK( result == 0 );
	
	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "Multiplier" );
	CHECK( result == 1 );
	
	result = TestHelper::isServiceRegisteredByBundle( registry, "bundle1", "Multiplier",1 );
	CHECK( result == 2 );
	
	result = TestHelper::isServiceRegisteredByBundle( registry, "bundle2" );
	CHECK( result == 0 );

	launcher.stop();

	corbaHelper.stop();
}

