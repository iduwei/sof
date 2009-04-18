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

	this->service = new SpeakerImpl();
	this->serviceReg = context->registerRemoteService( "Speaker", this->service, props );


}

void BundleActivator1::stop(IRemoteBundleContext::ConstPtr context) 
{
	this->serviceReg->unregister();
	delete this->serviceReg;
	delete this->service;
}

REGISTER_REMOTE_BUNDLE_ACTIVATOR_CLASS( "BundleActivator1", BundleActivator1 )

