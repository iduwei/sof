#include "CORBARegistryObserverImpl.h"

#include <CORBA.h>

#include "sof/util/memory/ScopeGuard.h"
#include "sof/framework/IServiceRegistrationImpl.h"

#include "../RemoteServiceInfo.h"
#include "../CORBAHelper.h"

using namespace sof::framework;
using namespace sof::util::memory;

using namespace sof::framework::remote::corba::registry;
using namespace sof::framework::remote::corba::generated;
using namespace sof::framework::remote::corba;

Logger& CORBARegistryObserverImpl::logger = LoggerFactory::getLogger( "Remote-Framework" );

CORBARegistryObserverImpl::CORBARegistryObserverImpl( IRegistry& reg, CORBAHelper& corbaHelperClass ) : registry( reg ), corbaHelper( corbaHelperClass )
{

}

CORBARegistryObserverImpl::~CORBARegistryObserverImpl()
{

}

void CORBARegistryObserverImpl::ping()
{
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#ping] Entered." );
}
void CORBARegistryObserverImpl::registerService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#registerService] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	RemoteServiceInfoPtr info = this->corbaHelper.convertToServiceInfo( serviceName, CORBAService::_duplicate( service ), const_cast<CORBAServiceProps&> (props) );
	// Note: addServiceInfo call returns NULL (for service registration object)
	this->registry.addServiceInfo( bName, info );
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#registerService] Left." );
}

void CORBARegistryObserverImpl::registerServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Converting service listener info." );	
	RemoteServiceListenerInfoPtr info = this->corbaHelper.convertToServiceListenerInfo( bName, sName, CORBAServiceListener::_duplicate( listener ) );
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Registering service listener." );	
	this->registry.addServiceListener( bName, info );
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Left." );
}

void CORBARegistryObserverImpl::unregisterService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#unregisterService] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	RemoteServiceInfoPtr info = this->corbaHelper.convertToServiceInfo( serviceName, CORBAService::_duplicate( service ), const_cast<CORBAServiceProps&> (props) );
	this->registry.removeServiceInfo( bName, info );
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#unregisterService] Left." );
}

void CORBARegistryObserverImpl::unregisterServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#unregisterServiceListener] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	RemoteServiceListenerInfoPtr info = this->corbaHelper.convertToServiceListenerInfo( bName, sName, CORBAServiceListener::_duplicate( listener ) );
	this->registry.removeServiceListener( bName, info );
	logger.log( Logger::LOG_DEBUG, "[CORBARegistryObserverImpl#unregisterServiceListener] Left." );
}
