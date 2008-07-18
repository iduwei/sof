#include "BundleInfo.h"

#include <sstream>

using namespace std;

using namespace sof::framework;

Logger& BundleInfo::logger = LoggerFactory::getLogger( "Framework" );

BundleInfo::BundleInfo( const string& bdleName, IBundleActivator* act, IBundleContext::ConstPtr bundleCtxt ) : bundleName(bdleName), activator( act ), bundleContext( bundleCtxt )
{
	logger.log( Logger::DEBUG, "[BundleInfo#ctor] Called." );
}

BundleInfo::~BundleInfo()
{
	logger.log( Logger::DEBUG, "[BundleInfo#destructor] Called." );
}

string BundleInfo::getBundleName()
{
	return this->bundleName;
}

IBundleActivator* BundleInfo::getBundleActivator()
{
	return this->activator;
}

IBundleContext::ConstPtr BundleInfo::getBundleContext()
{
	return this->bundleContext;
}

void BundleInfo::addRegisteredService( ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfo#addRegisteredService] Called." );
	this->registeredServices.push_back( serviceInfo );
}

void BundleInfo::removeDeregisteredService( ServiceInfo* serviceInfo )
{	
	logger.log( Logger::DEBUG, "[BundleInfo#removeDeregisteredService] Called, service info: %1", serviceInfo->toString() );

	logger.log( Logger::DEBUG, "[BundleInfo#removeDeregisteredService] Iterate over vector of registered services." );					
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->registeredServices.begin(); iter != this->registeredServices.end(); iter++ )
	{
		if ( (*(*iter)) == (*serviceInfo) )
		{
			logger.log( Logger::DEBUG, "[BundleInfo#removeDeregisteredService] Service found." );	
			logger.log( Logger::DEBUG, "[BundleInfo#removeDeregisteredService] Delete service object." );					
			delete (*iter);
			logger.log( Logger::DEBUG, "[BundleInfo#removeDeregisteredService] Service object deleted." );									
			logger.log( Logger::DEBUG, "[BundleInfo#removeDeregisteredService] Remove element from vector of registered services." );					
			iter = this->registeredServices.erase( iter );		
			
			// TODO: Why breaking here?
			break;
		}
	}
}

void BundleInfo::removeUsedService( ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Called, service info: %1", serviceInfo->toString() );

	logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Iterate over vector of used services." );					
	
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->usedServices.begin(); iter != this->usedServices.end(); iter++ )
	{
		if ( (*(*iter)) == (*serviceInfo) )
		{
			logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Service found." );	
			logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Remove element from vector of used services." );					
			
			// TODO: Why not deleting object like in 'removeDeregisteredService'?
			iter = this->usedServices.erase( iter );
			
			// TODO: Why breaking here?
			break;
		}
	}		
}

void BundleInfo::removeAllUsedServices()
{
	logger.log( Logger::DEBUG, "[BundleInfo#removeAllUsedServices] Called." );				
	this->usedServices.clear();
}

void BundleInfo::removeUsedService( const string& serviceName )
{
	logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Called, service name: %1", serviceName );		
	logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Iterate over vector of used services." );					
	
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->usedServices.begin(); iter != this->usedServices.end(); iter++ )
	{
		if ( (*iter)->getServiceName() == serviceName )
		{
			logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Service found." );	
			logger.log( Logger::DEBUG, "[BundleInfo#removeUsedService] Remove element from vector of used services." );					
			
			iter = this->usedServices.erase( iter );
			break;
		}
	}		
}

void BundleInfo::addUsedService( ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfo#addUsedService] Called, service info: %1", serviceInfo->toString() );				
	this->usedServices.push_back( serviceInfo );
}

void BundleInfo::addRegisteredListener( ServiceListenerInfo* listenerInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfo#addRegisteredListener] Called, service listener info: %1", listenerInfo->toString() );					
	this->registeredListeners.push_back( listenerInfo );
}

void BundleInfo::removeRegisteredListener( ServiceListenerInfo* listenerInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfo#removeRegisteredListener] Called, service listener info: %1", 
		listenerInfo->toString() );		
	logger.log( Logger::DEBUG, "[BundleInfo#removeRegisteredListener] Iterate over vector of registered listeners." );					
	
	vector<ServiceListenerInfo*>::iterator iter;
	for ( iter = this->registeredListeners.begin(); iter != this->registeredListeners.end(); iter++ )
	{
		if ( (*(*iter)) == (*listenerInfo) )
		{
			logger.log( Logger::DEBUG, "[BundleInfo#removeRegisteredListener] Listener found." );	
			logger.log( Logger::DEBUG, "[BundleInfo#removeRegisteredListener] Delete service listener info object." );					
			
			delete (*iter);

			logger.log( Logger::DEBUG, "[BundleInfo#removeRegisteredListener] Listener info object deleted." );									
			logger.log( Logger::DEBUG, "[BundleInfo#removeRegisteredListener] Remove element from vector of registered listeners." );					
			
			this->registeredListeners.erase( iter );			
			return;
		}
	}
}

string BundleInfo::toString()
{
	ostringstream stream;
	stream << "*** Bundle: " << this->bundleName << " ****" << endl;
	
	stream << "*** Registered services ***" << endl;
	vector<ServiceInfo*>::iterator iter;
	for ( iter = registeredServices.begin(); iter != registeredServices.end(); iter++ )
	{
		stream << "  ->" << (*iter)->toString() << endl;
	}

	stream << "*** Services in use ***" << endl;
	for ( iter = usedServices.begin(); iter != usedServices.end(); iter++ )
	{
		stream << "  ->" << (*iter)->toString() << endl;
	}

	stream << "*** Registered service listener ***" << endl;
	vector<ServiceListenerInfo*>::iterator listenerIter;

	for ( listenerIter = registeredListeners.begin(); listenerIter != registeredListeners.end(); listenerIter++ )
	{
		stream << "  ->" << (*listenerIter)->toString() << endl;
	}
	stream << endl;	
	return stream.str();
}

vector<ServiceInfo*> BundleInfo::getRegisteredServices()
{
	return this->registeredServices;
}

vector<ServiceInfo*> BundleInfo::getUsedServices()
{
	return this->usedServices;
}

vector<ServiceListenerInfo*> BundleInfo::getRegisteredListeners()
{
	return this->registeredListeners;
}