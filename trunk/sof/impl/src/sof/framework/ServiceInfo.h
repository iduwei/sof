#ifndef SERVICE_INFO_H
#define SERVICE_INFO_H

#include <string>

#include "IService.h"
#include "Properties.h"

#include "../util/logging/LoggerFactory.h"
#include "../util/logging/Logger.h"

#include <sstream>
#include <string>

using namespace std;

using namespace sof::util::logging;
using namespace sof::framework;

class ServiceInfo
{
	private:
		IService::ConstPtr service;
		string serviceName;
		Properties props;
		static Logger& logger;

	public:
		ServiceInfo( const string &servName, IService::ConstPtr service, const Properties &properties );
		~ServiceInfo();
		string getServiceName() const;
		Properties getProperties() const;
		IService::ConstPtr getService() const;
		string toString() const;
		bool operator==( const ServiceInfo& serviceInfo1 );
};
#endif