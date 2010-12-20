#ifndef UNIT_TEST_LOGGER_H
#define UNIT_TEST_LOGGER_H

#include "sof/util/logging/LoggerFactory.h"
#include "sof/util/logging/Logger.h"

using namespace sof::util::logging;

/**
 * Logger used by the test cases.
 */
class UnitTestLogger
{
	public:

		/**
		 * Returns the logger instance.
		 *
		 * @return
		 *			The logger instance.
		 */
		static Logger& getInstance();
};
#endif