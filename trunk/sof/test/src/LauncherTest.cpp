// CppUnitLite Headers
#include <iostream>
#include <vector>
#include <iostream>

#include "TestHarness.h"
#include "Test.h"

#include "sof/config/BundleConfiguration.h"
#include "sof/framework/Launcher.h"
#include "sof/framework/BundleInfo.h"
#include "sof/framework/Registry.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"

#include "TestBundleActivator.h"

#include "UnitTestLogger.h"

using namespace std;

using namespace sof::config;
using namespace sof::framework;

class TestHelper
{
	public:
		static int isServiceRegisteredByBundle( Registry& reg, const string& bundleName, const string& serviceName, int propsSize );
		static int isServiceUsedByBundle( Registry& reg, const string& bundleName, const string& serviceName, int propsSize );
		static int isServiceListenerRegisteredByBundle( Registry& reg, const string& bundleName, const string& serviceName );
		static int isServiceRegisteredByBundle( Registry& reg, const string& bundleName );
		static int isServiceUsedByBundle( Registry& reg, const string& bundleName );
		static int isServiceListenerRegisteredByBundle( Registry& reg, const string& bundleName );
		static bool isBundleStarted( Registry& reg, const string& bundleName );
};

int TestHelper::isServiceListenerRegisteredByBundle( Registry& reg, const string& bundleName, const string& serviceName )
{
	BundleInfo* bi = reg.getBundleInfo( bundleName );	
	vector<ServiceListenerInfo*> serviceListenerInfos = bi->getRegisteredListeners();
	vector<ServiceListenerInfo*>::iterator iter;
	int counter = 0;
	for ( iter = serviceListenerInfos.begin(); iter != serviceListenerInfos.end(); iter++ )
	{
		if ( (*iter)->getBundleName() == bundleName &&
			(*iter)->getServiceName() == serviceName )
		{
			counter++;
		}
	}
	return counter;
}

int TestHelper::isServiceRegisteredByBundle( Registry& registry, const string& bundleName, const string& serviceName, int propsSize )
{
	BundleInfo* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getRegisteredServices();
	vector<ServiceInfo*>::iterator iter;
	int foundCounter = 0;
	for ( iter = serviceInfos.begin(); iter != serviceInfos.end(); iter++ )
	{
		if ( (*iter)->getServiceName() == serviceName &&
			(*iter)->getProperties().getSize() == propsSize )
		{
			foundCounter++;
		}
	}
	return foundCounter;
}

int TestHelper::isServiceUsedByBundle( Registry& registry, const string& bundleName, const string& serviceName, int propsSize )
{
	BundleInfo* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getUsedServices();
	vector<ServiceInfo*>::iterator iter;
	int foundCounter = 0;
	for ( iter = serviceInfos.begin(); iter != serviceInfos.end(); iter++ )
	{
		if ( (*iter)->getServiceName() == serviceName &&
			(*iter)->getProperties().getSize() == propsSize )
		{
			foundCounter++;
		}
	}
	return foundCounter;
}

int TestHelper::isServiceListenerRegisteredByBundle( Registry& reg, const string& bundleName )
{
	BundleInfo* bi = reg.getBundleInfo( bundleName );	
	vector<ServiceListenerInfo*> serviceListenerInfos = bi->getRegisteredListeners();
	return serviceListenerInfos.size();
}

bool TestHelper::isBundleStarted( Registry& reg, const string& bundleName )
{
	BundleInfo* bi = reg.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return false;
	} 
	else
	{
		return true;
	}
}

int TestHelper::isServiceRegisteredByBundle( Registry& registry, const string& bundleName )
{
	BundleInfo* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getRegisteredServices();
	return serviceInfos.size();
}

int TestHelper::isServiceUsedByBundle( Registry& registry, const string& bundleName )
{
	BundleInfo* bi = registry.getBundleInfo( bundleName );	
	vector<ServiceInfo*> serviceInfos = bi->getUsedServices();
	return serviceInfos.size();
}

/**
 * Tests whether it is possible to load bundles locally and from DLL.
 */
TEST( Launcher, Load )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-Load Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher launcher;
	launcher.start( bundleConfVec );	
}

/**
 * Tests whether service listeners can be registered.
 */
TEST( Launcher, RegisterServiceListeners )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-RegisterServiceListeners Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher launcher;
	launcher.start( bundleConfVec );

	Registry& registry = launcher.getRegistry();

	int result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle1", "ServiceB" );
	CHECK( result == 1 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "ServiceA" );
	CHECK( result == 0 );
}

/**
 * Tests whether services can be used.
 */
TEST( Launcher, UsedServices )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-UsedServices Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher launcher;
	launcher.start( bundleConfVec );

	Registry& registry = launcher.getRegistry();

	int result = TestHelper::isServiceUsedByBundle( registry, "bundle1", "ServiceB", 1 );
	CHECK( result == 1 );
}

/**
 * Tests whether services can be registered.
 */
TEST( Launcher, RegisterServices )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-RegisterServices Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher launcher;
	launcher.start( bundleConfVec );

	Registry& registry = launcher.getRegistry();
	
	int result = TestHelper::isServiceRegisteredByBundle( registry, "bundle1", "ServiceA", 0 );
	CHECK( result == 1 );	

	result = TestHelper::isServiceRegisteredByBundle( registry, "bundle2", "ServiceB", 1 );
	CHECK( result == 1 );
}

/**
 * Tests whether services can be deregistered.
 */
TEST( Launcher, DeregisterService )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-DeregisterService Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher launcher;
	launcher.start( bundleConfVec );

	TestBundleActivator::unregisterServiceB();
	
	Registry& registry = launcher.getRegistry();
	int result = TestHelper::isServiceRegisteredByBundle( registry, "bundle2", "ServiceB", 1 );
	CHECK( result == 0 );

	result = TestHelper::isServiceUsedByBundle( registry, "bundle1", "ServiceB", 1 );
	CHECK( result == 0 );


	result = TestHelper::isServiceRegisteredByBundle( registry, "bundle1", "ServiceA", 0 );
	CHECK( result == 1 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle1", "ServiceB" );
	CHECK( result == 1 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "ServiceA" );
	CHECK( result == 0 );
}

/**
 * Tests whether listener can be deregistered.
 */
TEST( Launcher, DeregisterListener )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-DeregisterListener Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher launcher;
	launcher.start( bundleConfVec );

	Registry& registry = launcher.getRegistry();

	int result = TestHelper::isServiceRegisteredByBundle( registry, "bundle2", "ServiceB", 1 );
	CHECK( result == 1 );

	TestBundleActivator::unregisterServiceB();
		
	result = TestHelper::isServiceRegisteredByBundle( registry, "bundle2", "ServiceB", 1 );
	CHECK( result == 0 );

	result = TestHelper::isServiceUsedByBundle( registry, "bundle1", "ServiceB", 1 );
	CHECK( result == 0 );


	result = TestHelper::isServiceRegisteredByBundle( registry, "bundle1", "ServiceA", 0 );
	CHECK( result == 1 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle1", "ServiceB" );
	CHECK( result == 1 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "ServiceA" );
	CHECK( result == 0 );
}

/**
 * Tests whether listener can be deregistered.
 */
TEST( Launcher, StopBundle )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-StopBundle Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher launcher;
	launcher.start( bundleConfVec );

	Registry& registry = launcher.getRegistry();

	launcher.stopBundle( "bundle2" );

	bool result = TestHelper::isBundleStarted( registry, "bundle2" );
	CHECK( result == false );

	result = TestHelper::isServiceUsedByBundle( registry, "bundle1", "ServiceB", 1 );
	CHECK( result == 0 );		
}