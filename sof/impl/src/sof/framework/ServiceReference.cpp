#include "ServiceReference.h"

#include <string>

using namespace std;
using namespace sof::framework;

ServiceReference::ServiceReference( const string &name, const Properties &properties, const IService::ConstPtr serv ) : serviceName( name ), props( properties ), service( serv )
{
}

ServiceReference::~ServiceReference()
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

IService::ConstPtr ServiceReference::getService() const
{
	return this->service;
}

string ServiceReference::toString() const
{	
	ostringstream refStream;
	refStream << "ServiceReference={";
	refStream << "serviceName=" << this->serviceName << ", ";
	refStream << this->props.toString();
	refStream << "}";
	return refStream.str();
}