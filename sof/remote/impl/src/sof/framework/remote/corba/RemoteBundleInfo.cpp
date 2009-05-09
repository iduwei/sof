#include "RemoteBundleInfo.h"

#include <sstream>

using namespace std;

using namespace sof::framework::remote::corba;


RemoteBundleInfo::RemoteBundleInfo( const string& bdleName, IRemoteBundleActivator* act, IBundleContext::ConstPtr bundleCtxt ) : activator(act), BundleInfoBase( bdleName, bundleCtxt )
{
	logger.log( Logger::DEBUG, "[RemoteBundleInfo#ctor] Called." );
}

RemoteBundleInfo::~RemoteBundleInfo()
{
	logger.log( Logger::DEBUG, "[RemoteBundleInfo#destructor] Called." );
}


IRemoteBundleActivator* RemoteBundleInfo::getRemoteBundleActivator()
{
	return this->activator;
}