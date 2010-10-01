#ifndef SERVICE_REFERENCE_H
#define SERVICE_REFERENCE_H

#include <string>
#include <sstream>

#include "Properties.h"
#include "IService.h"

#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"

namespace sof { namespace framework {

using namespace std;

using namespace sof::framework;
using namespace sof::util::logging;

/**
 * The <code>ServiceReference</code> represents a 
 * service and holds all important information regarding
 * a service object.
 *
 * @author magr74
 */
class ServiceReference 
{
	protected:		

		/**
		 * The name of the service.
		 */
		string serviceName;

		/**
		 * The properties describing the service object.
		 */
		Properties props;

		/**
		 * The constant pointer to the service object.
		 */
		IService* service;

		/**
		 * The logger instance.
		 */
		static Logger& logger;

	public:

		/**
		 * Creates instances of class <code>ServiceReference</code>.
		 *
		 */
		ServiceReference();

		/**
		 * Creates instances of class <code>ServiceReference</code>.
		 *
		 * @param name
		 *			The service name.
		 *
		 * @param properties
		 *			The properties object describing the service object.
		 *
		 * @param serv
		 *			The service object.
		 */
		ServiceReference( const string &name, const Properties &properties, const IService::ConstPtr serv );

		/**
		 * Copy constructor.
		 *
		 * @param serviceRef
		 *				The <code>ServiceReference</code> object which is copied.
		 */
		ServiceReference( const ServiceReference& serviceRef );

		/**
		 * The assignment operator.
		 *
		 * @param serviceRef
		 *				The <code>ServiceReference</code> object which is assignd to this
		 *				object.
		 */
		virtual ServiceReference &operator=( const ServiceReference &serviceRef );

		/**
		 * Destroys the <code>ServiceReference</code> object.
		 */
		virtual ~ServiceReference();

		/**
		 * Sets the name of the service.
		 *
		 * @param name
		 *			The service name.
		 */
		virtual void setServiceName( const string& name );

		/**
		 * Sets the properties of the service.
		 *
		 * @param props
		 *			The service properties.
		 */
		virtual void setServiceProperties( const Properties& props );

		/**
		 * Sets the service object.
		 * 
		 * @param service
		 *				The service object.
		 */
		virtual void setService( IService::ConstPtr service );

		/**
		 * Returns the service name.
		 *
		 * @return
		 *		The name of the service.
		 */
		virtual string getServiceName() const;

		/**
		 * Returns the properties object.
		 *
		 * @return
		 *		The properties describing the service object.
		 */
		virtual Properties getServiceProperties() const;

		/**
		 * Returns a constant pointer to the service object.
		 *
		 * @return
		 *		The constant pointer to the service object.
		 */
		virtual IService::ConstPtr getService() const;

		/**
		 * Returns the string representation of the <code>ServiceReference</code> object.
		 *
		 * @return 
		 *		The string representation.
		 */
		virtual string toString() const;

};

}}
#endif