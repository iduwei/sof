#include <CORBA.h>
#include <coss/CosNaming.h>
#include <iostream>
#include <string>
#include <pthread.h>


#include "sof/framework/remote/corba/namingservice/CORBANamingServiceImpl.h"
#include "sof/framework/remote/corba/registry/CORBARegistryImpl.h"
#include "sof/framework/remote/corba/generated/CORBAObjects.h"
#include "sof/framework/remote/corba/registry/IRemoteRegistryImpl.h"
#include "sof/framework/remote/corba/CORBAHelper.h"
#include "sof/framework/remote/corba/RemoteSOFLauncher.h"

using namespace std;

using namespace sof::framework::remote;
using namespace sof::framework::remote::corba;
using namespace sof::framework::remote::corba::namingservice;
using namespace sof::framework::remote::corba::registry;
using namespace sof::framework::remote::corba::registry::generated;


int main( int argc, char **argv)
{	
	Logger::LogLevel logLevel = Logger::LogLevel::DEBUG;
	vector<string> args;

	for ( int i=0; i<argc; i++ )
	{
		string arg(argv[i]);
		args.push_back( arg );
		
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
	args.push_back( "-ORBNamingAddr" );
	args.push_back( "inet:localhost:5000" );

	CORBAHelper corbaHelper( args );
	corbaHelper.start();

	#ifdef WIN
		RemoteSOFLauncher<SingleThreaded,WinDllCreator> launcher( corbaHelper );
	#else
		RemoteSOFLauncher<SingleThreaded,NullCreator> launcher( corbaHelper );
	#endif
	
	launcher.setLogLevel( logLevel );

	BundleConfiguration bundle1( "bundle1", "BundleActivator1" );
	vector<BundleConfiguration> configuration;
	configuration.push_back( bundle1 );

	launcher.start( configuration );

	launcher.startAdministrationBundle();
	
	return 0;    
}


