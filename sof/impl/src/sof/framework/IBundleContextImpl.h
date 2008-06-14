#ifndef IBUNDLE_CONTEXT_IMPL_H
#define IBUNDLE_CONTEXT_IMPL_H

#include <string>
#include "IService.h"
#include "IBundleContext.h"
#include "Properties.h"
#include "IServiceListener.h"
#include "IServiceRegistration.h"
#include "IRegistry.h"
#include "../util/logging/Logger.h"

namespace sof { namespace framework {

using namespace std;
using namespace sof::framework;
using namespace sof::util::logging;

/**
 * The <code>IBundleContextImpl</code> class represents the implementation
 * of the <code>IBundleContext</code> interface.
 */
class IBundleContextImpl : public IBundleContext
{
	private:

		/**
		 * The registry which stores all relevant information
		 * about the bundles (registered services, registered listeners etc.)
		 */
		IRegistry* const registry;

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
		IBundleContextImpl( const string& bundleName, IRegistry* const reg );

		/**
		 * The destructor of the bundle context.
		 */
		virtual ~IBundleContextImpl();

		/**
		 * Registers a service.
		 *
		 * @see sof::framework::IBundleContext::registerService
		 */
		virtual IServiceRegistration::ConstPtr registerService( const string &className, IService::ConstPtr service, const Properties &dict );

		/**
		 * Registers a service listener object.
		 *
		 * @see sof::framework::IBundleContext::addServiceListener
		 */
		virtual void addServiceListener( IServiceListener::ConstPtr serviceListener, const string &serviceName );

		/**
		 * Removes a service listener object.
		 *
		 * @see sof::framework::IBundleContext::removeServiceListener
		 */
		virtual void removeServiceListener( IServiceListener::ConstPtr serviceListener );
};

}}
#endif