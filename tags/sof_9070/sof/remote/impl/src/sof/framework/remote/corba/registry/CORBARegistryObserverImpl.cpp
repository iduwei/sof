#include "CORBARegistryObserverImpl.h"

#include <CORBA.h>

#include "../RemoteServiceInfo.h"
#include "../CORBAHelper.h"

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
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#ping] Entered." );
}
void CORBARegistryObserverImpl::registerService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#registerService] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	RemoteServiceInfo& info = this->corbaHelper.convertToServiceInfo( serviceName, CORBAService::_duplicate( service ), props );
	this->registry.addServiceInfo( bName, &info );
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#registerService] Left." );
}

void CORBARegistryObserverImpl::registerServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Converting service listener info." );	
	RemoteServiceListenerInfo& info = this->corbaHelper.convertToServiceListenerInfo( bName, sName, CORBAServiceListener::_duplicate( listener ) );
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Registering service listener." );	
	this->registry.addServiceListener( bName, &info );
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#registerServiceListener] Left." );
}

void CORBARegistryObserverImpl::unregisterService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#unregisterService] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	RemoteServiceInfo& info = this->corbaHelper.convertToServiceInfo( serviceName, CORBAService::_duplicate( service ), props );
	this->registry.removeServiceInfo( bName, &info );
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#unregisterService] Left." );
}

void CORBARegistryObserverImpl::unregisterServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#unregisterServiceListener] Entered." );
	string bName( bundleName );
	string sName( serviceName );
	RemoteServiceListenerInfo& info = this->corbaHelper.convertToServiceListenerInfo( bName, sName, CORBAServiceListener::_duplicate( listener ) );
	this->registry.removeServiceListener( bName, info );
	logger.log( Logger::DEBUG, "[CORBARegistryObserverImpl#unregisterServiceListener] Left." );
}