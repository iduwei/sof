#include "StartBundlesFromFileCmd.h"

using namespace sof::services::admin;

StartBundlesFromFileCmd::StartBundlesFromFileCmd() 
{
}

string StartBundlesFromFileCmd::getName()
{
	return "stbfile";
}

int StartBundlesFromFileCmd::getParameterNum()
{
	return 1;
}

string StartBundlesFromFileCmd::getDescription()
{
	return "Starts bundles from configuration file.";
}

string StartBundlesFromFileCmd::execute( IAdministrationService* const adminService, vector<string> params )
{
	adminService->startBundlesFromConfigFile( params[0] );
	return "";
}