#include "StopBundleCmd.h"

using namespace sof::services::admin;

StopBundleCmd::StopBundleCmd() 
{
}

string StopBundleCmd::getName()
{
	return "spb";
}

int StopBundleCmd::getParameterNum()
{
	return 1;
}

string StopBundleCmd::getDescription()
{
	return "Stops a bundle (Parameters: bundle name).";
}

string StopBundleCmd::execute( IAdministrationService* const adminService, vector<string> params )
{
	adminService->stopBundle( params[0] );
	return "";
}