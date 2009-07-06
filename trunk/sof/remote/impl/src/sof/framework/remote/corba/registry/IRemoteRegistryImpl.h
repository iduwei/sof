#ifndef IREMOTE_REGISTRY_IMPL_H
#define IREMOTE_REGISTRY_IMPL_H

#include "sof/framework/IRegistryImpl.h"
#include "sof/framework/remote/corba/RemoteServiceListenerInfo.h"
#include "sof/framework/remote/corba/RemoteServiceReference.h"
#include "sof/framework/remote/corba/RemoteServiceInfo.h"
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

		/**
		 * Calls the remote service listener object.
		 *
		 * @param info
		 *			The service listener info object.
		 *
		 * @param serviceEvent
		 *			The occured event the remote service listener has to be
		 *			informed about.
		 */
		virtual bool callServiceListenerObject( const ServiceListenerInfo& info, const ServiceEvent& serviceEvent );

		/**
		 * Stops the activator of the specified bundel information object.
		 *
		 * @param bi
		 *			The object which encapsulates bundle information.
		 */
		virtual void stopActivator( BundleInfoBase* bi ) ;

		/**
		 * Destroys the activator object which is specified by the
		 * given bundle information.
		 *
		 * @param bi
		 *			The object which encapsulates bundle information
		 *			(e.g. bundle activator).
		 */
		virtual void deleteActivator( BundleInfoBase* bi ) ;

		/**
		 * Creates a <code>ServiceReference</code> object.
		 *
		 * @param serviceInfo
		 *				The <code>ServiceInfo</code> instance.
		 * @return 
		 *				The created <code>ServiceReference</code>.
         */		
		virtual ServiceReference* createServiceReference( const ServiceInfo& serviceInfo );

		/**
		 * Compares two objects of type <code>ServiceListenerInfo</code>.
		 *
		 * @param info1
		 *			The info object of the first service listener.
		 *
		 * @param info2
		 *			The info object of the second service listener.
		 */		 			
		virtual bool areServiceListenerObjectsEqual( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 );


};

#include "IRemoteRegistryImpl.cpp"

}}}}}
#endif