#ifndef START_BUNDLE_FROM_DLL_CMD_H
#define START_BUNDLE_FROM_DLL_CMD_H

#include <string>
#include <vector>

#include "ConsoleCommand.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

/**
 * The <code>StartBundleFromDLLCmd<code> represents a console command
 * which starts a bundle from DLL.<br>
 * Example:<br>
 * <code>stbdll <bundle name> <class name> <lib path> <lib name></code>
 *
 * @author magr74
 */
class StartBundleFromDLLCmd : public ConsoleCommand
{
	public:

		/**
		 * Creates instances of class </code>StartBundleFromDLLCmd</code>.
		 */
		StartBundleFromDLLCmd();

		/**
		 * @see sof::services::admin::ConsoleCommand::getName
		 */
		string getName();

		/**
		 * @see sof::services::admin::ConsoleCommand::getDescription
		 */
		string getDescription();

		/**
		 * @see sof::services::admin::ConsoleCommand::getParameterNum
		 */
		int getParameterNum();

		/**
		 * @see sof::services::admin::ConsoleCommand::execute
		 */
		string execute( IAdministrationService* const adminService, vector<string> params );
};

}}}

#endif