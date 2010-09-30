#include "BundleInfoBase.h"

#include <sstream>

using namespace std;

using namespace sof::framework;

Logger& BundleInfoBase::logger = LoggerFactory::getLogger( "Framework" );

BundleInfoBase::BundleInfoBase( const string& bdleName, IBundleContext::ConstPtr bundleCtxt ) : bundleName(bdleName), bundleContext( bundleCtxt )
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#ctor] Called." );
}

BundleInfoBase::~BundleInfoBase()
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#destructor] Called." );
}

string BundleInfoBase::getBundleName() const
{
	return this->bundleName;
}

IBundleContext::ConstPtr BundleInfoBase::getBundleContext()
{
	return this->bundleContext;
}

void BundleInfoBase::addRegisteredService( ServiceInfo& serviceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#addRegisteredService] Called." );
	this->registeredServices.push_back( &serviceInfo );
}

void BundleInfoBase::removeDeregisteredService( const ServiceInfo& serviceInfo )
{	
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeDeregisteredService] Called, service info: %1", serviceInfo.toString() );

	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeDeregisteredService] Iterate over vector of registered services." );					
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->registeredServices.begin(); iter != this->registeredServices.end(); ++iter )
	{
		if ( (*iter)->equals( (*(*iter)), serviceInfo ) )
		{
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeDeregisteredService] Service found." );	
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeDeregisteredService] Delete service object." );	
			delete (*iter);
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeDeregisteredService] Service object deleted." );									
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeDeregisteredService] Remove element from vector of registered services." );					
			iter = this->registeredServices.erase( iter );		
			
			// TODO: Why breaking here?
			break;
		}
	}
}

void BundleInfoBase::removeUsedService( const ServiceInfo& serviceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Called, service info: %1", serviceInfo.toString() );

	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Iterate over vector of used services." );					
	
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->usedServices.begin(); iter != this->usedServices.end(); ++iter )
	{
		if ( (*(*iter)) == serviceInfo )
		{
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Service found." );	
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Remove element from vector of used services." );					
			
			// TODO: Why not deleting object like in 'removeDeregisteredService'?
			iter = this->usedServices.erase( iter );
			
			// TODO: Why breaking here?
			break;
		}
	}		
}

void BundleInfoBase::removeAllUsedServices()
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeAllUsedServices] Called." );				
	this->usedServices.clear();
}

void BundleInfoBase::removeUsedService( const string& serviceName )
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Called, service name: %1", serviceName );		
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Iterate over vector of used services." );					
	
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->usedServices.begin(); iter != this->usedServices.end(); ++iter )
	{
		if ( (*iter)->getServiceName() == serviceName )
		{
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Service found." );	
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeUsedService] Remove element from vector of used services." );					
			
			iter = this->usedServices.erase( iter );
			break;
		}
	}		
}


void BundleInfoBase::addUsedService( ServiceInfo& serviceInfo )
{
	// Bugfix: [Remote SOF] Services are listed double as used services - ID: 2821783
	// Note:
	//	- 'addUsedService' could be call twice (in RemoteServiceTracker and in registry)
	//		for the same service info object, therefore double entries have to be avoided
	
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#addUsedService] Called, service info: %1", serviceInfo.toString() );

	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#addUsedService] Check whether service info is already cached in vector." );					
	
	vector<ServiceInfo*>::iterator iter;
	for ( iter = this->usedServices.begin(); iter != this->usedServices.end(); ++iter )
	{
		if ( (*(*iter)) == serviceInfo )
		{
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#addUsedService] Service already cached, do not put it once again!" );					
			return;
		}
	}	
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#addUsedService] Put service info into vector." );								
	this->usedServices.push_back( &serviceInfo );
}

void BundleInfoBase::addRegisteredListener( ServiceListenerInfo& listenerInfo )
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#addRegisteredListener] Called, service listener info: %1", listenerInfo.toString() );					
	this->registeredListeners.push_back( &listenerInfo );
}

void BundleInfoBase::removeRegisteredListener( const ServiceListenerInfo& listenerInfo )
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeRegisteredListener] Called, service listener info: %1", 
		listenerInfo.toString() );		
	logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeRegisteredListener] Iterate over vector of registered listeners." );					
	
	vector<ServiceListenerInfo*>::iterator iter;
	for ( iter = this->registeredListeners.begin(); iter != this->registeredListeners.end(); ++iter )
	{
		if ( (*iter)->equals( listenerInfo, (*(*iter )) )   )
		{
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeRegisteredListener] Listener found." );	
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeRegisteredListener] Delete service listener info object." );					

			delete (*iter);

			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeRegisteredListener] Listener info object deleted." );									
			logger.log( Logger::LOG_DEBUG, "[BundleInfoBase#removeRegisteredListener] Remove element from vector of registered listeners." );					
			
			this->registeredListeners.erase( iter );			
			return;
		}
	}
}

string BundleInfoBase::toString() const
{
	ostringstream stream;
	stream << "*** Bundle: " << this->bundleName << " ****" << endl;
	
	stream << "*** Registered services ***" << endl;
	vector<ServiceInfo*>::const_iterator iter;
	
	for ( iter = registeredServices.begin(); iter != registeredServices.end(); ++iter )
	{
		stream << "  ->" << (*iter)->toString() << endl;
	}

	stream << "*** Services in use ***" << endl;
	for ( iter = usedServices.begin(); iter != usedServices.end(); ++iter )
	{
		stream << "  ->" << (*iter)->toString() << endl;
	}

	stream << "*** Registered service listener ***" << endl;
	vector<ServiceListenerInfo*>::const_iterator listenerIter;

	for ( listenerIter = registeredListeners.begin(); listenerIter != registeredListeners.end(); ++listenerIter )
	{
		stream << "  ->" << (*listenerIter)->toString() << endl;
	}
	stream << endl;	
	return stream.str();
}

vector<ServiceInfo*> BundleInfoBase::getRegisteredServices() const
{
	return this->registeredServices;
}

vector<ServiceInfo*> BundleInfoBase::getUsedServices() const
{
	return this->usedServices;
}

vector<ServiceListenerInfo*> BundleInfoBase::getRegisteredListeners() const
{
	return this->registeredListeners;
} 