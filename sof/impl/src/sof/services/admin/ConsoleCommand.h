#ifndef CONSOLE_COMMAND_H
#define CONSOLE_COMMAND_H

#include <string>
#include <vector>

#include "IAdministrationService.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

class ConsoleCommand
{
	public:		
		virtual string getName() = 0;
		virtual string getDescription() = 0;
		virtual int getParameterNum() = 0;
		virtual string execute( IAdministrationService* const adminService, vector<string> params ) = 0;
};

}}}
#endif