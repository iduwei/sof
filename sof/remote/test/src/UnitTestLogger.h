#ifndef UNIT_TEST_LOGGER_H
#define UNIT_TEST_LOGGER_H

#include "sof/util/logging/LoggerFactory.h"
#include "sof/util/logging/Logger.h"

using namespace sof::util::logging;

class UnitTestLogger
{
	public:
		static Logger& getInstance();
};
#endif