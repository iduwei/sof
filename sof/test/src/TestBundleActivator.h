#ifndef TEST_BUNDLE_ACTIVATOR_H
#define TEST_BUNDLE_ACTIVATOR_H

#include "sof/framework/IBundleActivator.h"
#include "sof/framework/IBundleContext.h"
#include "sof/framework/IServiceRegistration.h"

#include "IServiceBImpl.h"

using namespace sof::framework;

class TestBundleActivator : public IBundleActivator
{
	private:
		static IBundleContext* context;
		static IServiceRegistration* serviceReg;
		IServiceBImpl serviceB;

	public:		
		virtual TestBundleActivator::~TestBundleActivator();
		virtual void start( IBundleContext::ConstPtr context );
		virtual void stop( IBundleContext::ConstPtr context );
		static void unregisterServiceB();
};
#endif