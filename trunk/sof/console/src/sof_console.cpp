#include <iostream>
#include "sof/framework/Launcher.h"

#ifdef WIN32
#include "sof/instantiation/win/WinDllCreator.h"
#endif

#include "sof/instantiation/NullCreator.h"
#include "sof/util/threading/SingleThreaded.h"

using namespace std;
using namespace sof::framework;
using namespace sof::util::threading;

#ifdef WIN32
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

	#ifdef WIN32
		Launcher<SingleThreaded,WinDllCreator> launcher;
	#else
		Launcher<SingleThreaded,NullCreator> launcher;
	#endif
	launcher.setLogLevel( logLevel );
	launcher.startAdministrationBundle();
	return 0;
}

