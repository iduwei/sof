#ifndef CORBA_NAMING_SERVICE_H
#define CORBA_NAMING_SERVICE_H

#include <CORBA.h>

#include <list>
#include <string>

using namespace std;

namespace sof { namespace framework { namespace remote { namespace corba { namespace namingservice {

/**
 * The <code>CORBANamingService</code> interface provides convenient methods for accessing the
 * CORBA naming service.
 *
 * @author magr74
 */
class CORBANamingService {

	public:

		/**
		 * Destroys the object.
		 */
		virtual ~CORBANamingService() {}

		/**
		 * Searches for CORBA objects at naming service.
		 *
		 * @param path 
		 *			Specifies the path at the CORBA naming service where the
		 *			CORBA objects can be found.
		 *
		 * @return
		 *			The list object which contains the found CORBA objects.
		 */
		virtual list<CORBA::Object_var> findObjects( const string& path ) = 0;

		/**
		 * Binds a CORBA object to a specified path and name.
		 *
		 * @param path
		 *				The path name where the CORBA object can be found at
		 *				CORBA naming service.
		 *
		 * @param objectName
		 *				The name of the CORBA object which is registered at CORBA
		 *				naming service.
		 *
		 * @param object
		 *				The CORBA object which is registered at CORBA naming service.
		 */
		virtual void bindObject( const string& path, const string& objectName,
			CORBA::Object_var object ) = 0;

		/**
		 * Unbinds a CORBA object from CORBA naming service.
		 *
		 * @param path
		 *			The path name where the CORBA object can be found for unbinding.
		 *
		 * @param objectName
		 *			The name of the CORBA object which is unbound.
		 */
		virtual void unbindObject( const string& path, const string& objectName ) = 0;

};

}}}}}
#endif
