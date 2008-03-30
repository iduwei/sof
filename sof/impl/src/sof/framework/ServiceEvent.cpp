#include "ServiceEvent.h"

using namespace sof::framework;

ServiceEvent::ServiceEvent( const int &eventType, const ServiceReference &ref ) : type( eventType ), reference( ref ) 
{
	
}

int ServiceEvent::getType() const
{
	return this->type;
}

ServiceReference ServiceEvent::getReference() const 
{
	return this->reference;
}
