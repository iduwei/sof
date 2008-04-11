#ifndef STOP_BUNDLE_CMD_H
#define STOP_BUNDLE_CMD_H

#include <string>
#include <vector>

#include "ConsoleCommand.h"

namespace sof { namespace services { namespace admin {

using namespace std;

using namespace sof::services::admin;

/**
 * The <code>StopBundleCmd<code> represents a console command
 * which stops a bundle.<br>
 * Example:<br>
 * <code>spb <bundle_name></code>
 */
class StopBundleCmd : public ConsoleCommand
{
	public:

		/**
		 * Creates instances of class </code>StopBundleCmd</code>.
		 */
		StopBundleCmd();

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