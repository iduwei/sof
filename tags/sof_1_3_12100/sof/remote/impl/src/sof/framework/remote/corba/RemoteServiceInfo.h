#ifndef REMOTE_SERVICE_INFO_H
#define REMOTE_SERVICE_INFO_H

#include <CORBA.h>

#include <string>

#include "sof/framework/ServiceInfo.h"
#include "sof/util/memory/SmartPtr.h"

#include "./generated/CORBAObjects.h"

using namespace sof::framework;
using namespace sof::framework::remote::corba::generated;
using namespace sof::util::memory;

namespace sof { namespace framework { namespace remote { namespace corba {

/**
 * The <code>RemoteServiceInfo</code> class extends the 
 * <code>ServiceInfo</code> class by remote relevant information.
 *
 * @author magr74
 */
class RemoteServiceInfo : public ServiceInfo
{
	private:

		/**
		 * The remote service object (CORBA object).
		 */
		CORBAService_var remoteServiceObject;

		/**
		 * The unique string representation of the remote service object.
		 */
		string objID;

	public:

		/**
		 * Creates instances of type <code>RemoteServiceInfo</code>.
		 *
		 * @param servName
		 *				The name of the service.
		 *
		 * @param serviceObj
		 *				The remote service object.
		 *
		 * @param objID
		 *				The identifier of the remote service object.
		 *
		 * @param properties
		 *				The description of the remote service object.
		 */
		RemoteServiceInfo( const string &servName, CORBAService_var serviceObj, const string& objID, 
			const Properties &properties );

		/**
		 * Copy constructor.
		 *
		 * @param info
		 *			The <code>RemoteServiceInfo</code> object which is copied.
		 */
		RemoteServiceInfo( const RemoteServiceInfo& info );

		/**
		 * Compares two <code>RemoteServiceInfo</code> objects.
		 *
		 * @param info1
		 *				The first of the two service info objects which are compared.
		 *
		 * @param info2
		 *				The second of the two service info objects which are compared.
		 *
		 * @return
		 *				True, if both objects are equal, otherwise false.
		 */
		virtual bool equals( const ServiceInfo& info1, const ServiceInfo& info2 );

		/**
		 * Destroys objects of type <code>RemoteServiceInfo</code>.
		 */
		virtual ~RemoteServiceInfo();

		/**
		 * Returns the identifier of the remote service object.
		 *
		 * @return
		 *			The identifier of the service object.
		 */
		virtual string getRemoteServiceID() const;
		
		/**
		 * Returns the remote service object.
		 *
		 * @return
		 *			The CORBA object which represents the remote service.
		 */
		virtual CORBAService_var getRemoteService() const;

		/**
		 * TODO: check whether this method is necessary.
		 *
		 * Compares this <code>RemoteServiceInfo</code> object with another one.
		 *
		 * @param serviceInfo
		 *				The service info object which is compared which this object.
		 *
		 * @return
		 *				True, if both objects are equal, otherwise false.
		 */
		virtual bool operator==( const RemoteServiceInfo& serviceInfo );

		/**
		 * Assigns the passed <code>RemoteServiceInfo</code> object to this object.
		 *
		 * @param serviceInfo
		 *				The service info object which is assigned to this.
		 *
		 * @return
		 *				This service info object.
		 */			
		virtual RemoteServiceInfo& operator=( const RemoteServiceInfo &serviceInfo );

		/**
		 * Returns a string representation of the remote service object.
		 *
		 * @return
		 *			The string representation of the remote service object.
		 */
		virtual string toString() const;

		/**
		 * TODO: check for removing!

		 * Returns the service object.
		 *
		 * @return
		 *			The service object.
		 */
		virtual IService::ConstPtr getService() const;
};

/** 
 * Smart pointer for <code>RemoteServiceInfo</code> objects.
 */
typedef SmartPtr<RemoteServiceInfo> RemoteServiceInfoPtr;

}}}}
#endif
