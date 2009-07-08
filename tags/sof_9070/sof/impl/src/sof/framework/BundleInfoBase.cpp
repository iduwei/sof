#include "BundleInfoBase.h"

#include <sstream>

using namespace std;

using namespace sof::framework;

Logger& BundleInfoBase::logger = LoggerFactory::getLogger( "Framework" );

BundleInfoBase::BundleInfoBase( const string& bdleName, IBundleContext::ConstPtr bundleCtxt ) : bundleName(bdleName), bundleContext( bundleCtxt )
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#ctor] Called." );
}

BundleInfoBase::~BundleInfoBase()
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#destructor] Called." );
}

string BundleInfoBase::getBundleName()
{
	return this->bundleName;
}

IBundleContext::ConstPtr BundleInfoBase::getBundleContext()
{
	return this->bundleContext;
}

void BundleInfoBase::addRegisteredService( ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#addRegisteredService] Called." );
	this->registeredServices.push_back( serviceInfo );
}

void BundleInfoBase::removeDeregisteredService( ServiceInfo* serviceInfo )
{	
	logger.log( Logger::DEBUG, "[BundleInfoBase#removeDeregisteredService] Called, service info: %1", serviceInfo->toString() );

	logger.log( Logger::DEBUG, "[BundleInfoBase#removeDeregisteredService] Iterate over vector of registered services." );					
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->registeredServices.begin(); iter != this->registeredServices.end(); iter++ )
	{
		if ( (*iter)->equals( (*(*iter)), (*serviceInfo) ) )
		{
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeDeregisteredService] Service found." );	
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeDeregisteredService] Delete service object." );					
			delete (*iter);
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeDeregisteredService] Service object deleted." );									
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeDeregisteredService] Remove element from vector of registered services." );					
			iter = this->registeredServices.erase( iter );		
			
			// TODO: Why breaking here?
			break;
		}
	}
}

void BundleInfoBase::removeUsedService( ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Called, service info: %1", serviceInfo->toString() );

	logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Iterate over vector of used services." );					
	
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->usedServices.begin(); iter != this->usedServices.end(); iter++ )
	{
		if ( (*(*iter)) == (*serviceInfo) )
		{
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Service found." );	
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Remove element from vector of used services." );					
			
			// TODO: Why not deleting object like in 'removeDeregisteredService'?
			iter = this->usedServices.erase( iter );
			
			// TODO: Why breaking here?
			break;
		}
	}		
}

void BundleInfoBase::removeAllUsedServices()
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#removeAllUsedServices] Called." );				
	this->usedServices.clear();
}

void BundleInfoBase::removeUsedService( const string& serviceName )
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Called, service name: %1", serviceName );		
	logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Iterate over vector of used services." );					
	
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->usedServices.begin(); iter != this->usedServices.end(); iter++ )
	{
		if ( (*iter)->getServiceName() == serviceName )
		{
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Service found." );	
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeUsedService] Remove element from vector of used services." );					
			
			iter = this->usedServices.erase( iter );
			break;
		}
	}		
}

void BundleInfoBase::addUsedService( ServiceInfo* serviceInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#addUsedService] Called, service info: %1", serviceInfo->toString() );				
	this->usedServices.push_back( serviceInfo );
}

void BundleInfoBase::addRegisteredListener( ServiceListenerInfo* listenerInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#addRegisteredListener] Called, service listener info: %1", listenerInfo->toString() );					
	this->registeredListeners.push_back( listenerInfo );
}

void BundleInfoBase::removeRegisteredListener( ServiceListenerInfo* listenerInfo )
{
	logger.log( Logger::DEBUG, "[BundleInfoBase#removeRegisteredListener] Called, service listener info: %1", 
		listenerInfo->toString() );		
	logger.log( Logger::DEBUG, "[BundleInfoBase#removeRegisteredListener] Iterate over vector of registered listeners." );					
	
	vector<ServiceListenerInfo*>::iterator iter;
	for ( iter = this->registeredListeners.begin(); iter != this->registeredListeners.end(); iter++ )
	{
		if ( (*(*iter)).equals( (*listenerInfo), (*(*iter) ) )   )
		{
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeRegisteredListener] Listener found." );	
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeRegisteredListener] Delete service listener info object." );					
			
			delete (*iter);

			logger.log( Logger::DEBUG, "[BundleInfoBase#removeRegisteredListener] Listener info object deleted." );									
			logger.log( Logger::DEBUG, "[BundleInfoBase#removeRegisteredListener] Remove element from vector of registered listeners." );					
			
			this->registeredListeners.erase( iter );			
			return;
		}
	}
}

string BundleInfoBase::toString()
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

vector<ServiceInfo*> BundleInfoBase::getRegisteredServices()
{
	return this->registeredServices;
}

vector<ServiceInfo*> BundleInfoBase::getUsedServices()
{
	return this->usedServices;
}

vector<ServiceListenerInfo*> BundleInfoBase::getRegisteredListeners()
{
	return this->registeredListeners;
} 