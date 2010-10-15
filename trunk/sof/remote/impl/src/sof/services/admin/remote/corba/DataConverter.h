#ifndef DATA_CONVERTER_H
#define DATA_CONVERTER_H

#include <vector>

#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/framework/Properties.h"
#include "sof/framework/ServiceInfo.h"

#include "./generated/CORBAAdminObjects.h"
#include "../../../../framework/remote/corba/RemoteServiceListenerInfo.h"
#include "../../../../framework/remote/corba/RemoteServiceInfo.h"


namespace sof { namespace services { namespace admin { namespace remote { namespace corba {

using namespace std;

using namespace sof::util::logging;
using namespace sof::framework;
using namespace sof::services::admin::remote::corba::generated;
using namespace sof::framework::remote::corba;

/**
 * The <code>DataConverter</code> class is a helper class which converts data container 
 * to CORBA specific data container and vice versa. The conversion is necessary for communication
 * between a SOF process and the SOF administration UI.
 */
class DataConverter
{
	private:

		/**
		 * The logger instance.
		 */
		static Logger& logger;

	public:

		/**
		 * Converts a vector of strings (bundle names) into a CORBA sequence.
		 *
		 * @param bundleNames
		 *					Vector containing the bundle names of a SOF process.
		 *
		 * @return
		 *					A CORBA sequence containing the bundle names.
		 */
		static CORBABundleNameSequence* convert( const vector<string>& bundleNames );

		/**
		 * Converts a <code>Properties</code> object into a <code>CORBAAdminServiceProps</code> object.
		 *
		 * @param props
		 *					The properties object
		 *
		 * @return
		 *					The pointer to the <code>CORBAAdminServiceProps</code> object.
		 */
		static CORBAAdminServiceProps* convert( const Properties& props );

		/**
		 * Converts a <code>RemoteServiceInfo</code> object into a <code>CORBAAdminServiceInfo</code> object.
		 *
		 * @param props
		 *					The <code>ServiceInfo</code> object
		 *
		 * @return
		 *					The pointer to the <code>CORBAAdminServiceInfo</code> object.
		 */
		static CORBAAdminServiceInfo* convert( ServiceInfoPtr serviceInfo );
		
		/**
		 * Converts a <code>RemoteServiceListenerInfo</code> object into a <code>CORBAAdminServiceListenerInfo</code> object.
		 *
		 * @param props
		 *					The <code>RemoteServiceListenerInfo</code> object
		 *
		 * @return
		 *					The pointer to the <code>CORBAAdminServiceListenerInfo</code> object.
		 */
		static CORBAAdminServiceListenerInfo* convert( const RemoteServiceListenerInfo& serviceListenerInfo );
		
		/**
		 * Converts a vector of <code>ServiceInfo</code> objects into a <code>CORBAAdminServiceInfoSequence</code> object.
		 *
		 * @param props
		 *					The vector of <code>ServiceInfo</code> object
		 *
		 * @return
		 *					The pointer to the <code>CORBAAdminServiceInfoSequence</code> object.
		 */
		static CORBAAdminServiceInfoSequence* convert( const vector<ServiceInfoPtr>& serviceInfo );
		
		/**
		 * Converts a vector of <code>ServiceListenerInfo</code> objects into a <code>CORBAAdminServiceListenerInfoSequence</code> object.
		 *
		 * @param props
		 *					The vector of <code>ServiceListenerInfo</code> object
		 *
		 * @return
		 *					The pointer to the <code>CORBAAdminServiceListenerInfoSequence</code> object.
		 */
		static CORBAAdminServiceListenerInfoSequence* convert( const vector<ServiceListenerInfo*>& serviceListenerInfo );
};
}}}}}
#endif