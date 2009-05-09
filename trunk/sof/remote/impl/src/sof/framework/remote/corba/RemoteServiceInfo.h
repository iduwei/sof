#ifndef REMOTE_SERVICE_INFO_H
#define REMOTE_SERVICE_INFO_H

#include <CORBA.h>

#include <string>

#include "sof/framework/ServiceInfo.h"

#include "./generated/CORBAObjects.h"

using namespace sof::framework;
using namespace sof::framework::remote::corba::generated;

namespace sof { namespace framework { namespace remote { namespace corba {

class RemoteServiceInfo : public ServiceInfo
{
	private:
		CORBAService_var remoteServiceObject;
		string objID;

	public:
		RemoteServiceInfo( const string &servName, CORBAService_var serviceObj, const string& objID, 
			const Properties &properties );

		virtual bool equals( const ServiceInfo& info1, const ServiceInfo& info2 );

		virtual ~RemoteServiceInfo();
		virtual string getRemoteServiceID() const;
		virtual CORBAService_var getRemoteService();
		virtual bool operator==( const RemoteServiceInfo& serviceInfo );
		virtual string toString() const;
		virtual IService::ConstPtr getService() const;
};

}}}}
#endif