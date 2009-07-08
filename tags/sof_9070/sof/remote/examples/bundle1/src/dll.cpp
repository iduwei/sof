#include <windows.h>

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/remote/corba/IRemoteBundleActivator.h"
#include "sof/util/logging/LoggerFactory.h"
#include "sof/util/logging/Logger.h"



#define DLL extern "C" __declspec(dllexport)

using namespace std;
using namespace sof::framework;
using namespace sof::framework::remote::corba;
using namespace sof::instantiation;
using namespace sof::util::logging;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{			
	if(ul_reason_for_call==DLL_THREAD_ATTACH)
	{
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[bundle1_dll#DllMain] Called, dll thread attach." );
	}

	if(ul_reason_for_call==DLL_THREAD_DETACH)
	{
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[bundle1_dll#DllMain] Called, dll thread detach." );
	}

	if(ul_reason_for_call==DLL_PROCESS_ATTACH)
	{
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[bundle1_dll#DllMain] Called, dll process attach." );
	}

	if(ul_reason_for_call==DLL_PROCESS_DETACH)
	{
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[bundle1_dll#DllMain] Called, dll process detach." );
	}

	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[bundle1_dll#DllMain] Left." );
	return TRUE;
}


DLL IRemoteBundleActivator* createObject( const string &className )
{	
	ObjectCreator<IRemoteBundleActivator> OC_BUNDLE_ACTIVATOR;
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[bundle1_dll#createObject] Loading instance of class '%1'.", className );
	return OC_BUNDLE_ACTIVATOR.createObject( className );					
}

