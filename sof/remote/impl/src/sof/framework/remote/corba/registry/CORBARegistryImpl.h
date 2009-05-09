#ifndef CORBA_REGISTRY_IMPL_H
#define CORBA_REGISTRY_IMPL_H

#include <vector>
#include <string>

#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"

#include "../generated/CORBAObjects.h"

namespace sof { namespace framework { namespace remote { namespace corba { namespace registry {

using namespace std;

using namespace sof::util::logging;
using namespace sof::framework::remote::corba::generated;

/**
 * The <code>CORBARegistryImpl</code> class represents the registry component where
 * the SOF processes forward registered services and service listeners.<br>
 * Each service and each service listener which is registered by a bundle of a SOF process is
 * forwarded to this registry component. Afterwards the registry notifies all SOF process which
 * are registered as observers at the registry component.
 */
class CORBARegistryImpl : virtual public POA_sof::framework::remote::corba::generated::CORBARegistry
{
	private:
		
		/**
		 * The logger instance.
		 */
		static Logger& logger;

		/**
		 * TODO: check for removing.
		 */
		CORBARegistryObserver_var obs;

		/**
		 * Vector containing the registry observer instances.
		 */
		vector<CORBARegistryObserver_var> objectVec;

	public:

		/**
		 * Adds a registry observer object to the internal observer vector.
		 *
		 * @param observer
		 *			The observer instance which is registered at the registry.
		 */
		virtual void addRegistryObserver( 
			sof::framework::remote::corba::generated::CORBARegistryObserver_ptr observer );

		/**
		 * Registers a service.
		 *
		 * @param bundleName
		 *			The name of the bundle which registers the service.
		 *
		 * @param serviceName
		 *			The name of the registered service instance.
		 *
		 * @param service
		 *			The CORBA service object.
		 *
		 * @param props
		 *			The properties object which describes the service instance.
		 */
		virtual void registerService( const char* bundleName, const char* serviceName, 
			CORBAService_ptr service,
			const CORBAServiceProps& props );

		/**
		 * Registers a service listener.
		 *
		 * @param bundleName
		 *			The name of the bundle which registers the service listener.
		 *
		 * @param serviceName
		 *			The name of the registered service instance the listener listens for.
		 *
		 * @param listener
		 *			The CORBA service listener object.
		 */
		virtual void registerServiceListener( const char* bundleName, const char* serviceName, 
			CORBAServiceListener_ptr listener );

		/**
		 * Unregisters a service.
		 *
		 * @param bundleName
		 *			The name of the bundle which registered the service.
		 *
		 * @param serviceName
		 *			The name of the service instance which is unregistered.
		 *
		 * @param service
		 *			The CORBA service object which is unregistered.
		 *
		 * @param props
		 *			The properties object which describes the service instance.
		 */
		virtual void unregisterService( const char* bundleName, const char* serviceName, 
			CORBAService_ptr service,
			const CORBAServiceProps& props );

		/**
		 * Unregisters a service listener.
		 *
		 * @param bundleName
		 *			The name of the bundle which registered the service listener
		 *
		 * @param serviceName
		 *			The name of the service instance the service listener listens for.
		 *
		 * @param listener
		 *			The CORBA service listener object.
		 */
		virtual void unregisterServiceListener( const char* bundleName, const char* serviceName, 
			CORBAServiceListener_ptr listener );

};

}}}}}
#endif
