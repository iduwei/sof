#include "BundleActivator1.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/Properties.h"

#include "IServiceA.h"
#include "IServiceAImpl.h"

using namespace sof::instantiation;
using namespace sof::framework;

BundleActivator1::~BundleActivator1() 
{
	// Deallocate memory
}

void BundleActivator1::start(IBundleContext::ConstPtr context) 
{
	Properties props;
	props.put( "instance", "1" );

	this->service = new IServiceAImpl();
	this->serviceReg = context->registerService( "IServiceA", this->service, props ); 
}

void BundleActivator1::stop(IBundleContext::ConstPtr context) 
{
	this->serviceReg->unregister();
	delete this->service;
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "BundleActivator1", BundleActivator1 )

