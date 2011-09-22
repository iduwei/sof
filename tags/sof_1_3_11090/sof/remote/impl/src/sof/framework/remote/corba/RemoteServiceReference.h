#ifndef REMOTE_SERVICE_REFERENCE_H
#define REMOTE_SERVICE_REFERENCE_H

#include <string>

#include "sof/framework/ServiceReference.h"
#include "sof/framework/SOFException.h"

#include "sof/util/logging/LoggerFactory.h"
#include "sof/util/logging/Logger.h"

#include "./generated/CORBAObjects.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace std;

using namespace sof::framework;
using namespace sof::framework::remote::corba::generated;

/**
 * The <code>RemoteServiceReference</code> class extends the
 * <code>ServiceReference</code> class by remote related features.
 *
 * @author magr74
 */
class RemoteServiceReference : public ServiceReference
{
	private:

		/**
		 * The object identifier of the remote service.
		 */
		string remoteObjectID;

		/**
		 * The remote service object represented by a CORBA object.
		 */
		CORBAService_var remoteService;

	public:

		/**
		 * Creates instances of type <code>RemoteServiceReference</code>.
		 *
		 * @param name
		 *			The name of the remote service.
		 *
		 * @param properties
		 *			The properties of the remote service.
		 *
		 * @param serviceObj
		 *			The remote service object which is represented by a CORBA object.
		 *
		 * @param objID
		 *			The object identifier of the remote service object.
		 */
		RemoteServiceReference( const string &name, const Properties &properties, CORBAService_var serviceObj, const string& objID );

		/**
		 * Copy constructor.
		 *
		 * @param serviceRef
		 *				The remote service reference object which is copied.
		 */
		RemoteServiceReference( const RemoteServiceReference& serviceRef );

		/**
		 * The assignment operator.
		 *
		 * @param serviceRef
		 *				The remote service reference object which is assigned to this object.
		 *
		 * @return
		 *				This remote service reference object.
		 */
		virtual RemoteServiceReference &operator=( const RemoteServiceReference &serviceRef );

		/**
		 * Destroys objects of type <code>RemoteServiceReference</code>.
		 */
		virtual ~RemoteServiceReference();

		/**
		 * Returns the identifier of the remote service.
		 *
		 * @return
		 *		The object identifier of the remote service.
		 */
		virtual string getRemoteServiceID() const;

		/**
		 * The remote service object represented by a CORBA object.
		 *
		 * @return
		 *			The CORBA object.
		 */
		virtual CORBAService_var getRemoteService() const;

		/**
		 * Compares the passed <code>RemoteServiceReference</code> object with this object.
		 *
		 * @param serviceReference
		 *				The service reference object which is compared with this object.
		 *
		 * @return
		 *				True, if both objects are equal, otherwise false.
		 */
		virtual bool operator==( const RemoteServiceReference& serviceReference );

		/**
		 * Returns the string representation of this object.
		 *
		 * @return
		 *			The string representation.
		 */
		virtual string toString() const;

		/**
		 * Returns the local service.
		 *
		 * @return
		 *			The local service object.
		 */
		virtual IService::ConstPtr getService() const;

};

}}}}

#endif