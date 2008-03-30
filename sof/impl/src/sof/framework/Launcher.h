#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <vector>

#include "IBundleActivator.h"
#include "Registry.h"

#include "../config/BundleConfiguration.h"
#include "../instantiation/ObjectCreator.h"
#include "../util/logging/Logger.h"


namespace sof { namespace framework {

using namespace std;

using namespace sof::config;
using namespace sof::framework;
using namespace sof::instantiation;
using namespace sof::util::logging;

class Launcher
{
	private:
		ObjectCreator<IBundleActivator> objectCreator;
		Registry registry;
		static Logger& logger;

	public:
		Launcher();
		void setLogLevel( Logger::LogLevel level );
		void start( vector<BundleConfiguration> &configuration );
		void stop();
		void startBundle( BundleConfiguration bundleConfig );
		void stopBundle( const string& bundleName );
		void startAdministrationBundle();
		void setAdministrationBundleEnabled( bool );
		vector<string> getBundleNames();			
		string dumpBundleInfo( const string& bundleName );
		Registry& getRegistry();
};

}}

#endif