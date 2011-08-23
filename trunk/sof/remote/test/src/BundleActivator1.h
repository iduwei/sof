#ifndef BUNDLE_ACTIVATOR1_H
#define BUNDLE_ACTIVATOR1_H

#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/remote/corba/IRemoteBundleContext.h"
#include "sof/framework/remote/corba/IRemoteServiceTrackerCustomizer.h"
#include "sof/framework/IServiceRegistration.h"
#include "sof/framework/remote/corba/RemoteServiceTracker.h"
#include "sof/framework/remote/corba/LocalServiceTracker.h"
#include "sof/framework/remote/corba/ILocalServiceTrackerCustomizer.h"

#include "MultiplierImpl.h"

using namespace sof::framework::remote::corba;

/**
 * Implements a test bundle and registers services.
 */
class BundleActivator1 : public IRemoteBundleActivator, public IRemoteServiceTrackerCustomizer,
	public ILocalServiceTrackerCustomizer
{
	private:

		/**
		 * Tracks the test services.
		 */
		RemoteServiceTracker* tracker;

		/**
		 * Tracks local services.
		 */
		LocalServiceTracker* localTracker;

		/**
		 * The registration object of service 1.
		 */
		IServiceRegistration* serviceReg1;

		/**
		 * Service instance 1.
		 */
		MultiplierImpl* service1;

		/**
		 * The registration object of service 1.
		 */
		IServiceRegistration* serviceReg2;
		
		/**
		 * Service instance 1.
		 */
		MultiplierImpl* service2;

	public:

		/** 
		 * Creates instances of class <code>BundleActivator2</code>.
		 */
		BundleActivator1();

		/**
		 * Destroys the bundle activator object.
		 */
		virtual ~BundleActivator1();
		
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
