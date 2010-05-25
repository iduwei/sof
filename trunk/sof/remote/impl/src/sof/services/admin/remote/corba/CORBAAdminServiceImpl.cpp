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
	logger.log( Logger::LOG_DEBUG, "[CORBAAdminServiceImpl#ctor] Called." );
}

CORBAAdminServiceImpl::~CORBAAdminServiceImpl()
{
	logger.log( Logger::LOG_DEBUG, "[CORBAAdminServiceImpl#destructor] Called." );
}

CORBABundleNameSequence* CORBAAdminServiceImpl::getBundleNames()
{
	logger.log( Logger::LOG_DEBUG, "[CORBAAdminServiceImpl#getBundleNames] Called." );
	vector<string> bundleNames = this->adminProvider.getBundleNames();
	return DataConverter::convert( bundleNames );	
}

CORBAAdminServiceInfoSequence* CORBAAdminServiceImpl::getUsedServices( const char* bundleName ) 
{
	logger.log( Logger::LOG_DEBUG, "[CORBAAdminServiceImpl#getUsedServices] Called, bundleName: %1",
		bundleName );

	BundleInfoBase& bundleInfo = this->adminProvider.getBundleInfo( bundleName );
	
	return DataConverter::convert( bundleInfo.getUsedServices() );	
}

CORBAAdminServiceInfoSequence* CORBAAdminServiceImpl::getRegisteredServices( const char* bundleName )
{
	string bName( bundleName );
	logger.log( Logger::LOG_DEBUG, "[CORBAAdminServiceImpl#getRegisteredServices] Called, bundleName: %1", bName );
	BundleInfoBase& bundleInfo = this->adminProvider.getBundleInfo( bName );
	logger.log( Logger::LOG_DEBUG, "[CORBAAdminServiceImpl#getRegisteredServices] Convert bundle info: %1",
		bundleInfo.toString() );
	return DataConverter::convert( bundleInfo.getRegisteredServices() );	
}

CORBAAdminServiceListenerInfoSequence* CORBAAdminServiceImpl::getRegisteredServiceListeners( const char* bundleName ) 
{
	string bName( bundleName );
	logger.log( Logger::LOG_DEBUG, "[CORBAAdminServiceImpl#getRegisteredServiceListeners] Called, bundleName: %1",
		bName );

	BundleInfoBase& bundleInfo = this->adminProvider.getBundleInfo( bName );
	
	return DataConverter::convert( bundleInfo.getRegisteredListeners() );
}
