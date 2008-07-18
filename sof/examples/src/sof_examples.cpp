#include <iostream>
#include <vector>

#include "sof/framework/Launcher.h"
#include "sof/framework/Global.h"
#include "sof/config/BundleConfiguration.h"

#ifdef WIN
#include "sof/instantiation/win/WinDllCreator.h"
#endif

#include "sof/instantiation/NullCreator.h"
#include "sof/util/threading/SingleThreaded.h"

using namespace std;
using namespace sof::framework;
using namespace sof::config;
using namespace sof::util::threading;

#ifdef WIN
using namespace sof::instantiation::win;
#endif

int main(int argc, char* argv[])
{
	Logger::LogLevel logLevel = Logger::LogLevel::DEBUG;
	for ( int i=0; i<argc; i++ )
	{
		string arg(argv[i]);
		if ( arg == "-nolog" )
		{
			logLevel = Logger::LogLevel::NOLOG;
		}
		else if ( arg == "-errorlog" )
		{
			logLevel = Logger::LogLevel::ERROR_;
		}
		else if ( arg == "-debuglog" )
		{
			logLevel = Logger::LogLevel::DEBUG;
		}
	}

	#ifdef WIN
		Launcher<SingleThreaded,WinDllCreator> launcher;
	#else
		Launcher<SingleThreaded,NullCreator> launcher;
	#endif
	
	launcher.setLogLevel( logLevel );

	BundleConfiguration bundle1( "bundle1", "BundleActivator1", ".", "sof_examples_bundle1.dll" );
	BundleConfiguration bundle2( "bundle2", "BundleActivator2", ".", "sof_examples_bundle2.dll" );
	vector<BundleConfiguration> configuration;
	configuration.push_back( bundle1 );
	configuration.push_back( bundle2 );

	launcher.start( configuration );

	launcher.startAdministrationBundle();
	return 0;
}

