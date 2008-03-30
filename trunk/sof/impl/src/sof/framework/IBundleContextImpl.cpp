#include "IBundleContextImpl.h"
#include "ServiceInfo.h"
#include "IServiceRegistration.h"
#include "IServiceRegistrationImpl.h"
#include "../util/logging/LoggerFactory.h"

using namespace std;
using namespace sof::framework;
using namespace sof::util::logging;

Logger& IBundleContextImpl::logger = LoggerFactory::getLogger( "Framework" );

IBundleContextImpl::IBundleContextImpl( const string& bdleName, Registry* const reg ) : bundleName( bdleName ), registry( reg )
{
	logger.log( Logger::DEBUG, "[IBundleContextImpl#ctor] Called, bundle name: %1", bdleName );
}

IBundleContextImpl::~IBundleContextImpl()
{
	logger.log( Logger::DEBUG, "[IBundleContextImpl#destructor] Called." );
}

IServiceRegistration::ConstPtr IBundleContextImpl::registerService( const string& className, IService::ConstPtr service, const Properties &dict )
{
	logger.log( Logger::DEBUG, "[IBundleContextImpl#registerService] Called, bundle name: %1, service name: %2", this->bundleName, className );
	ServiceInfo *serviceInfo = new ServiceInfo( className, service, dict );
	this->registry->addServiceInfo( this->bundleName, className, serviceInfo );
	return new IServiceRegistrationImpl( bundleName, registry, serviceInfo );
}

void IBundleContextImpl::addServiceListener( IServiceListener::ConstPtr serviceListener, const string &serviceName )
{
	logger.log( Logger::DEBUG, "[IBundleContextImpl#addServiceListener] Called, bundle name: %1, service name: %2", this->bundleName, serviceName );
	this->registry->addServiceListener( this->bundleName, serviceListener, serviceName );
}

void IBundleContextImpl::removeServiceListener( IServiceListener::ConstPtr serviceListener )
{
	logger.log( Logger::DEBUG, "[IBundleContextImpl#removeServiceListener] Called, bundle name: %1", this->bundleName );	
	this->registry->removeServiceListener( this->bundleName, serviceListener );
}