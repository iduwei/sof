#include "TestBundleActivator.h"

#include <iostream>

#include "sof/framework/Properties.h"
#include "sof/instantiation/ObjectCreator.h"

#include "UnitTestLogger.h"

using namespace std;
using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::logging;

IBundleContext* TestBundleActivator::context = 0;
IServiceRegistration* TestBundleActivator::serviceReg = 0;

void TestBundleActivator::start( IBundleContext::ConstPtr ctxt )
{
	context = ctxt;
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] Called." );
	Properties props;
	props.put( "instance", "1" );

	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] Register ServiceB..." );	
	serviceReg = context->registerService( "ServiceB", &( this->serviceB ), props );
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] ServiceB registered." );	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#start] Left." );
}

TestBundleActivator::~TestBundleActivator()
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#destructor] Called." );	
}

void TestBundleActivator::stop( IBundleContext::ConstPtr context )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#stop] Called." );		
}

void TestBundleActivator::unregisterServiceB()
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[TestBundleActivator#unregisterServiceB] Called." );		
	serviceReg->unregister();
}

REGISTER_CLASS( "TestBundleActivator", IBundleActivator, TestBundleActivator )