#include "AdministrationActivator.h"
#include "IAdministrationServiceImpl.h"

using namespace sof::services::admin;
using namespace sof::util::logging;

Logger& AdministrationActivator::log = LoggerFactory::getLogger( "services" );

void AdministrationActivator::start( IBundleContext::ConstPtr context )
{
	log.log( Logger::DEBUG, "[AdministrationActivator#start] Called." );
	IAdministrationServiceImpl adminService( this->launcher );
	adminService.startConsole();
}

void AdministrationActivator::stop( IBundleContext::ConstPtr context )
{
	log.log( Logger::DEBUG, "[AdministrationActivator#stop] Called." );
}

void AdministrationActivator::setLauncher( Launcher* launch )
{
	log.log( Logger::DEBUG, "[AdministrationActivator#setLauncher] Called." );
	this->launcher = launch;
}

REGISTER_CLASS( "sof::services::admin::AdministrationActivator", IBundleActivator, AdministrationActivator );

