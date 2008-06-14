#ifndef NULL_CREATOR_H
#define NULL_CREATOR_H

#include <string>

#include "ObjectCreationException.h"

using namespace std;
using namespace sof::instantiation;

namespace sof { namespace instantiation {

/**
 * The <code>NullCreator</code> class is an default implementation
 * of the creation policy which can be defined when a new 
 * <code>Launcher</code> object is created.<br>
 * When the <code>NullCreator</code> class is used it is not possible
 * to create objects from DLL, because the <code>NullCreator</code> object
 * returns a null pointer for the <code>createObjectFromDll</code>.
 */
template <typename BaseT>
class NullCreator
{
	public:

		/**
		 * Each class which implements the creation policy has to implement this
		 * method for creating objects from a DLL.<br>
		 * That means the method implementation has to load the DLL and then call
		 * the DLL for creating an object.
		 *
		 * @param path
	     *			The path to the directory where the DLL is located.
		 * @param dllName
		 *			The name of the DLL which has to be loaded.
		 * @param className
		 *			The name of the class an object is created from.
		 */
		static BaseT* createObjectFromDll( const string &path, const string &dllName, const string &className );
};

template <typename BaseT>
BaseT* NullCreator<BaseT>::createObjectFromDll( const string &path, const string &dllName, const string &className )
{
	return 0;
}

}}
#endif