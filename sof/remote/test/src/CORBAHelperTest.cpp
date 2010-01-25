// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "UnitTestLogger.h"

#include "sof/framework/remote/corba/CORBAHelper.h"

// Standard namespaces
using namespace std;

using namespace sof::framework::remote::corba;

TEST( startStop, CORBAHelperTest )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[CORBAHelperTest] *** CORBAHelperTest-startStop Test" );
	vector<string> args;
	args.push_back( "-ORBNamingAddr" );
	args.push_back( "inet:localhost:5000" );
	args.push_back( "-ORBNamingAddr" );
	args.push_back( "inet:localhost:5000" );
	CORBAHelper corbaHelper( args );
	corbaHelper.start();
	string input;
	while( getline(cin,input) ) 
	{
		break;
	}
	corbaHelper.stop();
	while( getline(cin,input) ) 
	{
		break;
	}
}

TEST( startStop2, CORBAHelperTest )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[CORBAHelperTest] *** CORBAHelperTest-startStop2 Test" );
	vector<string> args;
	args.push_back( "-ORBNamingAddr" );
	args.push_back( "inet:localhost:5000" );
	args.push_back( "-ORBNamingAddr" );
	args.push_back( "inet:localhost:5000" );
	CORBAHelper corbaHelper( args );
	corbaHelper.start();
	string input;
	while( getline(cin,input) ) 
	{
		break;
	}
	corbaHelper.stop();
	while( getline(cin,input) ) 
	{
		break;
	}
}

