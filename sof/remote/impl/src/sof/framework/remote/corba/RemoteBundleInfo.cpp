#include "RemoteBundleInfo.h"

#include <sstream>

using namespace std;

using namespace sof::framework::remote::corba;


RemoteBundleInfo::RemoteBundleInfo( const string& bdleName, bool isSOFBundle, IRemoteBundleActivator* act, IBundleContext::ConstPtr bundleCtxt ) : activator(act), BundleInfoBase( bdleName, isSOFBundle, bundleCtxt )
{
	logger.log( Logger::LOG_DEBUG, "[RemoteBundleInfo#ctor] Called." );
}

RemoteBundleInfo::~RemoteBundleInfo()
{
	logger.log( Logger::LOG_DEBUG, "[RemoteBundleInfo#destructor] Called." );
}


IRemoteBundleActivator* RemoteBundleInfo::getRemoteBundleActivator()
{
	return this->activator;
}