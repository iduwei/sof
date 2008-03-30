// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "sof/classloading/ObjectLoader.h"

#include "BaseTestClass.h"
#include "ITest.h"
#include "ITestImpl.h"
#include "TestClass.h"
#include "UnitTestLogger.h"

// Standard namespaces
using namespace std;

using namespace sof::classloading;

/**
 * Tests whether loading of a class
 * and casting to the base class 
 * (here: <code>BaseClass</code>) works.
 */
TEST( ObjectLoader, Loading )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-Loading Test" );
		
	// only local search
	ObjectLoader<ITest> OL;

	try
	{
		ITest* obj = OL.loadObject( "ITestImpl" );	
		CHECK( 13 == obj->getValue() );
	}
	catch( ObjectLoadingException &exc )
	{
		string msg( exc.what() );
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] Exception occured: %1", msg );	
		FAIL( "Should not happen, class must be loadable" );
	}	
}

/**
 * Tests whether loading of a class and
 * casting to the loaded class 
 * (here: <code>TestClass</code>) works.
 */
TEST( ObjectLoader, LoadingAndCast )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-LoadingAndCast Test" );
	
	// only local search
	ObjectLoader<ITest> OL;
	
	try
	{
		ITestImpl* obj = static_cast<ITestImpl*> ( OL.loadObject( "ITestImpl" ) );
		CHECK( 13 == obj->getValue() );
	}
	catch( ObjectLoadingException &exc )
	{
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] Exception occured: %1", string( exc.what() ) );	
		FAIL( "Should not happen, class must be loadable" );
	}	
}

/**
 * Tests whether loading a class which
 * is not available (not registered at class loader)
 * leads to an exception.
 */
TEST( ObjectLoader, NotAvailableClass )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-NotAvailableClass Test" );	
	
	// only local search
	ObjectLoader<ITest> OL;
	
	try
	{
		ITest* obj = OL.loadLocalObject( "ClassX" );
		FAIL( "Class instantiation should not work for this class!" );	
	}
	catch( ObjectLoadingException &exc )
	{
		// OK!
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] Exception occured: %1", string( exc.what() ) );			
	}	
}

/**
 * The object loader is defined to return
 * instances of type <code>BaseTestClass</code>.
 * Therefore casting to another type is not allowed.
 * -> Compiler error!
 */
TEST( ObjectLoader, LoadingAndWrongCast )
{	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-LoadingAndWrongCast Test" );	
	
	ObjectLoader<BaseTestClass> OL;	
	
	// compiler error!
	//string* obj = static_cast<string*> ( OL.loadObject( "TestClass" ) );				
}

/**
 * Checks whether the object loader is able to load objects from
 * DLLs.
 */
TEST( ObjectLoader, LoadingFromDll )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-LoadingDll Test" );	
	
	// loading object of type 'ITestImpl' from DLL './TestDll1.dll'
	ObjectLoader<ITest> OL( false, ".", "sof_TestDll1.dll" );	
	ITest* test = OL.loadObject( "ITestImpl" );
	CHECK( 69 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects of 
 * different type (ITestImpl2) from
 * DLLs. 
 */
TEST( ObjectLoader, LoadingFromDllDifferentType )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-LoadingFromDllDifferentType Test" );	
	
	ObjectLoader<ITest> OL( false, ".", "sof_TestDll1.dll" );	
	ITest* test = OL.loadObject( "ITestImpl2" );
	CHECK( 42 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects
 * from DLL even though the object loader is configured with
 * local search.
 *
 */
TEST( ObjectLoader, LoadingFromDllAfterLocalSearch )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-LoadingFromDllAfterLocalSearch Test" );	

	ObjectLoader<ITest> OL( true, ".", "sof_TestDll1.dll" );	
	ITest* test = OL.loadObject( "ITestImpl2" );
	CHECK( 42 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects
 * local although searching in DLL is configured too.
 *
 */
TEST( ObjectLoader, LoadingLocalObjectByConfiguredSearchingInDLL )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-LoadingLocalObjectByConfiguredSearchingInDLL Test" );	

	ObjectLoader<ITest> OL( true, ".", "sof_TestDll1.dll" );	
	ITest* test = OL.loadObject( "ITestImpl" );
	CHECK( 13 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load several
 * objects of different types consecutively.
 *
 */
TEST( ObjectLoader, LoadingSeveralObjectsOfDifferentTypes )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ClassloaderTest] *** ObjectLoader-LoadingSeveralObjectsOfDifferentTypes Test" );	

	ObjectLoader<ITest> OL( true, ".", "sof_TestDll1.dll" );	
	ITest* testObject1 = OL.loadObject( "ITestImpl" );
	CHECK( 13 == testObject1->getValue() );	

	ITest* testObject2 = OL.loadObject( "ITestImpl" );
	CHECK( 13 == testObject2->getValue() );	

	ITest* testObject3 = OL.loadObject( "ITestImpl2" );
	CHECK( 42 == testObject3->getValue() );	
}

/**
 * The object loader is defined to return
 * instances of type <code>BaseTestClass</code>.
 * Therefore casting to another type is not allowed.
 * -> Compiler error!
 */
TEST( ObjectLoader, LoadingDll3 )
{
	/*
	cout << "*** ObjectLoader-LoadingDll3 Test" << endl;
	ObjectLoader<ITest> OL( false, "C:/software_entwicklung/Test/osgi_sof/test/bin", "TestDll1.dll" );
	
	ITest* test = OL.loadObject( "ITestImpl" );
	cout << "value: " << (test->getValue()) << endl;
	// compiler error!
	//string* obj = static_cast<string*> ( OL::loadObject( "TestClass" ) );			
	*/
}

/**
 * The object loader is defined to return
 * instances of type <code>BaseTestClass</code>.
 * Therefore casting to another type is not allowed.
 * -> Compiler error!
 */
TEST( ObjectLoader, LoadingDll4 )
{
	/*
	cout << "*** ObjectLoader-LoadingDll4 Test" << endl;
	typedef ObjectLoader<ITest> OL;	
	
	try
	{
		ITest* test = OL::loadObjectFromDll( "C:/blabla", "TestDll1.dll", "foo" );
		cout << "value: " << (test->getValue()) << endl;
		FAIL( "Should not happen, class must not be loadable." );
	} catch( ObjectLoadingException &exc )
	{
		// OK!
		cout << "exception occured: " << exc.what() << endl;		
	}
	*/
}

/**
 * The object loader is defined to return
 * instances of type <code>BaseTestClass</code>.
 * Therefore casting to another type is not allowed.
 * -> Compiler error!
 */
TEST( ObjectLoader, LoadingLocalObject )
{
	/*
	cout << "*** ObjectLoader-LoadingLocalObject Test" << endl;
	ObjectLoader<BaseTestClass> OL;
	
	try
	{
		BaseTestClass* obj = OL.loadObject( "TestClass" );		
	}
	catch( ObjectLoadingException &exc )
	{
		cout << "exception occured: " << exc.what() << endl;
		FAIL( "Should not happen, class must be loadable" );
	}
	*/
}