// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "sof/config/ConfigFileReader.h"
#include "sof/config/ConfigurationException.h"

#include "UnitTestLogger.h"

// Standard namespaces
using namespace std;

using namespace sof::config;

string bundleNames[] = { "test_bundle1", "test_bundle2", "test_bundle3" };
string activatorNames[] = { "TestBundleActivator1", "TestBundleActivator2", "TestBundleActivator3" };
string libPaths[] = { BundleConfiguration::NO_LIB_PATH, "c:/temp/libraries", "c:/temp/foo/libraries" };
string libNames[] = { BundleConfiguration::NO_LIB_NAME, "test_bundle2.dll", "test_bundle3.dll" };

TEST( ConfigFileReader, ReadValidFileCheckNumberOfConfigEntries )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ConfigFileReaderTest] *** ConfigFileReader-ReadValidFileCheckNumberOfConfigEntries Test" );

	try
	{
		vector<BundleConfiguration> bc = ConfigFileReader::readFromFile( "./config_file_reader_test.sof" );	
		CHECK( bc.size() == 3 );
	}
	catch( ConfigurationException &exc )
	{
		string msg( exc.what() );
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ConfigFileReaderTest] Exception occured: %1", msg );	
		FAIL( "Should not happen, file must be loadable" );
	}	
}

TEST( ConfigFileReader, ReadValidFileCheckContent )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ConfigFileReaderTest] *** ConfigFileReader-ReadValidFileCheckContent Test" );

	try
	{
		vector<BundleConfiguration> bc = ConfigFileReader::readFromFile( "./config_file_reader_test.sof" );	
		vector<BundleConfiguration>::iterator iter;
		int counter = 0;
		for ( iter = bc.begin(); iter != bc.end(); iter++ )
		{
			CHECK( (*iter).getBundleName() == bundleNames[counter] );
			CHECK( (*iter).getClassName() == activatorNames[counter] );
			CHECK( (*iter).getLibraryPath() == libPaths[counter] );
			CHECK( (*iter).getLibraryName() == libNames[counter] );
			counter++;
		}
	}
	catch( ConfigurationException &exc )
	{
		string msg( exc.what() );
		UnitTestLogger::getInstance().log( Logger::DEBUG, "[ConfigFileReaderTest] Exception occured: %1", msg );	
		FAIL( "Should not happen, file must be loadable" );
	}	
}
