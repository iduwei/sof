#ifndef ADMINISTRATION_ACTIVATOR_H
#define ADMINISTRATION_ACTIVATOR_H

#include "../../framework/IBundleActivator.h"
#include "../../util/logging/LoggerFactory.h"
#include "../../util/logging/Logger.h"
#include "../../framework/Launcher.h"
#include "../../instantiation/ObjectCreator.h"

namespace sof { namespace services { namespace admin {

using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::logging;

/**
 * The <code>AdministrationActivator</code> is the activator
 * class of the administration bundle which provides a administration
 * console for the user.<br>
 * This activator class is created when <code>startAdministrationBundle</code>
 * of the <code>Launcher</code> class is called.<br>
 * Note: After the <code>startAdministrationBundle</code> method is called the
 * executing thread blocks and waits for user inputs on the console.
 */
class AdministrationActivator : public IBundleActivator
{
	private:

		/**
		 * The logger instance.
		 */
		static Logger& log;

		/**
		 * The launcher instance.
		 */
		Launcher* launcher;

	public:

		/**
		 * Starts the administration bundle by creating
		 * a console and waits for user input.
		 */
		void start( IBundleContext::ConstPtr context );

		/**
		 * Stops the administration bundle.
		 */
		void stop( IBundleContext::ConstPtr context );

		/**
		 * Sets the <code>Launcher</code> instance to be able
		 * to communicate with the framework.
		 */
		void setLauncher( Launcher* launcher );
};

}}}

#endif