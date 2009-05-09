#include "BundleActivator1.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/Properties.h"

using namespace sof::instantiation;
using namespace sof::framework;

BundleActivator1::~BundleActivator1() 
{
	// Deallocate memory
}

void BundleActivator1::start(IRemoteBundleContext::ConstPtr context) 
{
	Properties props;
	props.put( "instance", "1" );

	this->service1 = new SpeakerImpl();
	this->serviceReg1 = context->registerRemoteService( "Speaker", this->service1, props );

	props.put( "instance", "2" );

	this->service2 = new SpeakerImpl();
	this->serviceReg2 = context->registerRemoteService( "Speaker", this->service2, props );
}

void BundleActivator1::stop(IRemoteBundleContext::ConstPtr context) 
{
	this->serviceReg1->unregister();
	delete this->serviceReg1;
	delete this->service1;

	this->serviceReg2->unregister();
	delete this->serviceReg2;
	delete this->service2;
}

REGISTER_REMOTE_BUNDLE_ACTIVATOR_CLASS( "BundleActivator1", BundleActivator1 )

