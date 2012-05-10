#include <CORBA.h>
#include <coss/CosNaming.h>

#include <list>
#include <vector>
#include <iostream>

#include "sof/framework/remote/corba/CORBAHelper.h"
#include "sof/framework/remote/corba/registry/CORBARegistryImpl.h"
#include "sof/util/threading/SingleThreaded.h"

using namespace sof::framework::remote;
using namespace sof::framework::remote::corba;
using namespace sof::framework::remote::corba::namingservice;
using namespace sof::framework::remote::corba::registry;
using namespace sof::util::threading;

int main( int argc, char **argv)
{
	vector<string> args;
	for ( int i=0; i<argc; i++ )
	{
		args.push_back( argv[i] );
	}

	CORBAHelper corbaHelper( args );

	// Note: Use Mutex-Class if you want to synchronize the access to the remote registry!
	CORBARegistryImpl<SingleThreaded> registry;
	CORBA::Object_var obj = corbaHelper.activateObject( &registry );
	if ( corbaHelper.useNamingService() )
	{
		cout << "Use naming service." << endl;
		corbaHelper.registerObject( obj, CORBAHelper::REMOTE_REGISTRY_PATH, CORBAHelper::REMOTE_REGISTRY_NAME );
		cout << "Registry object registered at naming service." << endl;
	}
	cout << "Registry service started!" << endl;
	corbaHelper.startAndWait();
    return 0;
}

