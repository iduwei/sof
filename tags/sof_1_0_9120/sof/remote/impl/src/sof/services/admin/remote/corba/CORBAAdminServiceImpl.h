#ifndef CORBA_ADMIN_SERVICE_IMPL_H
#define CORBA_ADMIN_SERVICE_IMPL_H

#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/services/admin/IAdministrationProvider.h"
#include "./generated/CORBAAdminObjects.h"

namespace sof { namespace services { namespace admin { namespace remote { namespace corba { 

using namespace sof::services::admin::remote::corba::generated;
using namespace sof::util::logging;
using namespace sof::services::admin;

/**
 * The <code>CORBAAdminServiceImpl</code> class provides diagnosis methods which can be called by
 * the SofAdminUI remotely.
 *
 * @author magr74
 */
class CORBAAdminServiceImpl : virtual public POA_sof::services::admin::remote::corba::generated::CORBAAdminService 
{
	private:

		/**
		 * The logger instance.
		 */
		static Logger& logger;

		/**
		 * The administration provider object the diagnosis method calls are forwarded to.
		 */
		IAdministrationProvider& adminProvider;

	public:

		/**
		 * Creates instance of class <code>CORBAAdminServiceImpl</code>.
		 *
		 * @param adminProvider
		 *					The administration provider instance.
		 */
		CORBAAdminServiceImpl( IAdministrationProvider& adminProvider );

		/**
		 * Destroys the instance <code>CORBAAdminServiceImpl</code>.
		 */
		virtual ~CORBAAdminServiceImpl();

		/**
		 * Returns the name of all running bundles.
		 *
		 * @return
		 *			A sequence object containing the bundle names.
		 */
		virtual CORBABundleNameSequence* getBundleNames();

		/**
		 * Returns the used services of the specified bundle.
		 *
		 * @param bundleName
		 *			The name of the bundle.
		 *
		 * @return
		 *			A sequence object containing the used services of a bundle.
		 */
		virtual CORBAAdminServiceInfoSequence* getUsedServices( const char* bundleName );

		/**
		 * Returns the registered services of the specified bundle.
		 *
		 * @param bundleName
		 *			The name of the bundle.
		 *
		 * @return
		 *			A sequence object containing the registered services of a bundle.
		 */
		virtual CORBAAdminServiceInfoSequence* getRegisteredServices( const char* bundleName );
		
		/**
		 * Returns the registered service listeners of the specified bundle.
		 *
		 * @param bundleName
		 *			The name of the bundle.
		 *
		 * @return
		 *			A sequence object containing the registered service listeners of a bundle.
		 */		
		virtual CORBAAdminServiceListenerInfoSequence* getRegisteredServiceListeners( const char* bundleName );
};

}}}}}
#endif