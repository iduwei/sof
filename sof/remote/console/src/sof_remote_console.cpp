#include "sof/framework/Global.h"
#include "sof/framework/remote/corba/CORBAHelper.h"
#include "sof/framework/remote/corba/RemoteSOFLauncher.h"

#ifdef WIN
#include "sof/instantiation/win/WinDllCreator.h"
#endif

#include "sof/instantiation/NullCreator.h"
#include "sof/util/threading/SingleThreaded.h"

using namespace std;
using namespace sof::framework;
using namespace sof::framework::remote;
using namespace sof::framework::remote::corba;

#ifdef WIN
using namespace sof::instantiation::win;
#endif


int main( int argc, char **argv)
{	
	Logger::LogLevel logLevel = Logger::LogLevel::DEBUG;
	vector<string> args;

	string processName;

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
		else if ( arg.find( "-proc_name:" ) == 0 )
		{
			processName = arg.substr( 10, arg.length() );
		}
	}

	if ( processName.length() == 0 )
	{
		cout << "!error: no process name defined." << endl;
		return -1;
	}

	CORBAHelper corbaHelper( args );
	corbaHelper.start();

	#ifdef WIN
		RemoteSOFLauncher<SingleThreaded,WinDllCreator> launcher( corbaHelper );
	#else
		RemoteSOFLauncher<SingleThreaded,NullCreator> launcher( corbaHelper );
	#endif
	
	launcher.setLogLevel( logLevel );
	launcher.startAdministrationBundle();
	
	return 0;    
}

