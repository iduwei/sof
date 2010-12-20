#ifndef CORBA_NAMING_SERVICE_IMPL_H
#define CORBA_NAMING_SERVICE_IMPL_H

#include <coss/CosNaming.h>

#include "CORBANamingService.h"

namespace sof { namespace framework { namespace remote { namespace corba { namespace namingservice {

/**
 * The <code>CORBANamingServiceImpl</code> class implements the
 * <code>CORBANamingService</code> interface and provides methods for
 * accessing the CORBA naming service.
 *
 * @author magr74
 */
class CORBANamingServiceImpl : public CORBANamingService {

	private:

		/**
		 * Reference to the CORBA naming service.
		 */
		CosNaming::NamingContext_var naming_context;
		
		/**
		 * The CORBA ORB instance.
		 */
		CORBA::ORB_var orb;

	public:

		/**
		 * Creates instances of class <code>CORBANamingServiceImpl</code>.
		 *
		 * TODO: check if this constructor is necessary.
		 */
		CORBANamingServiceImpl();
		
		/**
		 * Creates instances of class <code>CORBANamingServiceImpl</code>.
		 *
		 * @param orb
		 *			The CORBA ORB instance.
		 */
		CORBANamingServiceImpl( CORBA::ORB_var orb );

		/**
		 * Creates instances of class <code>CORBANamingServiceImpl</code>.
		 *
		 * @param ctx
		 *			The CORBA naming service context.
		 */
		CORBANamingServiceImpl( CosNaming::NamingContext_var ctx );

		/**
		 * Destroys instances of class <code>CORBANamingServiceImpl</code>.
		 */
		virtual ~CORBANamingServiceImpl();

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
		list<CORBA::Object_var> findObjects( const string& objectName );

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
		void bindObject( const string& name, const string& objectName,
			CORBA::Object_var object );

		/**
		 * Unbinds a CORBA object from CORBA naming service.
		 *
		 * @param path
		 *			The path name where the CORBA object can be found for unbinding.
		 *
		 * @param objectName
		 *			The name of the CORBA object which is unbound.
		 */
		void unbindObject( const string& name, const string& objectName );
		
		/**
		 * Returns the path elements (e.g. ['foo','bar','xy']) of a path string (e.g. 'foo/bar/xy').
		 * 
		 * TODO: have to be moved in private block.
		 *
		 * @param path
		 *			The string containing the path.
		 *
		 * @return 
		 *			Returns the list which contains the path elements as string.
		 */
		list<string> getPathElements( const string& path );
		
		/**
		 * Returns the CORBA naming context object of a specific path.
		 *
		 * @param names
		 *			The string which contains the path elements.
		 *
		 * @param force
		 *			True, if naming context object is created if it does not exist, otherwise
		 *			false.
		 */
		CosNaming::NamingContext_var getNamingContext( list<string> names, bool force );

};

}}}}}

#endif
