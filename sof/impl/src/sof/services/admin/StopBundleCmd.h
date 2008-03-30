#ifndef STOP_BUNDLE_CMD_H
#define STOP_BUNDLE_CMD_H

#include <string>
#include <vector>

#include "ConsoleCommand.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

class StopBundleCmd : public ConsoleCommand
{
	public:
		StopBundleCmd();
		string getName();
		string getDescription();
		int getParameterNum();
		string execute( IAdministrationService* const adminService, vector<string> params );
};

}}}

#endif