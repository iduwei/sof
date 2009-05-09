#ifndef REMOTE_BUNDLE_INFO_H
#define REMOTE_BUNDLE_INFO_H

#include <vector>
#include <string>

#include "IRemoteBundleActivator.h"
#include "sof/framework/BundleInfoBase.h"

namespace sof { namespace framework { namespace remote { namespace corba {

using namespace std;

using namespace sof::framework;
using namespace sof::framework::remote::corba;
using namespace sof::util::logging;

/**
 * The <code>RemoteBundleInfo</code> class contains all the relevant information
 * of a specific bundle:
 * <ul>
 *		<li>The name of the bundle.
 *		<li>The bundle activator.
 *		<li>The bundle context.
 *		<li>The list of services which were registered by the bundle.
 *		<li>The list of services which are used by the bundle.
 *		<li>The list of service listeners.<br>
 * </ul>
 */
class RemoteBundleInfo : public BundleInfoBase
{
	private:		

		/**
		 * The bundle activator instance.
		 */
		IRemoteBundleActivator* activator;

		
	public:

		/**
		 * Creates instances of class <code>BundleInfo</code>.
		 *
		 * @param bundleName
		 *			The name of the bundle.
		 * @param act
		 *			The bundle activator instance.
		 * @param bundleCtxt
		 *			The bundle context.
		 */
		RemoteBundleInfo( const string& bundleName, IRemoteBundleActivator* act, IBundleContext::ConstPtr bundleCtxt );

		/**
		 * The destructor for cleaning resources.
		 */
		virtual ~RemoteBundleInfo();

		/**
		 * Returns the pointer to the bundle activator instance.
		 * 
		 * @return
		 *		The pointer to bundle activator instance.
		 */
		virtual IRemoteBundleActivator* getRemoteBundleActivator();
		
};

}}}}
#endif