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

class AdministrationActivator : public IBundleActivator
{
	private:
		static Logger& log;
		Launcher* launcher;

	public:
		void start( IBundleContext::ConstPtr context );
		void stop( IBundleContext::ConstPtr context );
		void setLauncher( Launcher* launcher );
};

}}}

#endif