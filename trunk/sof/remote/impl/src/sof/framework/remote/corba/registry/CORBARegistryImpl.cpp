#include "CORBARegistryImpl.h"

#include <CORBA.h>
#include <sstream>

using namespace sof::framework::remote::corba::registry;
using namespace sof::framework::remote::corba::generated;

Logger& CORBARegistryImpl::logger = LoggerFactory::getLogger( "Remote-Framework" );

void CORBARegistryImpl::addRegistryObserver( CORBARegistryObserver_ptr observer )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#addRegistryObserver] Called." );
	this->objectList.push_back( CORBARegistryObserver::_duplicate( observer ) );
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#addRegistryObserver] Left." );
}

void CORBARegistryImpl::registerService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerService] Entered." );
	list<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectList.begin(); iter != this->objectList.end();)
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerService] Forward registering service, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		try 
		{			
			(*iter)->registerService( bundleName, serviceName, CORBAService::_duplicate( service ), props );
			++iter;
		} 
		catch( std::exception &exc )
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#registerService] std::exception occurred: %1", string( exc.what() ) );
			iter = this->objectList.erase( iter );
		}
		catch(CORBA::Exception &cexc)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#registerService] CORBA::Exception occurred: %1", string( cexc._repoid() ) );
			iter = this->objectList.erase( iter );
		}
		catch(...)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#registerService] Exception occurred." );
			iter = this->objectList.erase( iter );
		}
	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerService] Left." );
}

void CORBARegistryImpl::registerServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerServiceListener] Entered." );
	list<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectList.begin(); iter != this->objectList.end();)
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerServiceListener] Forward registering service listener, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		try
		{
			(*iter)->registerServiceListener( bundleName, serviceName, CORBAServiceListener::_duplicate( listener ) );
			++iter;
		}
		catch( std::exception &exc )
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#registerServiceListener] std::exception occurred: %1", string( exc.what() ) );
			iter = this->objectList.erase( iter );
		}
		catch(CORBA::Exception &cexc)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#registerServiceListener] CORBA::Exception occurred: %1", string( cexc._repoid() ) );
			iter = this->objectList.erase( iter );
		}
		catch(...)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#registerServiceListener] Exception occurred." );
			iter = this->objectList.erase( iter );
		}

	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerServiceListener] Left." );
}

void CORBARegistryImpl::unregisterService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterService] Entered." );
	list<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectList.begin(); iter != this->objectList.end();)
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterService] Forward unregistering service, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		try
		{
			(*iter)->unregisterService( bundleName, serviceName, service, props );
			++iter;
		}
		catch( std::exception &exc )
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#unregisterService] std::exception occurred: %1", string( exc.what() ) );
			iter = this->objectList.erase( iter );
		}
		catch(CORBA::Exception &cexc)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#unregisterService] CORBA::Exception occurred: %1", string( cexc._repoid() ) );
			iter = this->objectList.erase( iter );
		}
		catch(...)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#unregisterService] Exception occurred." );
			iter = this->objectList.erase( iter );
		}
	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterService] Left." );
}

void CORBARegistryImpl::unregisterServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterServiceListener] Entered." );
	list<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectList.begin(); iter != this->objectList.end();)
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterServiceListener] Forward unregistering service listener, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		try
		{
			(*iter)->unregisterServiceListener( bundleName, serviceName, CORBAServiceListener::_duplicate( listener ) );
			++iter;
		}
		catch( std::exception &exc )
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#unregisterServiceListener] std::exception occurred: %1", string( exc.what() ) );
			iter = this->objectList.erase( iter );
		}
		catch(CORBA::Exception &cexc)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#unregisterServiceListener] CORBA::Exception occurred: %1", string( cexc._repoid() ) );
			iter = this->objectList.erase( iter );
		}
		catch(...)
		{
			logger.log( Logger::ERROR_, "[CORBARegistryImpl#unregisterServiceListener] Exception occurred." );
			iter = this->objectList.erase( iter );
		}
	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterServiceListener] Left." );
}
