#include <iostream>

#include "sof/framework/Launcher.h"

using namespace std;
using namespace sof::framework;

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

	Launcher launcher;

	launcher.setLogLevel( logLevel );
	launcher.startAdministrationBundle();
	return 0;
}

