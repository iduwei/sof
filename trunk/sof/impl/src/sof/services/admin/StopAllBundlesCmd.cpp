#include "StopAllBundlesCmd.h"

using namespace sof::services::admin;

StopAllBundlesCmd::StopAllBundlesCmd() 
{
}

string StopAllBundlesCmd::getName()
{
	return "spab";
}

int StopAllBundlesCmd::getParameterNum()
{
	return 0;
}

string StopAllBundlesCmd::getDescription()
{
	return "Stops all bundles.";
}

string StopAllBundlesCmd::execute( IAdministrationService* const adminService, vector<string> params )
{
	adminService->stopAllBundles();
	return "";
}