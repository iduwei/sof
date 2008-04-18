#ifndef OBJECT_CREATION_EXCEPTION_H
#define OBJECT_CREATION_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace sof { namespace instantiation {

using namespace std;

/**
 * The <code>ObjectCreationException</code> defines an exception which
 * is thrown when the <code>ObjectCreator</code> instance tries to create
 * an object (e.g. a bundle activator object) but it can not be created
 * (e.g. the bundle library or bundle activator class is unknown).
 */
class ObjectCreationException : public exception
{
	private:

		/**
		 * The message of the exception.
		 */
		string message;

	public:

		/**
		 * Creates instances of class <code>ObjectCreationException</code>.
		 *
		 * @param msg
		 *			The message of the exception.
		 */
		ObjectCreationException( const string &msg );

		/**
		 * Returns what kind of error happened.
		 */
		const char* what() const;
};

}}
#endif