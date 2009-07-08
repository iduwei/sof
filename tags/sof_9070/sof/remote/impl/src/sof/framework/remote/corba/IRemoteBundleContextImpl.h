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

/**
 * When the framework starts or stops a bundle (calling <code>start</code> or
 * <code>stop</code> of the <code>IRemoteBundleActivator</code>) a bundle context object
 * is passed. This <code>IRemoteBundleContext</code> object provides methods for registering
 * distributed services, service listeners etc.<br>
 * It represents a means for the software bundle developer in order to communicate with
 * the framework.
 *
 * @author magr74
 */
class IRemoteBundleContextImpl : public IRemoteBundleContext
{
	private:

		/**
		 * Map object which maps <code>CORBAServiceListener</code> objects to
		 * their CORBA objects.
		 */
		map<POA_sof::framework::remote::corba::generated::CORBAServiceListener*,
			CORBA::Object_var> listenerMap;

		/**
		 * The registry object which stores all relevant information
		 * about the bundles (registered services, registered listeners etc.)
		 */
		IRegistry& registry;

		/**
		 * Helper class which provides CORBA related methods (e.g. for creating,
		 * activating and deactivating CORBA objects).		 
		 */
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

		/**
		 * Registers a service object.
		 * 
		 * @param className
		 *				The name of the service (e.g. class name)
		 *
		 * @param service
		 *				The service object.
		 *
		 * @param dict
		 *				Describes the properties of the service object.
		 *
		 * @return
		 *				Handle to the registered service.
		 */
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

		/**
		 * Returns the CORBA helper object which provides CORBA related
		 * functions.
		 *
		 * @return 
		 *			The CORBA helper object.
		 */
		virtual CORBAHelper& getCORBAHelper();
};
}}}}
#endif