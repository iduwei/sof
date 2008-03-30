#ifndef LOGGER_IMPL_H
#define LOGGER_IMPL_H

#include "Logger.h"
#include <string>
#include <vector>

namespace sof { namespace util { namespace logging {

using namespace std;

class LoggerImpl : public Logger
{
	private:
		string logCh;
		string levels[4];
		unsigned int level;
		void logMessage( const vector<string>& messageParts, LogLevel level );
		void logMessage( const string& msg, const vector<int>& messageParts, LogLevel level );
		void logMessage( const string& msg, const vector<bool>& messageParts, LogLevel level );

		string lastLogMessage;
	public:
		LoggerImpl( const string& channel );
		void log( LogLevel channel, const string& message, const string& param1,
				const string& param2, const string& param3 );
		void log( LogLevel channel, const string& message, const string& param1,
				const string& param2 );
		void log( LogLevel channel, const string& message, const string& param1 );
		void log( LogLevel channel, const string& message, int param1,
				int param2, int param3 );
		void log( LogLevel channel, const string& message, int param1,
				int param2 );
		void log( LogLevel channel, const string& message, int param1 );
		void log( LogLevel channel, const string& message );
		void log( LogLevel channel, const string& message, bool param1 );
		void log( LogLevel channel, const string& message, bool param1, bool param2 );
		void setLogLevel( Logger::LogLevel level );
		string getLastLogMessage();
};

}}}
#endif 