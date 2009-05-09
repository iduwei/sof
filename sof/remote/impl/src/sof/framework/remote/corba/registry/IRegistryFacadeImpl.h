#ifndef IREGISTRY_FACADE_IMPL_H
#define IREGISTRY_FACADE_IMPL_H

#include "sof/framework/IRegistry.h"
#include "sof/framework/BundleInfo.h"
#include "sof/framework/ServiceInfo.h"
#include "sof/framework/ServiceListenerInfo.h"
#include "sof/framework/IServiceRegistration.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"

#include "../CORBAHelper.h"
#include "../generated/CORBAObjects.h"
#include "CORBARegistryObserverImpl.h"

namespace sof { namespace framework { namespace remote { namespace corba { namespace registry {

using namespace sof::framework;
using namespace sof::framework::remote::corba;
using namespace sof::framework::remote::corba::generated;

/**
 * The <code>IRegistryFacadeImpl</code> implements the <code>IRegistry</code> interface and has
 * access to the remote registry component and to the local registry. It decides which registry 
 * calls have to be forwarded to the remote registry and to the local registry.
 */
class IRegistryFacadeImpl : public IRegistry
{
	private:

		/**
		 * The logger instance.
		 */
		static Logger& logger;
		
		/**
		 * The local registry.
		 */
		IRegistry& registry;

		/**
		 * Helper class for CORBA related calls.
		 */
		CORBAHelper& corbaHelper;

		/**
		 * The remote registry component where registered services
		 * and service listeners are forwarded to for example.
		 */
		CORBARegistry_var remoteRegistry;

		/**
		 * The remote registry observer component which receives register
		 * calls from the remote registry.
		 */
		CORBA::Object_var remoteRegistryObserver;

		/**
		 * The implementation class of the remote registry observer component.
		 */
		CORBARegistryObserverImpl* regObserver;

		/**
		 * Initializes the object.
		 */
		virtual void init();

	public:

		/**
		 * Creates instances of class <code>IRegistryFacadeImpl</code>.
		 *
		 * @param corbaHelper
		 *				The CORBA helper class.
		 *
		 * @param registry
		 *				The local registry object.
		 */
		IRegistryFacadeImpl( CORBAHelper& corbaHelper, IRegistry& registry );

		/**
		 * Destroys objects of type <code>IRegistryFacadeImpl</code>.
		 */
		virtual ~IRegistryFacadeImpl();		

		/**
		 * Adds a <code>BundleInfo</code> object to the registry.
		 *
		 * @param bundleInfo
		 *			The <code>BundleInfo</code> object which describes a bundle.
		 */
		virtual void addBundleInfo( BundleInfoBase* bundleInfo );

		/**
		 * Returns the <code>BundleInfo</code> object of a specific bundle.
		 *
		 * @param  bundleName
		 *				The name of the bundle whose bundle info object is returned.
		 *
		 * @return	The <code>BundleInfo</code> object.
		 */
		virtual BundleInfoBase* getBundleInfo( const string& bundleName );

		/**
		 * Returns all <code>BundleInfo</code> objects which are currently
		 * stored in registry.
		 *
		 * @return	A vector of <code>BundleInfo</code> objects.
		 *
		 */
		virtual vector<BundleInfoBase*> getBundleInfos();

		/**
		 * Removes the <code>BundleInfo</code> object of a specific bundle.
		 *
		 * @param bundleName
		 *				The name of the bundle whose bundle info object is removed.
		 */
		virtual void removeBundleInfo( const string& bundleName );

		/**
		 * Removes all <code>BundleInfo</code> objects which are currently
		 * stored in registry.		 
		 */
		virtual void removeAllBundleInfos();

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
		virtual IServiceRegistration::ConstPtr addServiceInfo( const string& bundleName, ServiceInfo* serviceInfo );
		
		/**
		 * Removes a <code>ServiceInfo</code> object from the registry.
		 *
		 * @param bundleName
		 *				The name of the bundle the service belongs to.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> object describing the service.
		 */
		virtual void removeServiceInfo( const string& bundleName, ServiceInfo* serviceInfo );

		/**
		 * Returns the <code>ServiceInfo</code> object for a specific service.
		 *
		 * @param serviceName
		 *				The name of the service.
		 *
		 * @return A pointer to a vector of pointers to <code>ServiceInfo</code> objects.
		 */
		virtual vector<ServiceInfo*>* getServiceInfo( const string &serviceName );

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
		virtual void addServiceListener( const string& bundleName, ServiceListenerInfo* listenerInfo );
		
		/**
		 * Removes a service listener object from the registry.
		 *
		 * @param bundleName
		 *				The name of the bundle the service listener belongs to.
		 *
		 * @param serviceListener
		 *				The pointer to the service listener object.
		 */
		virtual void removeServiceListener( const string& bundleName, const ServiceListenerInfo& info );
		
};

}}}}}
#endif