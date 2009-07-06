#ifndef CORBA_REGISTRY_OBSERVER_IMPL_H
#define CORBA_REGISTRY_OBSERVER_IMPL_H

#include "sof/framework/IRegistry.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"

#include "../generated/CORBAObjects.h"

#include "../CORBAHelper.h"

namespace sof { namespace framework { namespace remote { namespace corba { namespace registry {

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::framework::remote::corba::generated;
using namespace sof::framework::remote::corba;

/**
 * Each SOF process activates a CORBA object of implementation type <code>CORBARegistryObserverImpl</code> in order
 * to be informed by the registry process about registered and unregistered services and service listeners.
 *
 * @author magr74
 */
class CORBARegistryObserverImpl : virtual public POA_sof::framework::remote::corba::generated::CORBARegistryObserver
{
	private:
		
		/**
		 * The logger instance.
		 */
		static Logger& logger;
		
		/**
		 * The registry object holding the information of registered services
		 * and service listeners of each SOF process.
		 */
		IRegistry& registry;

		/**
		 * Helper class providing an interface for CORBA related calls.
		 */
		CORBAHelper& corbaHelper;

	public:
		
		/**
		 * Creates instances of class <code>CORBARegistryObserverImpl</code>.
		 *
		 * @param registry
		 *			The registry instance.
		 *
		 * @param corbaHelper
		 *			The CORBA helper class.
		 */
		CORBARegistryObserverImpl( IRegistry& registry, CORBAHelper& corbaHelper );

		/**
		 * Destroys objects of type <code>CORBARegistryObserverImpl</code>.
		 */
		virtual ~CORBARegistryObserverImpl();

		/**
		 * Alive method call.
		 * TODO: remove this call.
		 */
		virtual void ping();

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
