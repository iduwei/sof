#include "IServiceRegistrationImpl.h"

using namespace sof::framework;
using namespace sof::util::logging;

Logger& IServiceRegistrationImpl::logger = LoggerFactory::getLogger( "Framework" );

IServiceRegistrationImpl::IServiceRegistrationImpl( const string& bName, IRegistry& reg, ServiceInfo& info ) : bundleName( bName ), registry( reg ), serviceInfo( info )
{
	logger.log( Logger::LOG_DEBUG, "[IServiceRegistrationImpl#ctor] Called." );
}
 
IServiceRegistrationImpl::~IServiceRegistrationImpl()
{
	logger.log( Logger::LOG_DEBUG, "[IServiceRegistrationImpl#destructor] Called." );
}

void IServiceRegistrationImpl::unregister()
{
	logger.log( Logger::LOG_DEBUG, "[IServiceRegistrationImpl#unregister] Called, service info: %1", this->serviceInfo.toString() );
	this->registry.removeServiceInfo( this->bundleName, this->serviceInfo );	
}