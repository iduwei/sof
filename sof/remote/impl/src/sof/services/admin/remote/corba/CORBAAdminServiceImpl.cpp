#include "CORBAAdminServiceImpl.h"

#include "DataConverter.h"
#include "sof/framework/BundleInfoBase.h"
#include "../../../../framework/remote/corba/RemoteServiceInfo.h"

using namespace sof::framework;
using namespace sof::services::admin::remote::corba;
using namespace sof::framework::remote::corba;
using namespace sof::util::logging;

Logger& CORBAAdminServiceImpl::logger = LoggerFactory::getLogger( "Remote-Framework" );

CORBAAdminServiceImpl::CORBAAdminServiceImpl( IAdministrationProvider& provider ) : adminProvider( provider )
{	
	logger.log( Logger::DEBUG, "[CORBAAdminServiceImpl#ctor] Called." );
}

CORBAAdminServiceImpl::~CORBAAdminServiceImpl()
{
	logger.log( Logger::DEBUG, "[CORBAAdminServiceImpl#destructor] Called." );
}

CORBABundleNameSequence* CORBAAdminServiceImpl::getBundleNames()
{
	logger.log( Logger::DEBUG, "[CORBAAdminServiceImpl#getBundleNames] Called." );
	vector<string> bundleNames = this->adminProvider.getBundleNames();
	return DataConverter::convert( bundleNames );	
}

CORBAAdminServiceInfoSequence* CORBAAdminServiceImpl::getUsedServices( const char* bundleName ) 
{
	logger.log( Logger::DEBUG, "[CORBAAdminServiceImpl#getUsedServices] Called, bundleName: %1",
		bundleName );

	BundleInfoBase& bundleInfo = this->adminProvider.getBundleInfo( bundleName );
	
	return DataConverter::convert( bundleInfo.getUsedServices() );	
}

CORBAAdminServiceInfoSequence* CORBAAdminServiceImpl::getRegisteredServices( const char* bundleName )
{
	logger.log( Logger::DEBUG, "[CORBAAdminServiceImpl#getRegisteredServices] Called, bundleName: %1",
		bundleName );
	BundleInfoBase& bundleInfo = this->adminProvider.getBundleInfo( bundleName );
	
	return DataConverter::convert( bundleInfo.getRegisteredServices() );	
}

CORBAAdminServiceListenerInfoSequence* CORBAAdminServiceImpl::getRegisteredServiceListeners( const char* bundleName ) 
{
	logger.log( Logger::DEBUG, "[CORBAAdminServiceImpl#getRegisteredServiceListeners] Called, bundleName: %1",
		bundleName );

	BundleInfoBase& bundleInfo = this->adminProvider.getBundleInfo( bundleName );
	
	return DataConverter::convert( bundleInfo.getRegisteredListeners() );
}
