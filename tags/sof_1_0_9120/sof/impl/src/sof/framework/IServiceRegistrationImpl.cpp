#include "IServiceRegistrationImpl.h"

using namespace sof::framework;
using namespace sof::util::logging;

Logger& IServiceRegistrationImpl::logger = LoggerFactory::getLogger( "Framework" );

IServiceRegistrationImpl::IServiceRegistrationImpl( const string& bName, IRegistry* const reg, ServiceInfo* const info ) : bundleName( bName ), registry( reg ), serviceInfo( info )
{
	logger.log( Logger::DEBUG, "[IServiceRegistrationImpl#ctor] Called." );
}
 
IServiceRegistrationImpl::~IServiceRegistrationImpl()
{
	logger.log( Logger::DEBUG, "[IServiceRegistrationImpl#destructor] Called." );
}

void IServiceRegistrationImpl::unregister()
{
	logger.log( Logger::DEBUG, "[IServiceRegistrationImpl#unregister] Called, service info: %1", this->serviceInfo->toString() );
	this->registry->removeServiceInfo( this->bundleName, this->serviceInfo );	
}