#ifndef DATA_CONVERTER_H
#define DATA_CONVERTER_H

#include <vector>

#include "./generated/CORBAAdminObjects.h"
#include "sof/framework/ServiceInfo.h"
#include "../../../../framework/remote/corba/RemoteServiceListenerInfo.h"
#include "../../../../framework/remote/corba/RemoteServiceInfo.h"
#include "sof/framework/Properties.h"

namespace sof { namespace services { namespace admin { namespace remote { namespace corba {

using namespace std;

using namespace sof::framework;
using namespace sof::services::admin::remote::corba::generated;
using namespace sof::framework::remote::corba;

class DataConverter
{
	public:
		static CORBABundleNameSequence_var convert( const vector<string>& bundleNames );
		static CORBAAdminServiceProps_var convert( const Properties& props );
		static CORBAAdminServiceInfo_var convert( const RemoteServiceInfo& serviceInfo );
		static CORBAAdminServiceListenerInfo_var convert( const RemoteServiceListenerInfo& serviceListenerInfo );
		static CORBAAdminServiceInfoSequence_var convert( const vector<ServiceInfo*>& serviceInfo );
		static CORBAAdminServiceListenerInfoSequence_var convert( const vector<ServiceListenerInfo*>& serviceListenerInfo );
};
}}}}}
#endif