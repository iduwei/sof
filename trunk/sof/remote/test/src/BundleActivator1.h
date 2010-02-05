#ifndef BUNDLE_ACTIVATOR1_H
#define BUNDLE_ACTIVATOR1_H

#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/remote/corba/IRemoteBundleContext.h"

#include "sof/framework/IServiceRegistration.h"

#include "MultiplierImpl.h"

using namespace sof::framework::remote::corba;

/**
 * Implements a test bundle and registers services.
 */
class BundleActivator1 : public IRemoteBundleActivator
{
	private:

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
};

#endif