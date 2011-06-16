#ifndef SHARED_LIB_LOADER_H
#define SHARED_LIB_LOADER_H

#include <string>
#include <dlfcn.h>

#include "../../util/logging/Logger.h"
#include "../../util/logging/LoggerFactory.h"
#include "../ObjectCreationException.h"

using namespace std;

using namespace sof::instantiation;
using namespace sof::util::logging;

namespace sof { namespace instantiation { namespace unix_ {

/**
 * The <code>SharedLibLoader</code> class implements the creation policy which
 * is used by the <code>ObjectCreator</code> class (see 
 * {@link sof::framework::instantiation::ObjectCreator::createObjectFromDll}) 
 * in order to create objects from a shared library.<br>
 * The <code>SharedLibLoader</code> is only able to create objects from a Unix
 * shared library.
 *
 * @author magr74
 */
template <typename BaseT>
class SharedLibLoader
{
	public:

		/**
		 * Creates an object from a shared library.
		 *
		 * @param path
		 *			The path where the UNIX shared library is located.
		 * @param dllName
		 *			The name of the Windows DLL.
		 * @param className
		 *			The name of the class an object is created from.
		 * @return
		 *			The pointer to the created object.
		 */
		static BaseT* createObjectFromDll( const string &path, const string &dllName, const string &className );
		
		/**
		 * Returns a logger instance.
		 *
		 * @return
		 *		Returns an instance of class <code>Logger</code>.
		 */
		static Logger& getLogger();
};

template <typename BaseT>
Logger& SharedLibLoader<BaseT>::getLogger()
{
	static Logger& logger = LoggerFactory::getLogger( "ObjectCreation" );
	return logger;
}

template <typename BaseT>
BaseT* SharedLibLoader<BaseT>::createObjectFromDll( const string &path, const string &dllName, const string &className )
{
	
	typedef BaseT* (*DLLPROC) ( const string& );

	DLLPROC pFunc = NULL;

	ostringstream str;
	
	int pos = path.find_last_of( '/' );
	if ( pos == ( path.size() - 1 ) )
	{
		str << path << dllName;	
	}
	else
	{
		str << path << '/' << dllName;	
	}
	
	getLogger().log( Logger::LOG_DEBUG, "[SharedLibLoader#createObjectFromDll] Loading DLL: '%1'", str.str() );

	void *lib_handle = NULL;
	try
	{
		lib_handle = dlopen( str.str().c_str(), RTLD_NOW);
	}
	catch( exception &exc )
	{
		getLogger().log( Logger::LOG_ERROR, "[SharedLibLoader#createObjectFromDll] Error occurred during loading DLL: %1", exc.what() );
		lib_handle = NULL;
	}

	if ( lib_handle == NULL )
	{
		ObjectCreationException exc( "Error during loading DLL." );
		throw exc;
	}
	
	try
	{
		pFunc = ( DLLPROC ) dlsym(lib_handle, "createObject");
	}
	catch( exception &exc)
	{
		getLogger().log( Logger::LOG_ERROR, "[SharedLibLoader#createObjectFromDll] Error occurred during calling DLL entry method, %1", exc.what() );
		pFunc = NULL;
	}

	char* error;
	if ( pFunc == NULL || (error = dlerror()) != NULL )
	{
		ObjectCreationException exc( "Error during loading object from DLL." );
		throw exc;
	}	
	return ((*pFunc)(className));
}

}}}
#endif