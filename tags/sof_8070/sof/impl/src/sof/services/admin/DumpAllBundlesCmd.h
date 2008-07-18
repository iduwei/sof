#ifndef DUMP_ALL_BUNDLES_CMD_H
#define DUMP_ALL_BUNDLES_CMD_H

#include <string>
#include <vector>

#include "ConsoleCommand.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

/**
 * The <code>DumpAllBundlesCmd<code> represents a console command
 * which dumps the name of all started bundles<br>
 * Example:<br>
 * <code>dab <bundle_name></code>
 */
class DumpAllBundlesCmd : public ConsoleCommand
{
	public:

		/**
		 * Creates instances of class </code>DumpAllBundlesCmd</code>.
		 */
		DumpAllBundlesCmd();

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