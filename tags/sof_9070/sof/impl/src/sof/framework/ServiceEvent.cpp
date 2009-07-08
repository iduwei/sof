#include "ServiceEvent.h"

using namespace sof::framework;

ServiceEvent::ServiceEvent( const int &eventType, ServiceReference &ref ) : type( eventType ), reference( ref ) 
{
	
}

int ServiceEvent::getType() const
{
	return this->type;
}

ServiceReference& ServiceEvent::getReference() const 
{
	return this->reference;
}

   
string ServiceEvent::toString() const
{	
	ostringstream eventStream;
	eventStream << "ServiceEvent={";
	eventStream << "type=" << this->type << ", ";
	eventStream << this->reference.toString();
	eventStream << "}";
	return eventStream.str();
}