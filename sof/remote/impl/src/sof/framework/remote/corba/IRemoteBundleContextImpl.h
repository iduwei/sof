#ifndef IREMOTE_BUNDLE_CONTEXT_IMPL
#define IREMOTE_BUNDLE_CONTEXT_IMPL

#include <map>

#include "sof/framework/IRegistry.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"

#include "CORBAHelper.h"
#include "IRemoteBundleContext.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::framework::remote::corba;

class IRemoteBundleContextImpl : public IRemoteBundleContext
{
	private:

		map<POA_sof::framework::remote::corba::generated::CORBAServiceListener*,
			CORBA::Object_var> listenerMap;

		/**
		 * The registry which stores all relevant information
		 * about the bundles (registered services, registered listeners etc.)
		 */
		IRegistry& registry;

		CORBAHelper& corbaHelper;

		/**
		 * The logger instance.
		 */
		static Logger& logger;

		/**
		 * Each bundle gets its own bundle context object. This is the
		 * name of the bundle the bundle context belongs to.
		 */
		string bundleName;

	public:

		/**
		 * Creates instances of class <code>IBundleContextImpl</code>.
		 *
		 * @param bundleName
		 *				The name of the bundle the context object belongs to.
		 *
		 * @param reg
		 *				The registry which stores bundle information of all
		 *				bundles.
		 */
		IRemoteBundleContextImpl( const string& bundleName, IRegistry& reg, CORBAHelper& corbaHelper );

		/**
		 * Desctructor which is called when object is deleted.
		 */
		virtual ~IRemoteBundleContextImpl();

		/**
		 * Registers a service with the SOF framework. Bundles which track this service
		 * are notified as soon as this service is registered.
		 *
		 * @param className
		 *				The class name of the service which is registered.
		 * @param service
		 *				The pointer to the service object.         		 
		 * @param dict
		 *				The properties object which describes the service object.
		 * @return 
		 *				Returns an object of type <code>IServiceRegistration</code> which provides
		 *				a method for unregistering the service object.
		 *
		 */
		virtual IServiceRegistration* registerRemoteService( const string &className, POA_sof::framework::remote::corba::generated::CORBAService* remoteService, 
			const Properties &dict );

		/**
         * Adds a service listener object to the framework. The service listener is notified when the service
		 * object (the service listener listens for) is registered.
		 * 
		 * @param serviceListener
		 *					The pointer to the service listener object.
		 * @param serviceName
		 *					The name of the service the listener listens for.
		 */
		virtual void addRemoteServiceListener( POA_sof::framework::remote::corba::generated::CORBAServiceListener* remoteServiceListener, const string &serviceName );

		/**
		 * Deregisters a service listener object.
		 *
		 * @param serviceListener
		 *				The pointer to the service listener object.
		 */
		virtual void removeRemoteServiceListener( POA_sof::framework::remote::corba::generated::CORBAServiceListener* remoteServiceListener );

		virtual IServiceRegistration* registerService( const string &className, IService::ConstPtr service, const Properties &dict );

		/**
         * Adds a service listener object to the framework. The service listener is notified when the service
		 * object (the service listener listens for) is registered.
		 * 
		 * @param serviceListener
		 *					The pointer to the service listener object.
		 * @param serviceName
		 *					The name of the service the listener listens for.
		 */
		virtual void addServiceListener( IServiceListener::ConstPtr serviceListener, const string &serviceName );

		/**
		 * Deregisters a service listener object.
		 *
		 * @param serviceListener
		 *				The pointer to the service listener object.
		 */
		virtual void removeServiceListener( IServiceListener::ConstPtr serviceListener );

		virtual CORBAHelper& getCORBAHelper();
};
}}}}
#endif