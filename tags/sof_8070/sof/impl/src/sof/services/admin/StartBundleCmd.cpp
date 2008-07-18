#include "StartBundleCmd.h"

using namespace sof::services::admin;

StartBundleCmd::StartBundleCmd() 
{
}

string StartBundleCmd::getName()
{
	return "stb";
}

int StartBundleCmd::getParameterNum()
{
	return 2;
}

string StartBundleCmd::getDescription()
{
	return "Starts a bundle (Parameters: bundle name, class name).";
}

string StartBundleCmd::execute( IAdministrationService* const adminService, vector<string> params )
{
	adminService->startBundle( params[0], params[1] );
	return "";
}