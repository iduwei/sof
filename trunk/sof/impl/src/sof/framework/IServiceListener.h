#ifndef ISERVICE_LISTENER_H
#define ISERVICE_LISTENER_H

#include "ServiceEvent.h"

namespace sof { namespace framework {

/**
 * The <code>IServiceListener</code> class defines the interface
 * for a listener object which is notified about service events 
 * (e.g. service was registered or deregistered).
 */
class IServiceListener
{
	public:
		
		/**
		 * Defines a constant pointer to a service listener object.
		 */
		typedef IServiceListener* const ConstPtr;

		/**
		 * Is called when a service event ocurred.
		 *
		 * @param serviceEvent
		 *				The service event.
		 */
		virtual void serviceChanged( const ServiceEvent &serviceEvent ) = 0;
};

}}
#endif