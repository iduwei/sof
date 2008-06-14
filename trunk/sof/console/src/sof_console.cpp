#include <iostream>

#include "sof/framework/Launcher.h"
#include "sof/framework/Global.h"
#include "sof/instantiation/win/WinDllCreator.h"
#include "sof/instantiation/NullCreator.h"
#include "sof/util/threading/SingleThreaded.h"

using namespace std;
using namespace sof::framework;
using namespace sof::util::threading;
using namespace sof::instantiation::win;

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
	launcher.startAdministrationBundle();
	return 0;
}

