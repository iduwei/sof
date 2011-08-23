#include "BundleActivator2.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/Properties.h"
#include "sof/framework/remote/corba/RemoteServiceReference.h"

#include "IDivider.h"

using namespace sof::instantiation;
using namespace sof::framework;
using namespace sof::framework::remote::corba;

BundleActivator2::BundleActivator2() 
{
	this->service1 = 0;
	this->serviceReg1 = 0;
	this->service2 = 0;
	this->serviceReg2 = 0;
	this->tracker = 0;

}

BundleActivator2::~BundleActivator2() 
{
	// Deallocate memory
}

void BundleActivator2::start(IRemoteBundleContext::ConstPtr context) 
{
	Properties props;
	props.put( "instance", "1" );

	this->service1 = new IDividerImpl();
	this->serviceReg1 = context->registerService( "Divider", this->service1, props );

	props.put( "instance", "2" );

	this->service2 = new IDividerImpl();
	this->serviceReg2 = context->registerService( "Divider", this->service2, props );

	this->tracker = new RemoteServiceTracker( context, "Multiplier", this );
	this->tracker->startTracking();

	this->localTracker = new LocalServiceTracker( context, "Divider", this );
	this->localTracker->startTracking();
}

void BundleActivator2::stop(IRemoteBundleContext::ConstPtr context) 
{
	this->serviceReg1->unregister();
	delete this->serviceReg1;
	delete this->service1;

	this->serviceReg2->unregister();
	delete this->serviceReg2;
	delete this->service2;

	this->tracker->stopTracking();
	delete ( this->tracker );

	this->localTracker->stopTracking();
	delete ( this->localTracker );
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

bool BundleActivator2::addingService( const ServiceReference& ref )
{
	cout << "[BundleActivator2#addingService] Called." << endl;
	if ( ref.getServiceName() == "Divider" )
	{
		Properties props = ref.getServiceProperties();
		cout << "[BundleActivator2#addingService] Multiplier instance found." << endl;
		cout << "[BundleActivator2#addingService] Properties: " << props.toString() << endl;
		cout << "[BundleActivator2#addingService] Service reference: " << ref.toString() << endl;
		IDivider* divider = static_cast<IDivider*> (ref.getService());
		double result = divider->divide( 15, 5 );
		cout << "Result: " << result << endl;
		return true;
	}
	else
	{
		return false;
	}
}

void BundleActivator2::removedService( const ServiceReference& ref )
{
	cout << "[BundleActivator2#removedService] Called, ref: " << ref.toString() << endl;
}

REGISTER_REMOTE_BUNDLE_ACTIVATOR_CLASS( "BundleActivator2", BundleActivator2 )

