#ifndef REMOTE_ADMINISTRATION_ACTIVATOR_H
#define REMOTE_ADMINISTRATION_ACTIVATOR_H

#include "sof/services/admin/IAdministrationProvider.h"
#include "sof/services/admin/IAdministrationServiceImpl.h"

#include "../../framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/framework/IServiceRegistration.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/util/logging/Logger.h"

namespace sof { namespace services { namespace admin {

using namespace sof::framework;
using namespace sof::framework::remote::corba;
using namespace sof::util::logging;
using namespace sof::services::admin;

/**
 * The <code>AdministrationActivator</code> is the activator
 * class of the administration bundle which provides a administration
 * console for the user.<br>
 * This activator class is created when <code>startAdministrationBundle</code>
 * of the <code>Launcher</code> class is called.<br>
 * Note: After the <code>startAdministrationBundle</code> method is called the
 * executing thread blocks and waits for user inputs on the console.
 */
class RemoteAdministrationActivator : public IRemoteBundleActivator
{
	private:

		/**
		 * The logger instance.
		 */
		static Logger& log;

		/**
		 * The administration service providing the interface for administrating
		 * the SOF runtime environment.
		 */
		IAdministrationServiceImpl* adminService;

		/**
		 * The administration provider the administration commands
		 * are forwarded to.
		 */
		IAdministrationProvider* adminProvider;

		/**
		 * The <code>IServiceRegistration</code> object of
		 * the administration service.
		 */
		IServiceRegistration* serviceReg;


	public:

		/**
		 * Starts the administration bundle by creating
		 * a console and waits for user input.
		 */
		void start( IRemoteBundleContext::ConstPtr context );

		/**
		 * Stops the administration bundle.
		 */
		void stop( IRemoteBundleContext::ConstPtr context );

		/**
		 * Sets the <code>Launcher</code> instance to be able
		 * to communicate with the framework.
		 */
		void setAdministrationProvider( IAdministrationProvider* adminProvider );
};

}}}

#endif