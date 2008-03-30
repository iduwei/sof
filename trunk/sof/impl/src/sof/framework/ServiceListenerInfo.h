#ifndef SERVICE_LISTENER_INFO_H
#define SERVICE_LISTENER_INFO_H

#include <string>

#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"

#include "IServiceListener.h"

namespace sof { namespace framework {

using namespace std;

using namespace sof::util::logging;
using namespace sof::framework;

class ServiceListenerInfo
{
	private:
		string bundleName;
		string serviceName;
		IServiceListener::ConstPtr serviceListenerObj;
		static Logger& logger;

	public:
		ServiceListenerInfo( const string& bundleName, const string& serviceName, IServiceListener::ConstPtr serviceListener );
		~ServiceListenerInfo();
		string getBundleName() const;
		string getServiceName() const;
		IServiceListener::ConstPtr getServiceListenerObj() const;
		bool operator==( const ServiceListenerInfo& info1 );
		string toString() const;
};

}}

#endif