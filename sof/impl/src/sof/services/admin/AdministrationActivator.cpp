#include "AdministrationActivator.h"

#include "../../framework/Properties.h"
#include "../../instantiation/ObjectCreator.h"
#include "../../instantiation/NullCreator.h"

#include "IAdministrationServiceImpl.h"

using namespace sof::framework;
using namespace sof::services::admin;
using namespace sof::util::logging;
using namespace sof::instantiation;

Logger& AdministrationActivator::log = LoggerFactory::getLogger( "services" );

AdministrationActivator::AdministrationActivator()
{
	log.log( Logger::LOG_DEBUG, "[AdministrationActivator#ctor] Called." );
	this->adminProvider = 0;
	this->adminService = 0;
	this->serviceReg = 0;
}

void AdministrationActivator::start( IBundleContext::ConstPtr context )
{
	log.log( Logger::LOG_DEBUG, "[AdministrationActivator#start] Called." );
	Properties props;
	this->adminService = new IAdministrationServiceImpl( this->adminProvider );
	this->serviceReg = context->registerService( "sof::services::admin::IAdministrationService", this->adminService, props );
	this->adminService->startConsole();
}

void AdministrationActivator::stop( IBundleContext::ConstPtr context )
{
	log.log( Logger::LOG_DEBUG, "[AdministrationActivator#stop] Called." );
	this->serviceReg->unregister();
	delete (this->serviceReg);
	delete (this->adminService);
}

void AdministrationActivator::setAdministrationProvider( IAdministrationProvider* provider )
{
	log.log( Logger::LOG_DEBUG, "[AdministrationActivator#setLauncher] Called." );
	this->adminProvider = provider;
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( "sof::services::admin::AdministrationActivator", AdministrationActivator );

