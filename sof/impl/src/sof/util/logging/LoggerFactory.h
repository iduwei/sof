#ifndef LOGGER_FACTORY_H
#define LOGGER_FACTORY_H

#include "Logger.h"
#include <string>
#include <map>

using namespace std;

namespace sof { namespace util { namespace logging {

class LoggerFactory
{
	private:
		LoggerFactory();
		static map<string,Logger*>* loggerMap;
		static Logger::LogLevel level;
	public:
		static Logger& getLogger( const string& logChannel );
		static void setLogLevel( Logger::LogLevel level );
};

}}}
#endif