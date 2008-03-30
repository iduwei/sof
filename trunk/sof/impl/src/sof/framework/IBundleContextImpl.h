#ifndef IBUNDLE_CONTEXT_IMPL_H
#define IBUNDLE_CONTEXT_IMPL_H

#include <string>
#include "IService.h"
#include "IBundleContext.h"
#include "Properties.h"
#include "IServiceListener.h"
#include "IServiceRegistration.h"
#include "Registry.h"
#include "../util/logging/Logger.h"

namespace sof { 
namespace framework {

using namespace std;
using namespace sof::framework;
using namespace sof::util::logging;

class IBundleContextImpl : public IBundleContext
{
	private:
		Registry* const registry;
		static Logger& logger;
		string bundleName;

	public:
		IBundleContextImpl( const string& bundleName, Registry* const reg );
		virtual ~IBundleContextImpl();
		virtual IServiceRegistration::ConstPtr registerService( const string &className, IService::ConstPtr service, const Properties &dict );
		virtual void addServiceListener( IServiceListener::ConstPtr serviceListener, const string &serviceName );
		virtual void removeServiceListener( IServiceListener::ConstPtr serviceListener );
};

}}
#endif