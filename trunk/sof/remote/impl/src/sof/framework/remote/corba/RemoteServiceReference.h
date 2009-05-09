#ifndef REMOTE_SERVICE_REFERENCE_H
#define REMOTE_SERVICE_REFERENCE_H

#include <string>

#include "sof/framework/ServiceReference.h"
#include "sof/framework/SOFException.h"

#include "./generated/CORBAObjects.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace std;

using namespace sof::framework;
using namespace sof::framework::remote::corba::generated;

class RemoteServiceReference : public ServiceReference
{
	private:
		string remoteObjectID;
		CORBAService_var remoteService;

	public:

		RemoteServiceReference( const string &name, const Properties &properties, CORBAService_var serviceObj, const string& objID );
		RemoteServiceReference( const RemoteServiceReference& serviceRef );
		virtual RemoteServiceReference &operator=( const RemoteServiceReference &serviceRef );
		virtual ~RemoteServiceReference();
		virtual string getRemoteServiceID() const;
		virtual CORBAService_var getRemoteService() const;
		virtual bool operator==( const RemoteServiceReference& serviceReference );
		virtual string toString() const;
		virtual IService::ConstPtr getService() const;

};

}}}}

#endif