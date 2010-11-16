#ifndef REMOTE_SERVICE_LISTENER_INFO_H
#define REMOTE_SERVICE_LISTENER_INFO_H

#include <CORBA.h>

#include <string>

#include "sof/framework/ServiceListenerInfo.h"

#include "./generated/CORBAObjects.h"

using namespace sof::framework;
using namespace sof::framework::remote::corba::generated;

namespace sof { namespace framework { namespace remote { namespace corba {

/**
 * The <code>RemoteServiceListenerInfo</code> object extends the
 * <code>ServiceListenerInfo</code> object by remote relevant information.
 *
 * @author magr74
 */
class RemoteServiceListenerInfo : public ServiceListenerInfo
{
	private:

		/**
		 * The service listener object which can be called remotely.
		 */
		CORBAServiceListener_var remoteServiceObject;

		/**
		 * The unique object identifier for the CORBA service listener object.
		 */
		string objID;

	public:

		/**
		 * Creates instances of type <code>RemoteServiceListener</code>.
		 *
		 * @param bundleName
		 *				The name of the bundle the listener object belongs to.
		 *
		 * @param servName
		 *				The name of the service the service listener object listens for.
		 *
		 * @param serviceObj
		 *				The CORBA object representing the service listener.
		 *
		 * @param objID
		 *				The object identifier of the service listener.
		 */
		RemoteServiceListenerInfo( const string& bundleName, const string &servName, CORBAServiceListener_var serviceObj, const string& objID );

		/**
		 * Copy constructor.
		 *
		 * @param info
		 *			The <code>RemoteServiceListenerInfo</code> object which is copied.
		 */
		RemoteServiceListenerInfo( const RemoteServiceListenerInfo& info );

		/**
		 * Destroys objects of type <code>RemoteServiceListenerInfo</code>.
		 */
		virtual ~RemoteServiceListenerInfo();

		/**
		 * Returns the identifier of the remote service listener.
		 *
		 * @return
		 *		The object identifier.
		 */
		virtual string getRemoteServiceListenerID() const;

		/**
		 * Returns the CORBA object representing the remote service listener.
		 *
		 * @return
		 *		The CORBA object.
		 */
		virtual CORBAServiceListener_var getRemoteServiceListener();

		/**
		 * Return the local service listener object.
		 *
		 * @return
		 *			The service listener object.
		 */
		virtual IServiceListener::ConstPtr getServiceListenerObj() const;

		/**
		 * TODO: check for removing.
		 *
		 * Compares this service listener object with another one.
		 *
		 * @param serviceInfo
		 *				The <code>RemoteServiceListenerInfo</code> object which is compared
		 *				with this.
		 *
		 * @return
		 *				True if both objects are equal, otherwise false.
		 */
		virtual bool operator==( const RemoteServiceListenerInfo& serviceInfo );
		
		/**		 
		 * Compares two service listener objects.
		 *
		 * @param info1
		 *				The first of two <code>RemoteServiceListenerInfo</code> objects.
		 *
		 * @return
		 *				The second <code>RemoteServiceListenerInfo</code> object which is compared
		 *				with the first one.
		 */
		virtual bool equals( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 );

		/**
		 * Assigns the passed <code>RemoteServiceListenerInfo</code> object to this object.
		 *
		 * @param serviceListenerInfo
		 *				The service listener object which is assigned to this.
		 *
		 * @return
		 *				This service listener object.
		 */			
		virtual RemoteServiceListenerInfo& operator=( const RemoteServiceListenerInfo &serviceListenerInfo );

		/**
		 * Returns the string representation of this service listener object.
		 *
		 * @return
		 *			The string representation.
		 */
		virtual string toString() const;
		
};

/** 
 * Smart pointer for <code>RemoteServiceInfo</code> objects.
 */
typedef SmartPtr<RemoteServiceListenerInfo> RemoteServiceListenerInfoPtr;

}}}}
#endif