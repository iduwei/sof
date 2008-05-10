#ifndef SERVICE_EVENT_H
#define SERVICE_EVENT_H

#include "ServiceReference.h"

namespace sof { namespace framework {

using namespace sof::framework;

/**
 * The <code>ServiceEvent</code> class describes
 * a change in the lifecycle of a service.<br>
 * Currently there are two events defined:<br>
 * <ul>
 *		<li>REGISTER: Service is registered with the 
 *						framework.
 *		<li>UNREGISTER: Service is unregistered with the 
 *						framework.
 * </ul>
 */
class ServiceEvent
{
	private:		
		
		/**
		 * The type of the event.
		 */
		int type;

		/**
		 * The service reference which represents
		 * the service whose lifecycle changed.
		 */
		ServiceReference reference;

	public:

		/**
		 * Definition of the events.
		 */
		enum EventType { REGISTER, UNREGISTER };

	public:

		/**
		 * Creates instances of class <code>ServiceEvent</code>.
		 *
		 * @param type
		 *				The type of the event.
		 *
		 * @param reference
		 *				Describes the service.
		 */
		ServiceEvent( const int &type, const ServiceReference &reference );

		/**
		 * Returns the type of the event.
		 *
		 * @return
		 *			The event type.
		 */
		int getType() const;

		/**
		 * Returns the service reference.
		 *
		 * @return
		 *			The <code>ServiceReference</code> object.
		 */
		ServiceReference getReference() const;

};

}}
#endif