#ifndef IREMOTE_REGISTRY_IMPL_H
#define IREMOTE_REGISTRY_IMPL_H

#include "sof/framework/IRegistryImpl.h"
#include "sof/framework/remote/corba/RemoteServiceListenerInfo.h"
#include "sof/framework/remote/corba/RemoteServiceReference.h"
#include "sof/framework/remote/corba/RemoteServiceInfo.h"
#include "../RemoteBundleInfo.h"
#include "../CORBAHelper.h"

namespace sof { namespace framework { namespace remote { namespace corba { namespace registry {

using namespace sof::framework;
using namespace sof::framework::remote::corba;
using namespace sof::util::logging;
using namespace sof::util::threading;

/**
 * The <code>IRemoteRegistryImpl</code> class extends the 
 * <code>IRegistryImpl</code> class and adds functionality for
 * remote features.
 *
 * @author magr74
 */
template<class ThreadingModel=SingleThreaded>
class IRemoteRegistryImpl : public IRegistryImpl<ThreadingModel>
{
	private:

		/**
		 * The <CORBAHelper</code> instance which provides corba
		 * related functions.
		 */
		CORBAHelper& corbaHelper;

	public:

		/**
		 * Creates instances of class <code>IRemoteRegistryImpl<code>.
		 *
		 * @param corbaHelper
		 *				The helper class for CORBA related calls.
		 */
		IRemoteRegistryImpl( CORBAHelper& corbaHelper );

		/**
		 * Destroys objects of type <code>IRemoteRegistryImpl</code>.
		 */
		virtual ~IRemoteRegistryImpl();

	protected:

		/**
		 * Sends an event to a service listener.
		 * 
		 * @param listenerInfo 
		 *					The <code>ServiceListenerInfo</code> object describing the service listener which
		 *					is notified.
		 *
		 * @param serviceInfo 
		 *					The <code>ServiceInfo</code> object describing the service the event is related to.
		 *
		 * @param eventType
		 *					The service event type (e.g. REGISTER, UNREGISTER).
		 */
		virtual bool callServiceListenerObject( ServiceListenerInfoPtr info, ServiceInfoPtr serviceInfo, const ServiceEvent::						EventType& eventType );

		/**
		 * Stops the activator of the specified bundel information object.
		 *
		 * @param bi
		 *			The object which encapsulates bundle information.
		 */
		virtual void stopActivator( const BundleInfoBase& bi ) ;

		/**
		 * Destroys the activator object which is specified by the
		 * given bundle information.
		 *
		 * @param bi
		 *			The object which encapsulates bundle information
		 *			(e.g. bundle activator).
		 */
		virtual void deleteActivator( const BundleInfoBase& bi ) ;

		/**
		 * Compares two objects of type <code>ServiceListenerInfo</code>.
		 *
		 * @param info1
		 *			The info object of the first service listener.
		 *
		 * @param info2
		 *			The info object of the second service listener.
		 */		 			
		virtual bool areServiceListenerObjectsEqual( ServiceListenerInfoPtr info1, ServiceListenerInfoPtr info2 );

		/**
		 * Creates no service registration object on 'remote' side and returns null. The service
		 * registration object was already created on client side.
		 */
		virtual IServiceRegistration::ConstPtr createServiceRegistrationObject( const string& bundleName, ServiceInfoPtr serviceInfo );
};

#include "IRemoteRegistryImpl.cpp"

}}}}}
#endif