#ifndef CORBA_ADMIN_SERVICE_IMPL_H
#define CORBA_ADMIN_SERVICE_IMPL_H

#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/services/admin/IAdministrationProvider.h"
#include "./generated/CORBAAdminObjects.h"

namespace sof { namespace services { namespace admin { namespace remote { namespace corba { 

using namespace sof::services::admin::remote::corba::generated;
using namespace sof::util::logging;
using namespace sof::services::admin;

class CORBAAdminServiceImpl : virtual public POA_sof::services::admin::remote::corba::generated::CORBAAdminService 
{
	private:
		static Logger& logger;
		IAdministrationProvider& adminProvider;

	public:
		CORBAAdminServiceImpl( IAdministrationProvider& adminProvider );
		virtual ~CORBAAdminServiceImpl();
		virtual CORBABundleNameSequence* getBundleNames();
		virtual CORBAAdminServiceInfoSequence* getUsedServices( const char* bundleName );
		virtual CORBAAdminServiceInfoSequence* getRegisteredServices( const char* bundleName );
		virtual CORBAAdminServiceListenerInfoSequence* getRegisteredServiceListeners( const char* bundleName );
};

}}}}}
#endif