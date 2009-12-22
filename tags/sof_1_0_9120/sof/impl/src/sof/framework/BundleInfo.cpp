#include "BundleInfo.h"

#include <sstream>

using namespace std;

using namespace sof::framework;


BundleInfo::BundleInfo( const string& bdleName, IBundleActivator* act, IBundleContext::ConstPtr bundleCtxt ) : activator(act), BundleInfoBase( bdleName, bundleCtxt )
{
	logger.log( Logger::DEBUG, "[BundleInfo#ctor] Called." );
}

BundleInfo::~BundleInfo()
{
	logger.log( Logger::DEBUG, "[BundleInfo#destructor] Called." );
}


IBundleActivator* BundleInfo::getBundleActivator()
{
	return this->activator;
}
 
