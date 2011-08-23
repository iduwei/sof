#ifndef BUNDLE_ACTIVATOR2_H
#define BUNDLE_ACTIVATOR2_H

#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/remote/corba/IRemoteBundleContext.h"

#include "sof/framework/IServiceTrackerCustomizer.h"
#include "sof/framework/remote/corba/RemoteServiceTracker.h"
#include "sof/framework/remote/corba/LocalServiceTracker.h"
#include "sof/framework/remote/corba/ILocalServiceTrackerCustomizer.h"

#include "Multiplier.h"
#include "IDividerImpl.h"

using namespace sof::framework::remote::corba;
using namespace sof::framework;

/**
 * Implements a test bundle and tracks services.
 */
class BundleActivator2 : public IRemoteBundleActivator, public IRemoteServiceTrackerCustomizer,
	public ILocalServiceTrackerCustomizer
{
	private:

		/**
		 * Tracks the test services of test bundle 1
		 */
		RemoteServiceTracker* tracker;

		/**
		 * The registration object of service 1.
		 */
		IServiceRegistration* serviceReg1;

		/**
		 * Local service instance 1.
		 */
		IDividerImpl* service1;

		/**
		 * The registration object of service 1.
		 */
		IServiceRegistration* serviceReg2;

		/**
		 * Local service instance 1.
		 */
		IDividerImpl* service2;

		/**
		 * Tracks local services.
		 */
		LocalServiceTracker* localTracker;

	public:

		/** 
		 * Creates instances of class <code>BundleActivator2</code>.
		 */
		BundleActivator2();

		/**
		 * Destroys the test bundle.
		 */
		virtual ~BundleActivator2();

		/**
		 * Starts the test bundle.
		 */
		virtual void start( IRemoteBundleContext::ConstPtr context );	
		
		/**
		 * Stops the test bundle.
		 */
		virtual void stop( IRemoteBundleContext::ConstPtr context );

		/**
		 * Listener method is called when remote services are started.
		 */
		virtual bool addingService( const RemoteServiceReference& ref );

		/**
		 * Listener method is called when remote services were removed.
		 */
		virtual void removedService( const RemoteServiceReference& ref );

		/**
		 * Listener method is called when local services were started.
		 */
		virtual bool addingService( const ServiceReference& ref );

		/**
		 * Listener method is called when local services were removed.
		 */
		virtual void removedService( const ServiceReference& ref );
};

#endif
