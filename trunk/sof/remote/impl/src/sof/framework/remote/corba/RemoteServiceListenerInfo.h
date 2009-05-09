#ifndef REMOTE_SERVICE_LISTENER_INFO_H
#define REMOTE_SERVICE_LISTENER_INFO_H

#include <CORBA.h>

#include <string>

#include "sof/framework/ServiceListenerInfo.h"

#include "./generated/CORBAObjects.h"

using namespace sof::framework;
using namespace sof::framework::remote::corba::generated;

namespace sof { namespace framework { namespace remote { namespace corba {

class RemoteServiceListenerInfo : public ServiceListenerInfo
{
	private:
		CORBAServiceListener_var remoteServiceObject;
		string objID;

	public:
		RemoteServiceListenerInfo( const string& bundleName, const string &servName, CORBAServiceListener_var serviceObj, const string& objID );

		//RemoteServiceListenerInfo( const RemoteServiceListenerInfo& info );
		virtual ~RemoteServiceListenerInfo();
		virtual string getRemoteServiceListenerID() const;
		virtual CORBAServiceListener_var getRemoteServiceListener();
		virtual IServiceListener::ConstPtr getServiceListenerObj() const;
		virtual bool operator==( const RemoteServiceListenerInfo& serviceInfo );
		virtual bool equals( const ServiceListenerInfo& info1, const ServiceListenerInfo& info2 );
		virtual RemoteServiceListenerInfo& operator=( const RemoteServiceListenerInfo &serviceListenerInfo );
		virtual string toString() const;
		
};

}}}}
#endif