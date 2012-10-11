#include "sof/framework/remote/corba/CORBAHelper.h"
#include "sof/framework/remote/corba/RemoteSOFLauncher.h"

#ifdef WIN32
#include "sof/instantiation/win/WinDllCreator.h"
#endif

#ifdef UNIX
#include "sof/instantiation/unix/SharedLibLoader.h"
#endif

#include "sof/instantiation/NullCreator.h"
#include "sof/util/threading/SingleThreaded.h"

using namespace std;
using namespace sof::framework;
using namespace sof::framework::remote;
using namespace sof::framework::remote::corba;

#ifdef WIN32
using namespace sof::instantiation::win;
#endif

#ifdef UNIX
using namespace sof::instantiation::unix_;
#endif


int main( int argc, char **argv)
{	
	Logger::LogLevel logLevel = Logger::LOG_DEBUG;
	vector<string> args;

	string processName;
	string ipAddress;

	for ( int i=0; i<argc; i++ )
	{
		string arg(argv[i]);
		args.push_back( arg );
		
		if ( arg == "-nolog" )
		{
			logLevel = Logger::LOG_NOLOG;
		}
		else if ( arg == "-errorlog" )
		{
			logLevel = Logger::LOG_ERROR;
		}
		else if ( arg == "-debuglog" )
		{
			logLevel = Logger::LOG_DEBUG;
		}		
		else if ( arg.find( "-proc_name:" ) == 0 )
		{
			processName = arg.substr( 11, arg.length() );
		}
		else if ( arg.find( "-registry_addr:") == 0 )
		{
			ipAddress = arg.substr( 15, arg.length() );
		}
	}

	if ( processName.length() == 0 )
	{
		cout << "!error: no process name defined." << endl;
		return -1;
	}

	CORBAHelper corbaHelper( args );
	corbaHelper.start();

	#ifdef WIN32
		RemoteSOFLauncher<SingleThreaded,WinDllCreator> launcher( corbaHelper, processName, ipAddress );
	#elif UNIX
		RemoteSOFLauncher<SingleThreaded,SharedLibLoader> launcher( corbaHelper, processName, ipAddress );
	#endif
	
	launcher.setLogLevel( logLevel );
	launcher.startAdministrationBundle();
	
	return 0;    
}

