#ifndef ISERVICE_REGISTRATION_IMPL_H
#define ISERVICE_REGISTRATION_IMPL_H

#include "IServiceRegistration.h"
#include "Registry.h"
#include "ServiceInfo.h"
#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"

namespace sof { namespace framework {

using namespace sof::framework;
using namespace sof::util::logging;

class IServiceRegistrationImpl : public IServiceRegistration
{
	private:
		Registry* const registry;
		ServiceInfo* const serviceInfo;
		string bundleName;
		static Logger& logger;

	public:
		IServiceRegistrationImpl( const string& bundleName, Registry* const reg, ServiceInfo* const serviceInfo );
		~IServiceRegistrationImpl();
		virtual void unregister();
};

}}
#endif