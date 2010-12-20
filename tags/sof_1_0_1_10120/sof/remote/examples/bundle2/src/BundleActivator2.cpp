#include "BundleActivator2.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/Properties.h"
#include "sof/framework/remote/corba/RemoteServiceReference.h"

using namespace sof::instantiation;
using namespace sof::framework;
using namespace sof::framework::remote::corba;

BundleActivator2::BundleActivator2() 
{
	this->tracker = 0;
}

BundleActivator2::~BundleActivator2() 
{
	// Deallocate memory
}

void BundleActivator2::start(IRemoteBundleContext::ConstPtr context) 
{
	this->tracker = new RemoteServiceTracker( context, "Multiplier", this );
	this->tracker->startTracking();
}

void BundleActivator2::stop(IRemoteBundleContext::ConstPtr context) 
{
	this->tracker->stopTracking();
	delete ( this->tracker );
}

bool BundleActivator2::addingService( const RemoteServiceReference& ref )
{
	cout << "[BundleActivator2#addingService] Called." << endl;	
	if ( ref.getServiceName() == "Multiplier" )
	{
		Properties props = ref.getServiceProperties();
		cout << "[BundleActivator2#addingService] Multiplier instance found." << endl;	
		cout << "[BundleActivator2#addingService] Properties: " << props.toString() << endl;	
		cout << "[BundleActivator2#addingService] Service reference: " << ref.toString() << endl;	
		Multiplier_var multiplier = Multiplier::_narrow( ref.getRemoteService() );
		CORBA::Long result = multiplier->multiply( 8, 15 );
		cout << "Result: " << result << endl; 
		return true;
	}
	else
	{
		return false;
	}
}

void BundleActivator2::removedService( const RemoteServiceReference& ref )
{
	cout << "[BundleActivator2#removedService] Called, ref: " << ref.toString() << endl;	
}

REGISTER_REMOTE_BUNDLE_ACTIVATOR_CLASS( "BundleActivator2", BundleActivator2 )

