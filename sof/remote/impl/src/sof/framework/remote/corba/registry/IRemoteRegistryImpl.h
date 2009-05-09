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

template<class ThreadingModel=SingleThreaded>
class IRemoteRegistryImpl : public IRegistryImpl<ThreadingModel>
{
	private:
		CORBAHelper& corbaHelper;

	public:
		IRemoteRegistryImpl( CORBAHelper& corbaHelper );
		virtual ~IRemoteRegistryImpl();
		virtual bool callServiceListenerObject( const ServiceListenerInfo& info, const ServiceEvent& serviceEvent );

		virtual void stopActivator( BundleInfoBase* bi ) ;

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

		virtual bool areServiceListenerObjectsEqual( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 );


};

#include "IRemoteRegistryImpl.cpp"

}}}}}
#endif