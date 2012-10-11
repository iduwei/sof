#include "StartBundleFromDLLCmd.h"

using namespace sof::services::admin;

StartBundleFromDLLCmd::StartBundleFromDLLCmd() 
{
}

string StartBundleFromDLLCmd::getName()
{
	return "stbdll";
}

int StartBundleFromDLLCmd::getParameterNum()
{
	return 4;
}

string StartBundleFromDLLCmd::getDescription()
{
	return "Starts a bundle from DLL (Parameters: bundle name, class name, lib path, lib name).";
}

string StartBundleFromDLLCmd::execute( IAdministrationService* const adminService, vector<string> params )
{
	adminService->startBundleFromDLL( params[0], params[1], params[2], params[3] );
	return "";
}