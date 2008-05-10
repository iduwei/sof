#ifndef TEST_BUNDLE_ACTIVATOR_H
#define TEST_BUNDLE_ACTIVATOR_H

#include "sof/framework/IBundleActivator.h"
#include "sof/framework/IBundleContext.h"
#include "sof/framework/IServiceRegistration.h"
#include "sof/framework/ServiceTracker.h"

#include "IServiceBImpl.h"

using namespace sof::framework;

class TestBundleActivator : public IBundleActivator, public IServiceTrackerCustomizer
{
	private:
		static ServiceTracker* tracker;
		static IBundleContext* context;
		static IServiceRegistration* serviceReg;
		IServiceBImpl serviceB;

	public:		
		virtual TestBundleActivator::~TestBundleActivator();
		virtual void start( IBundleContext::ConstPtr context );
		virtual void stop( IBundleContext::ConstPtr context );
		virtual bool addingService( const ServiceReference& ref );
		virtual void removedService( const ServiceReference& ref );
		static void unregisterServiceB();
		static void stopServiceListener();
};
#endif