#ifndef BUNDLE_ACTIVATOR_2_H
#define BUNDLE_ACTIVATOR_2_H

#include "sof/framework/IBundleActivator.h"
#include "sof/framework/IBundleContext.h"
#include "sof/framework/IServiceRegistration.h"

#include "IServiceBImpl.h"

using namespace sof::framework;

class BundleActivator2 : public IBundleActivator
{
	private:
		static IBundleContext* context;
		static IServiceRegistration* serviceReg;
		IServiceBImpl serviceB;

	public:		
		virtual BundleActivator2::~BundleActivator2();
		virtual void start( IBundleContext::ConstPtr context );
		virtual void stop( IBundleContext::ConstPtr context );
		static void unregisterServiceB();
};
#endif