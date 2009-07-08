#include "UnitTestLogger.h"

#include "sof/util/logging/LoggerFactory.h"
#include "sof/util/logging/Logger.h"

using namespace sof::util::logging;

Logger& UnitTestLogger::getInstance()
{
	return LoggerFactory::getLogger( "Test" );
}