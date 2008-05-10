#ifndef REGISTRY_H
#define REGISTRY_H

#include <map>
#include <string>
#include <vector>

#include "BundleInfo.h"
#include "ServiceInfo.h"
#include "ServiceListenerInfo.h"
#include "IServiceListener.h"

#include "../util/logging/Logger.h"

namespace sof { namespace framework {

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;

/**
 * The central class (the 'brain') of the SOF framework which
 * stores and holds all relevant data of the bundles.<br>
 * The <code>Registry</code> class has the knowledge about
 * all registered service objects and service listeners for
 * example.<br>
 * The main tasks of the registry are:<br>* <ul>
 *		<li>Storing the information about started bundles wheres
 *			the bundle data consists of bundle name, activator object
 *			registered services and registered listeners.
 *		<li>Notifying the accordant service listener objects when 
 *			a new service object is registered or a service
 *			object is removed.<br>
 * </ul>
 */
class Registry 
{
	private:

		/**
		 * The logger instance.
		 */
		static Logger &logger;

		/**
		 * The vector storing <code>BundleInfo</code> objects
		 * which hold all bundle relevant data.
		 */
		vector<BundleInfo*> bundleInfoVec;

		/**
		 * Stores vectors of <code>ServiceInfo</code> objects 
		 * relating to the service name. <code>ServiceInfo</code>
		 * objects store the name of the service, the service object 
		 * and the service properties. There can be several services
		 * (several <code>ServiceInfo</code> objects) with the same 
		 * service name.
		 * 
		 */
		map<string, vector<ServiceInfo*>* > serviceInfoMap;

		/**
		 * Maps <code>ServiceListenerInfo</code>  objects to the
		 * service name. <code>ServiceListenerInfo</code> objects contain
		 * the service name they are listen for.
		 */
		map<string, vector<ServiceListenerInfo*>* > serviceListenerMap;		

		/**
		 * Notifies service listener objects about a specific service which was
		 * registered.<br>
		 * Is called when a new service listener object is registered.
		 *
		 * @param bundleName
		 *				The name of the bundle the registered service belongs to.
		 *
		 * @param serviceInfoVec
		 *				A vector of <code>ServiceInfo</code> objects which have all the same
		 *				service name.
		 * 
		 * @param serviceListenerInfoVec
		 *				A vector of <code>ServiceListenerInfo</code> objects containing the
		 *				service listener objects which are notified.
	     * 
		 * @param serviceName
		 *				The name of the service which is registered.
		 */
		void notifyListenersAboutRegisteredService( const string& bundleName, vector<ServiceInfo*>* serviceInfoVec, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName );

		/**
		 * Notifies service listener objects about a specific service which was
		 * registered.<br>
		 * Is called when a new service is registered.
		 *
		 * @param bundleName
		 *				The name of the bundle the registered service belongs to.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> object of the service which was registered.
		 * 
		 * @param serviceListenerInfoVec
		 *				A vector of <code>ServiceListenerInfo</code> objects containing the
		 *				service listener objects which are notified.
	     * 
		 * @param serviceName
		 *				The name of the service which is registered.
		 */
		void notifyListenersAboutRegisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName );

		/**
		 * Notifies service listener objects about a specific service which is
		 * deregistered.<br>
		 * Is called when a service is deregistered.
		 *
		 * @param bundleName
		 *				The name of the bundle the deregistered service belongs to.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> object of the service which is deregistered.
		 * 
		 * @param serviceListenerInfoVec
		 *				A vector of <code>ServiceListenerInfo</code> objects containing the
		 *				service listener objects which must be notified.
		 */
		void notifyListenersAboutDeregisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec );

		/**
		 * All registered service are cached by using <code>ServiceInfo</code> objects. This method
		 * adds a new <code>ServiceInfo</code> object to the internal storage.
		 *
		 * @param serviceName
		 *				The name of the service whose <code>ServiceInfo</code> object must be stored.
		 *
		 * @param serviceInfo
		 *				The object of type <code>ServiceInfo</code>.
		 */
		vector<ServiceInfo*>* addToServiceInfoVector( const string& serviceName, ServiceInfo* serviceInfo ) ;

		/**
		 * Removes a <code>ServiceInfo</code> object from the internal storage.
		 *
		 * @param serviceInfo
		 *				The service info object which is removed.
		 */
		void removeFromServiceInfoVector( ServiceInfo* serviceInfo ) ;

		/**
		 * Helper method which returns the vector of <code>ServiceListenerInfo</code>
		 * objects.
		 *
		 * @param serviceName
		 *				The service name the <code>ServiceListenerInfo</code> objects are mapped to.
		 */
		vector<ServiceListenerInfo*>* getServiceListenerInfoVector( const string& serviceName ) ;

