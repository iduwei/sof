#include "RemoteServiceEvent.h"

using namespace sof::framework::remote::corba;

RemoteServiceEvent::RemoteServiceEvent( int eventType, const RemoteServiceReference& ref ) : type( eventType ), reference( ref ) 
{
	
}

int RemoteServiceEvent::getType() const
{
	return this->type;
}

RemoteServiceReference RemoteServiceEvent::getReference() const 
{
	return this->reference;
}

   
string RemoteServiceEvent::toString() const
{	
	ostringstream eventStream;
	eventStream << "RemoteServiceEvent={";
	eventStream << "type=" << this->type << ", ";
	eventStream << this->reference.toString();
	eventStream << "}";
	return eventStream.str();
}