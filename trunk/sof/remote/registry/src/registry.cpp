#include <CORBA.h>
#include <coss/CosNaming.h>
#include "sof/framework/remote/corba/CORBAHelper.h"
#include "sof/framework/remote/corba/namingservice/CORBANamingService.h"
#include "sof/framework/remote/corba/registry/CORBARegistryImpl.h"
#include "sof/framework/remote/corba/RemoteSOFLauncher.h"

#include <list>
#include <vector>
#include <iostream>

using namespace sof::framework::remote;
using namespace sof::framework::remote::corba;
using namespace sof::framework::remote::corba::namingservice;
using namespace sof::framework::remote::corba::registry;

int main( int argc, char **argv)
{
	vector<string> args;

	for ( int i=0; i<argc; i++ )
	{
		args.push_back( argv[i] );
	}

	CORBAHelper corbaHelper( args );
	CORBARegistryImpl registry;
	CORBA::Object_var obj = corbaHelper.activateObject( &registry );
	corbaHelper.registerObject( obj, CORBAHelper::REMOTE_REGISTRY_PATH, CORBAHelper::REMOTE_REGISTRY_NAME );
	cout << "Registry service started!" << endl;
	corbaHelper.startAndWait();
    return 0;
}

