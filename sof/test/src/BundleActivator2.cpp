#include "BundleActivator2.h"

#include <iostream>

#include "sof/framework/Properties.h"
#include "sof/classloading/Object.h"

#include "UnitTestLogger.h"

using namespace std;
using namespace sof::framework;
using namespace sof::classloading;
using namespace sof::util::logging;

IBundleContext* BundleActivator2::context = 0;
IServiceRegistration* BundleActivator2::serviceReg = 0;

void BundleActivator2::start( IBundleContext::ConstPtr ctxt )
{
	context = ctxt;
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivator2#start] Called." );
	Properties props;
	props.put( "instance", "1" );

	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivator2#start] Register ServiceB..." );	
	serviceReg = context->registerService( "ServiceB", &( this->serviceB ), props );
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivator2#start] ServiceB registered." );	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivator2#start] Left." );
}

BundleActivator2::~BundleActivator2()
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivator2#destructor] Called." );	
}

void BundleActivator2::stop( IBundleContext::ConstPtr context )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivator2#stop] Called." );		
}

void BundleActivator2::unregisterServiceB()
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[BundleActivator2#unregisterServiceB] Called." );		
	serviceReg->unregister();
}

REGISTER_CLASS( "BundleActivator2", IBundleActivator, BundleActivator2 )