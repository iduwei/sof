#ifndef SERVICE_LISTENER_INFO_H
#define SERVICE_LISTENER_INFO_H

#include <string>

#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"

#include "IServiceListener.h"

namespace sof { namespace framework {

using namespace std;

using namespace sof::util::logging;
using namespace sof::framework;

/**
 * The <code>ServiceListenerInfo</code> class is a helper
 * class for framework internal use and holds all important
 * information about a service listener.
 */
class ServiceListenerInfo
{
	private:

		/**
		 * The name of the bundle the service listener belongs to.
		 */
		string bundleName;

		/**
		 * The name of the service the service listener listens for.
		 */
		string serviceName;

		/**
		 * The constant pointer to the service listener object.
		 */
		IServiceListener::ConstPtr serviceListenerObj;

		/**
		 * The logger instance.
		 */
		static Logger& logger;

	public:

		/**
		 * Creates instances of class <code>ServiceListenerInfo</code>.
		 *
		 * @param bundleName
		 *				The name of the bundle the service listener belongs to.
		 *
		 * @param serviceName
		 *				The name of the service the service listener listens to.
		 *
		 * @param serviceListener
		 *				The service listener.
		 */
		ServiceListenerInfo( const string& bundleName, const string& serviceName, IServiceListener::ConstPtr serviceListener );

		/**
		 * Destroys the object.
		 */
		~ServiceListenerInfo();

		/**
		 * Returns the bundle name.
		 *
		 * @return 
		 *			The name of the bundle.
		 */
		string getBundleName() const;
		
		/**
		 * Returns the service name.
		 *
		 * @return 
		 *		The name of the service.
		 */
		string getServiceName() const;
		
		/**
		 * Returns the service listener object.
		 *
		 * @return 
		 *		A constant pointer to the service listener object.
		 */
		IServiceListener::ConstPtr getServiceListenerObj() const;
		
		/**
		 * Compares to instances of <code>ServiceListenerInfo</code>
		 * objects.
		 *
		 * @return
		 *			True if the <code>ServiceListenerInfo</code> objects
		 *			are equal, otherwise false.
		 */
		bool operator==( const ServiceListenerInfo& info1 );
		
		/**
		 * Returns a string representation of the 
		 * <code>ServiceListenerInfo</code> object.
		 *
		 * @return
		 *		A string containing all data of the
		 *		<code>ServiceListenerInfo</code>.
		 */
		string toString() const;
};

}}

#endif