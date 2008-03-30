#ifndef START_BUNDLES_FROM_FILE_CMD_H
#define START_BUNDLES_FROM_FILE_CMD_H

#include <string>
#include <vector>

#include "ConsoleCommand.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

class StartBundlesFromFileCmd : public ConsoleCommand
{
	public:
		StartBundlesFromFileCmd();
		string getName();
		string getDescription();
		int getParameterNum();
		string execute( IAdministrationService* const adminService, vector<string> params );
};

}}}

#endif 