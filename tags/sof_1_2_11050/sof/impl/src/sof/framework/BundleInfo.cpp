#include "BundleInfo.h"

#include <sstream>

using namespace std;

using namespace sof::framework;


BundleInfo::BundleInfo( const string& bdleName, bool isSOFBundle, IBundleActivator* act, IBundleContext::ConstPtr bundleCtxt ) : activator(act), BundleInfoBase( bdleName, isSOFBundle, bundleCtxt )
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfo#ctor] Called." );
}

BundleInfo::~BundleInfo()
{
	logger.log( Logger::LOG_DEBUG, "[BundleInfo#destructor] Called." );
}


IBundleActivator* BundleInfo::getBundleActivator()
{
	return this->activator;
}
 
