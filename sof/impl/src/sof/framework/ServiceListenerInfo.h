#ifndef SERVICE_LISTENER_INFO_H
#define SERVICE_LISTENER_INFO_H

#include <string>

#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"
#include "../util/memory/SmartPtr.h"

#include "IServiceListener.h"

namespace sof { namespace framework {

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::util::memory;

/**
 * The <code>ServiceListenerInfo</code> class is a helper
 * class for framework internal use and holds all important
 * information about a service listener.
 *
 * @author magr74
 */
class ServiceListenerInfo
{
	protected:

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
		IServiceListener* serviceListenerObj;

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
		 * Copy constructor.
		 *
		 * @param info
		 *			The <code>ServiceListenerInfo</code> object which is copied.
		 */
		ServiceListenerInfo( const ServiceListenerInfo& info );

		/**
		 * Destroys the object.
		 */
		virtual ~ServiceListenerInfo();

		/**
		 * Returns the bundle name.
		 *
		 * @return 
		 *			The name of the bundle.
		 */
		virtual string getBundleName() const;
		
		/**
		 * Returns the service name.
		 *
		 * @return 
		 *		The name of the service.
		 */
		virtual string getServiceName() const;
		
		/**
		 * Returns the service listener object.
		 *
		 * @return 
		 *		A constant pointer to the service listener object.
		 */
		virtual IServiceListener::ConstPtr getServiceListenerObj() const;
		
		/**
		 * Compares to instances of <code>ServiceListenerInfo</code>
		 * objects.
		 *
		 * @return
		 *			True if the <code>ServiceListenerInfo</code> objects
		 *			are equal, otherwise false.
		 */
		virtual bool operator==( const ServiceListenerInfo& info1 );
		
		/**
		 * Assigns the passed <code>ServiceListenerInfo</code> object to this object.
		 *
		 * @param serviceListenerInfo
		 *				The service listener object which is assigned to this.
		 *
		 * @return
		 *				This service listener object.
		 */			
		virtual ServiceListenerInfo& operator=( const ServiceListenerInfo &serviceListenerInfo );

		/**
		 * Compares two objects of type <code>ServiceListenerInfo</code>.
		 *
		 * @param info1
		 *				The first <code>ServiceListenerInfo</code> object which is compared.
		 *
		 * @param info2
		 *				The second <code>ServiceListenerInfo</code> object which is compared.
		 *
		 * @return
		 *				True, if the objects are equal, otherwise false.
		 */
		virtual bool equals( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 );

		/**
		 * Returns a string representation of the 
		 * <code>ServiceListenerInfo</code> object.
		 *
		 * @return
		 *		A string containing all data of the
		 *		<code>ServiceListenerInfo</code>.
		 */
		virtual string toString() const;		
};

		/** 
		 * Smart pointer for <code>ServiceInfo</code> objects.
		 */
		typedef SmartPtr<ServiceListenerInfo> ServiceListenerInfoPtr;

}}

#endif