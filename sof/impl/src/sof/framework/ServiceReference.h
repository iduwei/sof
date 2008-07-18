#ifndef SERVICE_REFERENCE_H
#define SERVICE_REFERENCE_H

#include <string>

#include "Properties.h"
#include "IService.h"

namespace sof { namespace framework {

using namespace std;

using namespace sof::framework;

/**
 * The <code>ServiceReference</code> represents a 
 * service and holds all important information regarding
 * a service object.
 */
class ServiceReference 
{
	private:		

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
		IService::ConstPtr service;

	public:

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
		 * Returns the service name.
		 *
		 * @return
		 *		The name of the service.
		 */
		string getServiceName() const;

		/**
		 * Returns the properties object.
		 *
		 * @return
		 *		The properties describing the service object.
		 */
		Properties getServiceProperties() const;

		/**
		 * Returns a constant pointer to the service object.
		 *
		 * @return
		 *		The constant pointer to the service object.
		 */
		IService* getService() const;

};

}}
#endif