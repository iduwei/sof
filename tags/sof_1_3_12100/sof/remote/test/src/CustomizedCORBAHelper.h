#ifndef CUSTOMIZED_CORBA_HELPER_H
#define CUSTOMIZED_CORBA_HELPER_H

#include "sof/framework/remote/corba/CORBAHelper.h"
#include "sof/framework/remote/corba/registry/CORBARegistryImpl.h"
#include "sof/util/threading/SingleThreaded.h"

#include "UnitTestLogger.h"

using namespace sof::framework::remote::corba;
using namespace sof::framework::remote::corba::registry;
using namespace sof::util::threading;

/**
 * The <code>CustomizedCORBAHelper</code> class modifies the behaviour of the 
 * <code>CORBAHelper</code> class in a manner that unit tests don't need a naming service
 * process.
 */
class CustomizedCORBAHelper : public CORBAHelper
{
	private:

		/**
		 * The remote registry object the SOF process usually gets from the naming service.
		 */
		CORBARegistryImpl<SingleThreaded> registry;		

	public:

		/** 
		 * Creates instances of class <code>CustomzedCORBAHelper</code>.
		 *
		 * @param args
		 *				The parameters for initializing.
		 */
		CustomizedCORBAHelper( const vector<string>& args );

		/**
		 * Returns the remote registry object without calling the
		 * naming service.
		 */
		list<CORBA::Object_var> findObjects( const string& path);

};

#endif