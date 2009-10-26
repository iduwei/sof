#include "RemoteAdministrationActivator.h"

#include "sof/framework/Properties.h"
#include "sof/instantiation/ObjectCreator.h"
#include "sof/instantiation/NullCreator.h"
#include "sof/services/admin/IAdministrationServiceImpl.h"

using namespace sof::framework;
using namespace sof::services::admin;
using namespace sof::util::logging;
using namespace sof::instantiation;
using namespace sof::services::admin::remote;

Logger& RemoteAdministrationActivator::log = LoggerFactory::getLogger( "services" );

void RemoteAdministrationActivator::start( IRemoteBundleContext::ConstPtr context )
{
	log.log( Logger::DEBUG, "[RemoteAdministrationActivator#start] Called." );
	
	//Properties props;
	this->adminService = new IAdministrationServiceImpl( this->adminProvider );
	//this->serviceReg = context->registerService( "sof::services::admin::IAdministrationService", this->adminService, props );
	this->adminService->startConsole();
}

void RemoteAdministrationActivator::stop( IRemoteBundleContext::ConstPtr context )
{
	log.log( Logger::DEBUG, "[RemoteAdministrationActivator#stop] Called." );
	//this->serviceReg->unregister();
	//delete (this->serviceReg);
	//delete (this->adminService);
}

void RemoteAdministrationActivator::setAdministrationProvider( IAdministrationProvider* provider )
{
	log.log( Logger::DEBUG, "[RemoteAdministrationActivator#setLauncher] Called." );
	this->adminProvider = provider;
}

REGISTER_REMOTE_BUNDLE_ACTIVATOR_CLASS( "sof::services::admin::remote::RemoteAdministrationActivator", RemoteAdministrationActivator );

