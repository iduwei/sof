#ifndef CONFIGURATION_EXCEPTION_H
#define CONFIGURATION_EXCEPTION_H

#include <stdexcept>
#include <string>

#include "../framework/SOFException.h"

namespace sof { namespace config {

using namespace std;

using namespace sof::framework;

/**
 * The <code>ConfigurationException</code> indicates that
 * something went wrong during reading configuration file.<br>
 * See class {@link sof::config::ConfigFileReader}.
 */
class ConfigurationException : public SOFException
{

	public:

		/**
		 * Creates instances of class <code>ConfigurationException</code>.
		 *
		 * @param msg
		 *			The message text which describes the exception.
		 */
		ConfigurationException( const string &msg );


};

}}
#endif