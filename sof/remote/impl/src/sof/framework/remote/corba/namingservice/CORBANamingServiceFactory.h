#ifndef CORBA_NAMING_SERVICE_FACTORY_H
#define CORBA_NAMING_SERVICE_FACTORY_H

#include <string>

#include "CORBANamingService.h"

namespace sof { namespace framework { namespace remote { namespace corba { namespace namingservice {

/**
 * The <code>CORBANamingServiceFactory</code> represents a factory class for creating objects of
 * type <code>CORBANamingService</code>.
 */
class CORBANamingServiceFactory
{
	public:

		/**		 
		 * Creates objects of type <code>CORBANamingService</code>.
		 *
		 * @param orb
		 *			The ORB instance.
		 *
		 * @return
		 *			The created <code>CORBANamingService</code> object.
		 */
		CORBANamingService* CORBANamingServiceFactory::createNamingService( CORBA::ORB_var orb );

};

}}}}}
#endif