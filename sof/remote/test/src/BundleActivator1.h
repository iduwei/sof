#ifndef BUNDLE_ACTIVATOR1_H
#define BUNDLE_ACTIVATOR1_H

#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/remote/corba/IRemoteBundleContext.h"

#include "sof/framework/IServiceRegistration.h"

#include "MultiplierImpl.h"

using namespace sof::framework::remote::corba;

class BundleActivator1 : public IRemoteBundleActivator
{
	private:
		IServiceRegistration* serviceReg1;
		MultiplierImpl* service1;

		IServiceRegistration* serviceReg2;
		MultiplierImpl* service2;

	public:
		virtual ~BundleActivator1();
		virtual void start( IRemoteBundleContext::ConstPtr context );	
		virtual void stop( IRemoteBundleContext::ConstPtr context );
};

#endif