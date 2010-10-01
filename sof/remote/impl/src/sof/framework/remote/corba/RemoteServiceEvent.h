#ifndef REMOTE_SERVICE_EVENT_H
#define REMOTE_SERVICE_EVENT_H

#include <string>
#include <sstream>

#include "RemoteServiceReference.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace sof::framework::remote::corba;
using namespace std;

/**
 * The <code>RemoteServiceEvent</code> class describes
 * a change in the lifecycle of a remote service.<br>
 * Currently there are two events defined:<br>
 * <ul>
 *		<li>REGISTER: Service is registered with the 
 *						framework.
 *		<li>UNREGISTER: Service is unregistered with the 
 *						framework.
 * </ul>
 *
 * @author magr74
 */
class RemoteServiceEvent
{
	public:

		/**
		 * Definition of the events.
		 */
		enum EventType { REGISTER, UNREGISTER };

	private:		
		
		/**
		 * The type of the event.
		 */
		int type;

		/**
		 * The remote service reference which represents
		 * the service whose lifecycle changed.
		 */
		RemoteServiceReference reference;	

	public:

		/**
		 * Creates instances of class <code>RemoteServiceEvent</code>.
		 * 
		 * @param type
		 *				The type of the event. Has to be of type integer due to compatibility to 
		 *				CORBA::short.
		 *
		 * @param reference
		 *				Describes the service.
		 */
		RemoteServiceEvent( int type, const RemoteServiceReference& reference );

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
		 *			The <code>RemoteServiceReference</code> object.
		 */
		RemoteServiceReference getReference() const;

		/**
		 * Returns a string representation of the <code>RemoteServiceEvent</code> object.
		 *
		 * @return
		 *			The string representation.
		 */
		string toString() const;

};

}}}}
#endif