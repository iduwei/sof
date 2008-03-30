#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

namespace sof { namespace util { namespace logging {

using namespace std;

class Logger
{	
	public:
		enum LogLevel { NOLOG, ERROR_ = 1, TRACE, DEBUG };

		virtual void log( LogLevel channel, const string& message, const string& param1,
				const string& param2, const string& param3 ) = 0;
				
		virtual void log( LogLevel channel, const string& message, const string& param1 ) = 0;
		
		virtual void log( LogLevel channel, const string& message, const string& param1, const string& param2 ) = 0;
		
		virtual void log( LogLevel channel, const string& message ) = 0;
		
		virtual void log( LogLevel channel, const string& message, int param1,
				int param2, int param3 ) = 0;
				
		virtual void log( LogLevel channel, const string& message, int param1 ) = 0;
		
		virtual void log( LogLevel channel, const string& message, int param1, int param2 ) = 0;
		
		virtual void log( LogLevel channel, const string& message, bool param1 ) = 0;
		
		virtual void log( LogLevel channel, const string& message, bool param1, bool param2 ) = 0;
		
		virtual void setLogLevel( LogLevel level ) = 0;
		
		
};

}}}
#endif 