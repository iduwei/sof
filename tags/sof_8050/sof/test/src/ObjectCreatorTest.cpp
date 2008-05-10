// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "sof/instantiation/ObjectCreator.h"

#include "BaseTestClass.h"
#include "ITest.h"
#include "ITestImpl.h"
#include "TestClass.h"
#include "UnitTestLogger.h"

// Standard namespaces
using namespace std;

using namespace sof::instantiation;

/**
 * Tests whether loading of a class
 * and casting to the base class 
 * (here: <code>BaseClass</code>) works.
 */
TEST( ObjectCreator, Loading )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectCreator-Loading Test" );
		
	// only local search
	ObjectCreator<ITest> OC;

	try
	{
		ITest* obj = OC.createObject( "ITestImpl" );	
		CHECK( 13 == obj->getValue() );
	}
	catch( ObjectCreationException &exc )
	{
		string msg( exc.what() );
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] Exception occured: %1", msg );	
		FAIL( "Should not happen, class must be loadable" );
	}	
}

/**
 * Tests whether loading of a class and
 * casting to the loaded class 
 * (here: <code>TestClass</code>) works.
 */
TEST( ObjectCreator, LoadingAndCast )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadingAndCast Test" );
	
	// only local search
	ObjectCreator<ITest> OC;
	
	try
	{
		ITestImpl* obj = static_cast<ITestImpl*> ( OC.createObject( "ITestImpl" ) );
		CHECK( 13 == obj->getValue() );
	}
	catch( ObjectCreationException &exc )
	{
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] Exception occured: %1", string( exc.what() ) );	
		FAIL( "Should not happen, class must be loadable" );
	}	
}

/**
 * Tests whether loading a class which
 * is not available (not registered at class loader)
 * leads to an exception.
 */
TEST( ObjectCreator, NotAvailableClass )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-NotAvailableClass Test" );	
	
	// only local search
	ObjectCreator<ITest> OC;
	
	try
	{
		ITest* obj = OC.createLocalObject( "ClassX" );
		FAIL( "Class instantiation should not work for this class!" );	
	}
	catch( ObjectCreationException &exc )
	{
		// OK!
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] Exception occured: %1", string( exc.what() ) );			
	}	
}

/**
 * The object loader is defined to return
 * instances of type <code>BaseTestClass</code>.
 * Therefore casting to another type is not allowed.
 * -> Compiler error!
 */
TEST( ObjectCreator, LoadingAndWrongCast )
{	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadingAndWrongCast Test" );	
	
	ObjectCreator<BaseTestClass> OC;	
	
	// compiler error!
	//string* obj = static_cast<string*> ( OL.loadObject( "TestClass" ) );				
}

/**
 * Checks whether the object loader is able to load objects from
 * DLLs.
 */
TEST( ObjectCreator, LoadingFromDll )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadingDll Test" );	
	
	// loading object of type 'ITestImpl' from DLL './TestDll1.dll'
	ObjectCreator<ITest> OC( false, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl" );
	CHECK( 69 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects of 
 * different type (ITestImpl2) from
 * DLLs. 
 */
TEST( ObjectCreator, LoadingFromDllDifferentType )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadingFromDllDifferentType Test" );	
	
	ObjectCreator<ITest> OC( false, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl2" );
	CHECK( 42 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects
 * from DLL even though the object loader is configured with
 * local search.
 *
 */
TEST( ObjectCreator, LoadingFromDllAfterLocalSearch )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadingFromDllAfterLocalSearch Test" );	

	ObjectCreator<ITest> OC( true, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl2" );
	CHECK( 42 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects
 * local although searching in DLL is configured too.
 *
 */
TEST( ObjectCreator, LoadingLocalObjectByConfiguredSearchingInDLL )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadingLocalObjectByConfiguredSearchingInDLL Test" );	

	ObjectCreator<ITest> OC( true, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl" );
	CHECK( 13 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load several
 * objects of different types consecutively.
 *
 */
TEST( ObjectCreator, LoadingSeveralObjectsOfDifferentTypes )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadingSeveralObjectsOfDifferentTypes Test" );	

	ObjectCreator<ITest> OC( true, ".", "sof_TestDll1.dll" );	
	ITest* testObject1 = OC.createObject( "ITestImpl" );
	CHECK( 13 == testObject1->getValue() );	

	ITest* testObject2 = OC.createObject( "ITestImpl" );
	CHECK( 13 == testObject2->getValue() );	

	ITest* testObject3 = OC.createObject( "ITestImpl2" );
	CHECK( 42 == testObject3->getValue() );	
}

/**
 * The object loader is defined to return
 * instances of type <code>BaseTestClass</code>.
 * Therefore casting to another type is not allowed.
 * -> Compiler error!
 */
TEST( ObjectCreator, LoadingDll3 )
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
TEST( ObjectCreator, LoadingDll4 )
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
TEST( ObjectCreator, LoadingLocalObject )
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