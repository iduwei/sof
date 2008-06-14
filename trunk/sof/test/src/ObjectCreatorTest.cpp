// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/instantiation/NullCreator.h"

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
	ObjectCreator<ITest,NullCreator> OC;

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
	ObjectCreator<ITest,NullCreator> OC;
	
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
	ObjectCreator<ITest,NullCreator> OC;
	
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
	
	ObjectCreator<BaseTestClass,NullCreator> OC;	
	
	// compiler error!
	//string* obj = static_cast<string*> ( OL.loadObject( "TestClass" ) );				
}

/**
 * The object creator uses here the NullCreator policy
 * for creating an object from a DLL. Therefore the loaded
 * object must be null.
 */
TEST( ObjectCreator, LoadFromDLLWithNullCreator )
{	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ObjectCreatorTest] *** ObjectLoader-LoadFromDLLWithNullCreator Test" );	
	
	ObjectCreator<ITest,NullCreator> OC;
	ITest* test = OC.createObjectFromDll( ".", "sof_TestDll1.dll", "ITestImpl2" );
	CHECK( test == 0 );			
}





