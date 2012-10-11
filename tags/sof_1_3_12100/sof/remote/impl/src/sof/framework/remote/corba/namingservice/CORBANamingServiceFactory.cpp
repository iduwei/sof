#include "CORBANamingServiceFactory.h"
#include "CORBANamingServiceImpl.h"
#include "CORBANamingService.h"

using namespace sof::framework::remote::corba::namingservice;

CORBANamingService* CORBANamingServiceFactory::createNamingService( CORBA::ORB_var orb )
{
	// TODO: check if created object is deleted again after use.
	return new CORBANamingServiceImpl( orb );	
}
