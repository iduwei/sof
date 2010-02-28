
#include <iostream>
#include <vector>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"
 
#ifdef WIN32
#include "sof/framework/Launcher.h"
#include "sof/framework/BundleInfoBase.h"
#include "sof/framework/IRegistry.h"
#include "sof/config/BundleConfiguration.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/instantiation/win/WinDllCreator.h"
#include "sof/util/threading/SingleThreaded.h"

#include "../TestBundleActivator.h"
#include "../UnitTestLogger.h"

using namespace std;

using namespace sof::config;
using namespace sof::framework;
using namespace sof::instantiation::win;

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
	
	Launcher<SingleThreaded,WinDllCreator> launcher;
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
	
	Launcher<SingleThreaded,WinDllCreator> launcher;
	launcher.start( bundleConfVec );

	IRegistry& registry = launcher.getRegistry();

	int result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle1", "ServiceB" );
	CHECK( result == 1 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "ServiceA" );
	CHECK( result == 1 );
}

/**
 * Tests whether services can be used.
 */
TEST( Launcher, UsedServices )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-UsedServices Test" );
			
	// Registers service listener for 'ServiceB'
	// Registers 'ServiceA' with properties 'instance=1'
	// Registers 'ServiceA' with properties 'instance=2'
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );

	// Registers service listener for 'ServiceA'
	// Registers 'ServiceB' with properties 'instance=1'
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );

	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher<SingleThreaded,WinDllCreator>  launcher;
	launcher.start( bundleConfVec );

	IRegistry& registry = launcher.getRegistry();

	int result = TestHelper::isServiceUsedByBundle( registry, "bundle1", "ServiceB", 1 );
	CHECK( result == 1 );

	// The bundle 'bundle1' registers two services of name 'ServiceA' but
	// 'bundle2' only uses one of them.
	result = TestHelper::isServiceUsedByBundle( registry, "bundle2", "ServiceA", 1 );
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
	
	Launcher<SingleThreaded,WinDllCreator>  launcher;
	launcher.start( bundleConfVec );

	IRegistry& registry = launcher.getRegistry();
	
	int result = TestHelper::isServiceRegisteredByBundle( registry, "bundle1", "ServiceA", 1 );
	CHECK( result == 2 );	

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
	
	Launcher<SingleThreaded,WinDllCreator>  launcher;
	launcher.start( bundleConfVec );

	TestBundleActivator::unregisterServiceB();
	
	IRegistry& registry = launcher.getRegistry();
	int result = TestHelper::isServiceRegisteredByBundle( registry, "bundle2", "ServiceB", 1 );
	CHECK( result == 0 );

	result = TestHelper::isServiceUsedByBundle( registry, "bundle1", "ServiceB", 1 );
	CHECK( result == 0 );


	result = TestHelper::isServiceRegisteredByBundle( registry, "bundle1", "ServiceA", 1 );
	CHECK( result == 2 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle1", "ServiceB" );
	CHECK( result == 1 );

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "ServiceA" );
	CHECK( result == 1 );
}

/**
 * Tests whether service listener can be deregistered.
 */
TEST( Launcher, DeregisterListener )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-DeregisterListener Test" );
			
	// Registers service listener for 'ServiceB'
	// Registers 'ServiceA' with properties 'instance=1'
	// Registers 'ServiceA' with properties 'instance=2'
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );

	// Registers service listener for 'ServiceA'
	// Registers 'ServiceB' with properties 'instance=1'	
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );

	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher<SingleThreaded,WinDllCreator>  launcher;
	launcher.start( bundleConfVec );

	IRegistry& registry = launcher.getRegistry();

	int result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "ServiceA" );
	CHECK( result == 1 );

	// Stops the service tracker 
	TestBundleActivator::stopServiceListener();

	result = TestHelper::isServiceListenerRegisteredByBundle( registry, "bundle2", "ServiceA" );
	CHECK( result == 0 );
}

/**
 * Tests whether a bundle can be stopped.
 */
TEST( Launcher, StopBundle )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-StopBundle Test" );
		
	// Registers service listener for 'ServiceB'
	// Registers 'ServiceA' with properties 'instance=1'
	// Registers 'ServiceA' with properties 'instance=2'
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );

	// Registers service listener for 'ServiceA'
	// Registers 'ServiceB' with properties 'instance=1'	
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );

	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher<SingleThreaded,WinDllCreator>  launcher;
	launcher.start( bundleConfVec );

	IRegistry& registry = launcher.getRegistry();

	launcher.stopBundle( "bundle2" );

	bool result = TestHelper::isBundleStarted( registry, "bundle2" );
	CHECK( result == false );

	result = TestHelper::isServiceUsedByBundle( registry, "bundle1", "ServiceB", 1 );
	CHECK( result == 0 );		
}

/**
 * Tests whether all bundles can be stopped.
 */
TEST( Launcher, StopAllBundles )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[LauncherTest] *** Launcher-StopAllBundles Test" );
			
	BundleConfiguration bundleConf1( "bundle1", "BundleActivator2", ".", "sof_TestDll2.dll" );
	BundleConfiguration bundleConf2( "bundle2", "TestBundleActivator" );
	vector<BundleConfiguration> bundleConfVec;
	bundleConfVec.push_back( bundleConf1 );
	bundleConfVec.push_back( bundleConf2 );
	
	Launcher<SingleThreaded,WinDllCreator>  launcher;
	launcher.start( bundleConfVec );

	IRegistry& registry = launcher.getRegistry();

	launcher.stop();

	bool result = TestHelper::isBundleStarted( registry, "bundle2" );
	CHECK( result == false );

	result = TestHelper::isBundleStarted( registry, "bundle1" );
	CHECK( result == false );
}

#endif