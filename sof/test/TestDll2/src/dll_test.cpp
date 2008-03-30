// Dies ist die Haupt-DLL.

#include <windows.h>

#include <stdlib.h>
#include <string>
#include <iostream>
#include "dll_test.h"
#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/IBundleActivator.h"
#include "TestBundleActivator.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"


#define DLL extern "C" __declspec(dllexport)

using namespace std;
using namespace sof::instantiation;
using namespace sof::framework;
using namespace sof::util::logging;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{		
	if(ul_reason_for_call==DLL_THREAD_ATTACH)
  {
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[dll_test2#DllMain] Called, dll thread attach." );
  }

if(ul_reason_for_call==DLL_THREAD_DETACH)
  {
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[dll_test2#DllMain] Called, dll thread detach." );
  }

if(ul_reason_for_call==DLL_PROCESS_ATTACH)
  {
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[dll_test2#DllMain] Called, dll process attach." );
  }

if(ul_reason_for_call==DLL_PROCESS_DETACH)
  {
	  LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[dll_test2#DllMain] Called, dll process detach." );
  }
	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[dll_test2#DllMain] Left." );
    return TRUE;
}


DLL IBundleActivator* createObject( const string &className )
{	
	ObjectCreator<IBundleActivator> OC_BUNDLE_ACTIVATOR;

	LoggerFactory::getLogger( "Test" ).log( Logger::DEBUG, "[dll_test2#createObject] Loading instance of class '%1'", className );
	return OC_BUNDLE_ACTIVATOR.createObject( className );	
}