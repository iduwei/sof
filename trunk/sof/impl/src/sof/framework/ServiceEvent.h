#ifndef SERVICE_EVENT_H
#define SERVICE_EVENT_H

#include "ServiceReference.h"

namespace sof { namespace framework {

using namespace sof::framework;

class ServiceEvent
{
	private:		
		int type;
		ServiceReference reference;

	public:
		// Attention: bei Verwendung von REGISTERED anstatt REGISTER gibt es bei der Kompilierung
		// der Unit-Tests zu Kompilierfehlern!!!
		enum EventType { REGISTER, UNREGISTER };

	public:		
		ServiceEvent( const int &type, const ServiceReference &reference );
		int getType() const;
		ServiceReference getReference() const;

};

}}
#endif