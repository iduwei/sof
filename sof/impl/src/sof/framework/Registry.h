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

		void notifyListenersAboutRegisteredService( const string& bundleName, vector<ServiceInfo*>* serviceInfoVec, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName );
		void notifyListenersAboutRegisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec, const string& serviceName );
		
		void notifyListenersAboutDeregisteredService( const string& bundleName, ServiceInfo* serviceInfo, vector<ServiceListenerInfo*>* serviceListenerInfoVec );

		vector<ServiceInfo*>* addToServiceInfoVector( const string& serviceName, ServiceInfo* serviceInfo ) ;
		void removeFromServiceInfoVector( ServiceInfo* serviceInfo ) ;

		vector<ServiceListenerInfo*>* getServiceListenerInfoVector( const string& serviceName ) ;
		void removeFromServiceListenerInfoVector( const string& bundleName, IServiceListener::ConstPtr serviceListener );

		void addRegisteredServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) ;
		void removeDeregisteredServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo ) ;
		void addUsedServiceToBundleInfo( const string& bundleName, ServiceInfo* serviceInfo );
		void removeUsedServiceFromBundleInfo( const string& bundleName, ServiceInfo* serviceInfo );

	public:
		void addBundleInfo( BundleInfo* bundleInfo );
		BundleInfo* getBundleInfo( const string& bundleName );
		vector<BundleInfo*> getBundleInfos();
		void removeBundleInfo( const string& bundleName );
		void removeAllBundleInfos();

		void addServiceInfo( const string& bundleName, const string& serviceName, ServiceInfo* serviceInfo ) ;
		void removeServiceInfo( const string& bundleName, ServiceInfo* serviceInfo ) ;
		vector<ServiceInfo*>* getServiceInfo( const string &serviceName ) ;

		void addServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener, const string& serviceName ) ;
		void removeServiceListener( const string& bundleName, IServiceListener::ConstPtr serviceListener ) ;

};

}}
#endif