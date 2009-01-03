#include "BundleActivator1.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/Properties.h"

#include "IMultiplier.h"
#include "IMultiplierImpl.h"

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

	this->service = new IMultiplierImpl();	
	this->serviceReg = context->registerService( "IMultiplier", this->service, props ); 
}

void BundleActivator1::stop(IBundleContext::ConstPtr context) 
{
	this->serviceReg->unregister();
	delete this->serviceReg;
	delete this->service;
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "BundleActivator1", BundleActivator1 )

