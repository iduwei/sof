#ifndef IADMINISTRATION_SERVICE_IMPL_H
#define IADMINISTRATION_SERVICE_IMPL_H

#include <string>
#include <vector>
#include <map>

#include "../../util/logging/Logger.h"
#include "../../util/logging/LoggerFactory.h"
#include "../../framework/Launcher.h"
#include "IAdministrationService.h"
#include "ConsoleCommand.h"

using namespace std;
using namespace sof::framework;
using namespace sof::util::logging;

namespace sof { namespace services { namespace admin {

class IAdministrationServiceImpl : public IAdministrationService
{
	private:
		Launcher* launcher;
		static Logger& logger;
		map<string,ConsoleCommand*> cmdMap;		

	public:
		IAdministrationServiceImpl( Launcher* launcher );
		void startConsole();
		void stopConsole();
		vector<string> getBundleNames();			
		string dumpBundleInfo( const string& bundleName );
		void stopBundle( const string& bundleName );
		void stopAllBundles();
		void startBundleFromDLL( const string& bundleName, const string& className, const string& libPath, const string& libName );
		void startBundle( const string& bundleName, const string& className );
		void startBundlesFromConfigFile( const string& configFile );
};

}}}
#endif