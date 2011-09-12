#ifndef BUNDLE_ACTIVATOR1_H
#define BUNDLE_ACTIVATOR1_H

#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/remote/corba/IRemoteBundleContext.h"
#include "sof/framework/remote/corba/LocalServiceTracker.h"

#include "sof/framework/IServiceRegistration.h"

#include "MultiplierImpl.h"

using namespace sof::framework::remote::corba;

class BundleActivator1 : public IRemoteBundleActivator, ILocalServiceTrackerCustomizer
{
	private:
		IServiceRegistration* serviceReg1;
		MultiplierImpl* service1;

		IServiceRegistration* serviceReg2;
		MultiplierImpl* service2;

		LocalServiceTracker* tracker;

	public:
		BundleActivator1();
		virtual ~BundleActivator1();
		virtual void start( IRemoteBundleContext::ConstPtr context );	
		virtual void stop( IRemoteBundleContext::ConstPtr context );
		virtual bool addingService( const ServiceReference& ref );
		virtual void removedService( const ServiceReference& ref );
};

#endif
