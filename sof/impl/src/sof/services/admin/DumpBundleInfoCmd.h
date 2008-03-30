#ifndef DUMP_BUNDLE_INFO_CMD_H
#define DUMP_BUNDLE_INFO_CMD_H

#include <string>
#include <vector>

#include "ConsoleCommand.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

class DumpBundleInfoCmd : public ConsoleCommand
{
	public:
		DumpBundleInfoCmd();
		string getName();
		string getDescription();
		int getParameterNum();
		string execute( IAdministrationService* const adminService, vector<string> params );
};

}}}

#endif