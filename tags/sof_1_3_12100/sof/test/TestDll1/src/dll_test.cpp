#ifdef WIN32
#include <windows.h>
#endif 

#include <stdlib.h>
#include <string>
#include <iostream>

#include "ITest.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/IBundleActivator.h"

using namespace std;
using namespace sof::instantiation;
using namespace sof::framework;
using namespace sof::util::logging;

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

DLL ITest* createObject( const string &className )
{	
	cout << "DLL loaded" << endl;
	ObjectCreator<ITest> OC;
	return OC.createObject( className );					
}


