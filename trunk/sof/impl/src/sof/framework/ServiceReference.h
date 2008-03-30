#ifndef SERVICE_REFERENCE_H
#define SERVICE_REFERENCE_H

#include <string>

#include "Properties.h"
#include "IService.h"

namespace sof {
	namespace framework {

using namespace std;
using namespace sof::framework;

class ServiceReference 
{
	private:		
		string serviceName;
		Properties props;
		IService::ConstPtr service;

	public:
		ServiceReference( const string &name, const Properties &properties, const IService::ConstPtr serv );
		string getServiceName() const;
		Properties getServiceProperties() const;
		IService::ConstPtr getService() const;

};

}}
#endif