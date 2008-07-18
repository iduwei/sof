#include "BundleActivator2.h"

#include <iostream>

#include "sof/instantiation/ObjectCreator.h"

#include "IServiceA.h"

using namespace std;
using namespace sof::instantiation;

BundleActivator2::~BundleActivator2() 
{
	// Deallocate memory
}

void BundleActivator2::start(IBundleContext::ConstPtr context) 
{
	this->tracker = new ServiceTracker( context, "IServiceA", this );
	this->tracker->startTracking();
}

void BundleActivator2::stop(IBundleContext::ConstPtr context) 
{
	this->tracker->stopTracking();
	delete ( this->tracker );
}

bool BundleActivator2::addingService( const ServiceReference& ref )
{
	if ( ref.getServiceName() == "IServiceA" )
	{
		Properties props = ref.getServiceProperties();
		if ( props.get( "instance" ) == "1" )
		{
			this->service = static_cast<IServiceA*> ( ref.getService() );
			cout << "[BundleActivator2#addingService] Calling IServiceA..." << endl;
			int value = this->service->getValue();
			cout << "[BundleActivator2#addingService] Returned value of IServiceA: " << value << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void BundleActivator2::removedService( const ServiceReference& ref )
{
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "BundleActivator2", BundleActivator2 )
