#include "ServiceReference.h"

#include <string>

using namespace std;
using namespace sof::framework;

ServiceReference::ServiceReference( const string &name, const Properties &properties, const IService::ConstPtr serv ) : serviceName( name ), props( properties ), service( serv )
{
}

string ServiceReference::getServiceName() const
{
	return this->serviceName;
}

Properties ServiceReference::getServiceProperties() const
{
	return this->props;
}

IService* ServiceReference::getService() const
{
	return this->service;
}