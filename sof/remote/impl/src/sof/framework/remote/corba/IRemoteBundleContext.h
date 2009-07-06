#ifndef IREMOTE_BUNDLE_CONTEXT_H
#define IREMOTE_BUNDLE_CONTEXT_H

#include <string>

#include "sof/framework/Properties.h"
#include "sof/framework/IBundleContext.h"
#include "sof/framework/IServiceRegistration.h"

#include "./generated/CORBAObjects.h"
#include "CORBAHelper.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace std;

using namespace sof::framework;
using namespace POA_sof::framework::remote::corba::generated;

/**
 * When the framework starts or stops a bundle (calling <code>start</code> or
 * <code>stop</code> of the <code>BundleActivator</code>) a bundle context object
 * is passed. This <code>IBundleContext</code> object provides methods for registering
 * services, service listeners etc.<br>
 * It represents a means for the software bundle developer in order to communicate with
 * the framework.
 *
 * @author magr74
 */
class IRemoteBundleContext : public IBundleContext
{
	public:

		/**
		 * Type definition for a constant pointer.
		 */
		typedef IRemoteBundleContext* const ConstPtr;

		/**
		 * Desctructor which is called when object is deleted.
		 */
		virtual ~IRemoteBundleContext() {};

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
		virtual IServiceRegistration* registerRemoteService( const string &className, 
			POA_sof::framework::remote::corba::generated::CORBAService* remoteService, const Properties &dict ) = 0;

		/**
         * Adds a service listener object to the framework. The service listener is notified when the service
		 * object (the service listener listens for) is registered.
		 * 
		 * @param serviceListener
		 *					The pointer to the service listener object.
		 * @param serviceName
		 *					The name of the service the listener listens for.
		 */
		virtual void addRemoteServiceListener( POA_sof::framework::remote::corba::generated::CORBAServiceListener* remoteServiceListener, 
			const string &serviceName ) = 0;

		/**
		 * Deregisters a service listener object.
		 *
		 * @param serviceListener
		 *				The pointer to the service listener object.
		 */
		virtual void removeRemoteServiceListener( POA_sof::framework::remote::corba::generated::CORBAServiceListener* remoteServiceListener ) = 0;

		/**
		 * Returns the CORBA helper object which provides CORBA related
		 * functions.
		 *
		 * @return 
		 *			The CORBA helper object.
		 */
		virtual CORBAHelper& getCORBAHelper() = 0;
};

}}}}
#endif