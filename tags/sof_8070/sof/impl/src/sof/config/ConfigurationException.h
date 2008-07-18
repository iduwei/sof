#ifndef CONFIGURATION_EXCEPTION_H
#define CONFIGURATION_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace sof { namespace config {

using namespace std;

/**
 * The <code>ConfigurationException</code> indicates that
 * something went wrong during reading configuration file.<br>
 * See class {@link sof::config::ConfigFileReader}.
 */
class ConfigurationException : public exception
{
	private:

		/**
		 * The message which describes the occured exception.
		 */
		string message;

	public:

		/**
		 * Creates instances of class <code>ConfigurationException</code>.
		 *
		 * @param msg
		 *			The message text which describes the exception.
		 */
		ConfigurationException( const string &msg );

		/**
		 * Returns the message text.
		 */
		const char* what() const;
};

}}
#endif