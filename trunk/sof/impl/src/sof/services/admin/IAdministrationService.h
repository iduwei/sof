#ifndef IADMINISTRATION_SERVICE_H
#define IADMINISTRATION_SERVICE_H

#include <string>
#include <vector>

using namespace std;

namespace sof { namespace services { namespace admin {

class IAdministrationService
{
	public:
		virtual vector<string> getBundleNames() = 0;			
		virtual string dumpBundleInfo( const string& bundleName ) = 0;
		virtual void stopBundle( const string& bundleName ) = 0;
		virtual void stopAllBundles() = 0;
		virtual void startBundleFromDLL( const string& bundleName, const string& className, const string& libPath, const string& libName ) = 0;
		virtual void startBundle( const string& bundleName, const string& className ) = 0;
		virtual void startBundlesFromConfigFile( const string& configFile ) = 0;
};

}}}
#endif