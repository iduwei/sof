#ifndef BUNDLE_ACTIVATOR2_H
#define BUNDLE_ACTIVATOR2_H

#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/remote/corba/IRemoteBundleContext.h"

#include "sof/framework/IServiceTrackerCustomizer.h"
#include "sof/framework/remote/corba/RemoteServiceTracker.h"

#include "Multiplier.h"

using namespace sof::framework::remote::corba;
using namespace sof::framework;

/**
 * Implements a test bundle and tracks services.
 */
class BundleActivator2 : public IRemoteBundleActivator, public IRemoteServiceTrackerCustomizer
{
	private:

		/**
		 * Tracks the test services of test bundle 1
		 */
		RemoteServiceTracker* tracker;


	public:

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
		 * Listener method is called when services are started.
		 */
		virtual bool addingService( const RemoteServiceReference& ref );

		/**
		 * Listener method is called when services were removed.
		 */
		virtual void removedService( const RemoteServiceReference& ref );
};

#endif