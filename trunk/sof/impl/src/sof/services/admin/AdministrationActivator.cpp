#include "AdministrationActivator.h"

#include "IAdministrationServiceImpl.h"
#include "../../instantiation/ObjectCreator.h"

using namespace sof::services::admin;
using namespace sof::util::logging;
using namespace sof::instantiation;

Logger& AdministrationActivator::log = LoggerFactory::getLogger( "services" );

void AdministrationActivator::start( IBundleContext::ConstPtr context )
{
	log.log( Logger::DEBUG, "[AdministrationActivator#start] Called." );
	IAdministrationServiceImpl adminService( this->adminProvider );
	adminService.startConsole();
}

void AdministrationActivator::stop( IBundleContext::ConstPtr context )
{
	log.log( Logger::DEBUG, "[AdministrationActivator#stop] Called." );
}

void AdministrationActivator::setAdministrationProvider( IAdministrationProvider* provider )
{
	log.log( Logger::DEBUG, "[AdministrationActivator#setLauncher] Called." );
	this->adminProvider = provider;
}

REGISTER_CLASS( "sof::services::admin::AdministrationActivator", IBundleActivator, AdministrationActivator );

