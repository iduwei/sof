#ifndef START_BUNDLES_FROM_FILE_CMD_H
#define START_BUNDLES_FROM_FILE_CMD_H

#include <string>
#include <vector>

#include "ConsoleCommand.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

/**
 * The <code>StartBundlesFromFileCmd<code> represents a console command
 * which starts bundles specified in a configuration file.<br>
 * Example:<br>
 * <code>stbfile <config_file></code>
 */
class StartBundlesFromFileCmd : public ConsoleCommand
{
	public:

		/**
		 * Creates instances of class </code>StartBundlesFromFileCmd</code>.
		 */
		StartBundlesFromFileCmd();

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