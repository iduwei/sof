#ifndef BUNDLE_ACTIVATOR2_H
#define BUNDLE_ACTIVATOR2_H

#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/remote/corba/IRemoteBundleContext.h"

#include "sof/framework/remote/corba/RemoteServiceTracker.h"

#include "Multiplier.h"
#include "IDividerImpl.h"

using namespace sof::framework::remote::corba;
using namespace sof::framework;

class BundleActivator2 : public IRemoteBundleActivator, public IRemoteServiceTrackerCustomizer
{
	private:
		RemoteServiceTracker* tracker;
		Multiplier_var service;

		IServiceRegistration* serviceReg1;
		IDividerImpl* service1;

		IServiceRegistration* serviceReg2;
		IDividerImpl* service2;

	public:
		BundleActivator2();
		virtual ~BundleActivator2();
		virtual void start( IRemoteBundleContext::ConstPtr context );	
		virtual void stop( IRemoteBundleContext::ConstPtr context );
		virtual bool addingService( const RemoteServiceReference& ref );
		virtual void removedService( const RemoteServiceReference& ref );
};

#endif
