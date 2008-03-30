#include "DumpBundleInfoCmd.h"

using namespace sof::services::admin;

DumpBundleInfoCmd::DumpBundleInfoCmd() 
{
}

string DumpBundleInfoCmd::getName()
{
	return "dbi";
}

int DumpBundleInfoCmd::getParameterNum()
{
	return 1;
}

string DumpBundleInfoCmd::getDescription()
{
	return "Dumps the bundle data which are registered services, used services, registered listeners (Parameters: bundle name).";
}

string DumpBundleInfoCmd::execute( IAdministrationService* const adminService, vector<string> params )
{
	return adminService->dumpBundleInfo( params[0] );
}