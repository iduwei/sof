#ifndef BUNDLE_ACTIVATOR1_H
#define BUNDLE_ACTIVATOR1_H

#include "sof/framework/IBundleActivator.h"
#include "sof/framework/IBundleContext.h"
#include "sof/framework/IServiceRegistration.h"

#include "IServiceA.h"

using namespace sof::framework;

class BundleActivator1 : public IBundleActivator
{
	private:
		IServiceA* service;
		IServiceRegistration* serviceReg;

	public:
		virtual ~BundleActivator1();
		virtual void start( IBundleContext::ConstPtr context );	
		virtual void stop( IBundleContext::ConstPtr context );
};

#endif