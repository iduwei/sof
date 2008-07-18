#ifndef BUNDLE_ACTIVATOR2_H
#define BUNDLE_ACTIVATOR2_H

#include "sof/framework/IBundleActivator.h"
#include "sof/framework/IBundleContext.h"
#include "sof/framework/IServiceTrackerCustomizer.h"
#include "sof/framework/ServiceTracker.h"

#include "IServiceA.h"

using namespace sof::framework;

class BundleActivator2 : public IBundleActivator, public IServiceTrackerCustomizer
{
	private:
		ServiceTracker* tracker;
		IServiceA* service;

	public:
		virtual ~BundleActivator2();
		virtual void start( IBundleContext::ConstPtr context );	
		virtual void stop( IBundleContext::ConstPtr context );
		virtual bool addingService( const ServiceReference& ref );
		virtual void removedService( const ServiceReference& ref );
};

#endif