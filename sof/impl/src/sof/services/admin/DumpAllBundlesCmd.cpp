#include "DumpAllBundlesCmd.h"

using namespace sof::services::admin;

DumpAllBundlesCmd::DumpAllBundlesCmd() 
{
}

string DumpAllBundlesCmd::getName()
{
	return "dab";
}

int DumpAllBundlesCmd::getParameterNum()
{
	return 0;
}

string DumpAllBundlesCmd::getDescription()
{
	return "Dumps the name of all started bundles.";
}

string DumpAllBundlesCmd::execute( IAdministrationService* const adminService, vector<string> params )
{
	return adminService->dumpAllBundleNames();
}