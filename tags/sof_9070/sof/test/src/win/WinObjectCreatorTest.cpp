// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "sof/framework/Global.h"
#include "sof/instantiation/ObjectCreator.h"

#ifdef WIN
#include "sof/instantiation/win/WinDllCreator.h"
#endif

#include "../BaseTestClass.h"
#include "../ITest.h"
#include "../ITestImpl.h"
#include "../TestClass.h"
#include "../UnitTestLogger.h"

// Standard namespaces
using namespace std;

using namespace sof::instantiation;

#ifdef WIN
using namespace sof::instantiation::win;
#endif

#ifdef WIN

/**
 * Checks whether the object loader is able to load objects from
 * DLLs.
 */
TEST( WinObjectCreator, LoadingFromDll )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[WinObjectCreatorTest] *** ObjectLoader-LoadingDll Test" );	
	
	// loading object of type 'ITestImpl' from DLL './TestDll1.dll'
	ObjectCreator<ITest,WinDllCreator> OC( false, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl" );
	CHECK( 69 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects of 
 * different type (ITestImpl2) from
 * DLLs. 
 */
TEST( WinObjectCreator, LoadingFromDllDifferentType )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[WinObjectCreatorTest] *** ObjectLoader-LoadingFromDllDifferentType Test" );	
	
	ObjectCreator<ITest,WinDllCreator> OC( false, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl2" );
	CHECK( 42 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects
 * from DLL even though the object loader is configured with
 * local search.
 *
 */
TEST( WinObjectCreator, LoadingFromDllAfterLocalSearch )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[WinObjectCreatorTest] *** ObjectLoader-LoadingFromDllAfterLocalSearch Test" );	

	ObjectCreator<ITest,WinDllCreator> OC( true, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl2" );
	CHECK( 42 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load objects
 * local although searching in DLL is configured too.
 *
 */
TEST( WinObjectCreator, LoadingLocalObjectByConfiguredSearchingInDLL )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[WinObjectCreatorTest] *** ObjectLoader-LoadingLocalObjectByConfiguredSearchingInDLL Test" );	

	ObjectCreator<ITest,WinDllCreator> OC( true, ".", "sof_TestDll1.dll" );	
	ITest* test = OC.createObject( "ITestImpl" );
	CHECK( 13 == test->getValue() );	
}

/**
 * Checks whether the object loader is able to load several
 * objects of different types consecutively.
 *
 */
TEST( WinObjectCreator, LoadingSeveralObjectsOfDifferentTypes )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[WinObjectCreatorTest] *** ObjectLoader-LoadingSeveralObjectsOfDifferentTypes Test" );	

	ObjectCreator<ITest,WinDllCreator> OC( true, ".", "sof_TestDll1.dll" );	
	ITest* testObject1 = OC.createObject( "ITestImpl" );
	CHECK( 13 == testObject1->getValue() );	

	ITest* testObject2 = OC.createObject( "ITestImpl" );
	CHECK( 13 == testObject2->getValue() );	

	ITest* testObject3 = OC.createObject( "ITestImpl2" );
	CHECK( 42 == testObject3->getValue() );	
}

#endif

/**
 * The object loader is defined to return
 * instances of type <code>BaseTestClass</code>.
 * Therefore casting to another type is not allowed.
 * -> Compiler error!
 */
TEST( WinObjectCreator, LoadingDll3 )
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
TEST( WinObjectCreator, LoadingDll4 )
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
TEST( WinObjectCreator, LoadingLocalObject )
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

