#ifdef WIN32
#include <windows.h>
#endif 

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/remote/corba/IRemoteBundleActivator.h"

using namespace std;
using namespace sof::instantiation;
using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::framework::remote::corba;

#ifdef WIN32
#define DLL extern "C" __declspec(dllexport)

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{				
	return TRUE;
}
#elif UNIX
#define DLL extern "C" __attribute__((visibility("default")))
#endif

DLL IRemoteBundleActivator* createObject( const string &className )
{	
	ObjectCreator<IRemoteBundleActivator> OC_BUNDLE_ACTIVATOR;
	LoggerFactory::getLogger( "Test" ).log( Logger::LOG_DEBUG, "[bundle1_dll#createObject] Loading instance of class '%1'.", className );
	return OC_BUNDLE_ACTIVATOR.createObject( className );						
}

