#include "CORBARegistryImpl.h"

#include <CORBA.h>
#include <sstream>

using namespace sof::framework::remote::corba::registry;
using namespace sof::framework::remote::corba::generated;

Logger& CORBARegistryImpl::logger = LoggerFactory::getLogger( "Remote-Framework" );

void CORBARegistryImpl::addRegistryObserver( CORBARegistryObserver_ptr observer )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#addRegistryObserver] Called." );
	//RemoteRegistryObserver_var regObserver = RemoteRegistryObserver::_duplicate( observer );
	//regObserver->ping();
	this->objectVec.push_back( CORBARegistryObserver::_duplicate( observer ) );
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#addRegistryObserver] Left." );
}

void CORBARegistryImpl::registerService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerService] Entered." );
	vector<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectVec.begin(); iter != this->objectVec.end(); iter++ )
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerService] Forward registering service, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		try 
		{			
			(*iter)->registerService( bundleName, serviceName, CORBAService::_duplicate( service ), props );
		} catch( std::exception &exc )
		{
			cout << "---> error: " << exc.what() << endl;
		}
		catch(CORBA::Exception &cexc)
		{
			ostringstream s;
			cout << "----> corba exception error" << endl;
			cexc._print_stack_trace( s );
			cout << s.str() << endl;			
		}
		catch(...)
		{
			cout << "----> error" << endl;
		}
	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerService] Left." );
}

void CORBARegistryImpl::registerServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerServiceListener] Entered." );
	vector<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectVec.begin(); iter != this->objectVec.end(); iter++ )
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerServiceListener] Forward registering service listener, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		(*iter)->registerServiceListener( bundleName, serviceName, CORBAServiceListener::_duplicate( listener ) );
	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#registerServiceListener] Left." );
}

void CORBARegistryImpl::unregisterService( const char* bundleName, const char* serviceName, CORBAService_ptr service, const CORBAServiceProps& props )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterService] Entered." );
	vector<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectVec.begin(); iter != this->objectVec.end(); iter++ )
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterService] Forward unregistering service, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		(*iter)->unregisterService( bundleName, serviceName, service, props );
	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterService] Left." );
}

void CORBARegistryImpl::unregisterServiceListener( const char* bundleName, const char* serviceName, CORBAServiceListener_ptr listener )
{
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterServiceListener] Entered." );
	vector<CORBARegistryObserver_var>::iterator iter;
	for ( iter = this->objectVec.begin(); iter != this->objectVec.end(); iter++ )
	{
		logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterServiceListener] Forward unregistering service listener, bundle name: %1, service name: %2",
			string( bundleName ), string( serviceName) );
		(*iter)->unregisterServiceListener( bundleName, serviceName, CORBAServiceListener::_duplicate( listener ) );
	}
	logger.log( Logger::DEBUG, "[CORBARegistryImpl#unregisterServiceListener] Left." );
}
