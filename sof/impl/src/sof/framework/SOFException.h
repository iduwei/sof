#ifndef SOF_EXCEPTION_H
#define SOF_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace sof { namespace framework {

using namespace std;

/**
 * The <code>SOFException</code> represents the base class of
 * all SOF related exceptions.
 *
 * @author magr74
 */
class SOFException : public exception
{
	protected:

		/**
		 * The message which describes the occured exception.
		 */
		string message;

	public:

		/**
		 * Creates instances of class <code>SOFException</code>.
		 *
		 * @param msg
		 *			The message text which describes the exception.
		 */
		SOFException( const string &msg );

		/**
		 * Destroys the exception instance.
		 */
		virtual ~SOFException() throw();

		/**
		 * Returns the message text.
		 */
		virtual const char* what() const throw();
};

}}
#endif