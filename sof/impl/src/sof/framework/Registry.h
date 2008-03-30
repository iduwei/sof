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

class Registry 
{
	private:
		static Logger &logger;
		vector<BundleInfo*> bundleInfoVec;
		map<string, vector<ServiceInfo*>* > serviceInfoMap;
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