		/**
		 * Removes a service listener info object from the internal storage.
		 * 
		 * @param bundleName
		 *				The name of the bundle the service listener belongs to.
		 *
		 * @param serviceListener
		 *				The service listener object.
		 */
		void removeFromServiceListenerInfoVector( const string& bundleName, IServiceListener::ConstPtr serviceListener );

		/**
		 * Adds a <code>ServiceInfo</code> object to the bundle info storage.<br>
		 * The <code>BundleInfo</code> object contains all relevant information of
		 * a bundle (like information about registered services).
		 * 
		 * @param bundleName
		 *				The name of the bundle the registered service belongs to.
		 *
		 * @param serviceInfo
		 *				The service info object which is stored.
		 */
		void addRegisteredServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) ;

		/**
		 * Removes a <code>ServiceInfo</code> object from the bundle info storage.<br>
		 * The <code>BundleInfo</code> object contains all relevant information of
		 * a bundle (like information about registered services).
		 * 
		 * @param bundleName
		 *				The name of the bundle the deregistered service belongs to.
		 *
		 * @param serviceInfo
		 *				The service info object which is removed.
		 */
		void removeDeregisteredServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) ;

		/**
		 * Adds a <code>ServiceInfo</code> object representing a used service to the bundle
		 * info object.
		 *
		 * @param bundleName
		 *				The name of the bundle which uses the specified service.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> object representing a service
		 *				which is used by the specified bundle.
		 */
		void addUsedServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo );
		
		/**
		 * Removes a <code>ServiceInfo</code> object representing a used service from the bundle
		 * info object.
		 *
		 * @param bundleName
		 *				The name of the bundle which used the specified service.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> object representing a service
		 *				which was used by the specified bundle.
		 */
		void removeUsedServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo );

	public:

		/**
		 * Adds a <code>BundleInfo</code> object to the registry.
		 *
		 * @param bundleInfo
		 *			The <code>BundleInfo</code> object which describes a bundle.
		 */
		void addBundleInfo( BundleInfo* bundleInfo );

		/**
		 * Returns the <code>BundleInfo</code> object of a specific bundle.
		 *
		 * @param  bundleName
		 *				The name of the bundle whose bundle info object is returned.
		 *
		 * @return	The <code>BundleInfo</code> object.
		 */
		BundleInfo* getBundleInfo( const string& bundleName );

		/**
		 * Returns all <code>BundleInfo</code> objects which are currently
		 * stored in registry.
		 *
		 * @return	A vector of <code>BundleInfo</code> objects.
		 *
		 */
		vector<BundleInfo*> getBundleInfos();

		/**
		 * Removes the <code>BundleInfo</code> object of a specific bundle.
		 *
		 * @param bundleName
		 *				The name of the bundle whose bundle info object is removed.
		 */
		void removeBundleInfo( const string& bundleName );

		/**
		 * Removes all <code>BundleInfo</code> objects which are currently
		 * stored in registry.		 
		 */
		void removeAllBundleInfos();

		/**
		 * Adds a <code>ServiceInfo</code> object to the registry.
		 *
		 * @param bundleName
		 *				The name of the bundle the service belongs to.
		 *
		 * @param serviceName
		 *				The name of the service.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> object describing the service.
		 */
		void addServiceInfo( const string& bundleName, const string& serviceName, ServiceInfo* serviceInfo ) ;
		
		/**
		 * Removes a <code>ServiceInfo</code> object from the registry.
		 *
		 * @param bundleName
		 *				The name of the bundle the service belongs to.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> object describing the service.
		 */
		void removeServiceInfo( const string& bundleName, ServiceInfo* serviceInfo ) ;

		/**
		 * Returns the <code>ServiceInfo</code> object for a specific service.
		 *
		 * @param serviceName
		 *				The name of the service.
		 *
		 * @return A pointer to a vector of pointers to <code>ServiceInfo</code> objects.
		 */
		vector<ServiceInfo*>* getServiceInfo( const string &serviceName ) ;

		/**
		 * Adds a service listener object to the registry.
		 *
		 * @param bundleName
		 *				The name of the bundle the service listener belongs to.
		 *
		 * @param serviceListener
		 *				The pointer to the service listener object.
		 *
		 * @param serviceName
		 *				The name of the service.
		 */
		void addServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener, const string& serviceName ) ;
		
		/**
		 * Removes a service listener object from the registry.
		 *
		 * @param bundleName
		 *				The name of the bundle the service listener belongs to.
		 *
		 * @param serviceListener
		 *				The pointer to the service listener object.
		 */
		void removeServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener ) ;

};

}}
#endif