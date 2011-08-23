#ifndef ILOCAL_SERVICE_TRACKER_CUSTOMIZER_H
#define ILOCAL_SERVICE_TRACKER_CUSTOMIZER_H

#include "sof/framework/IServiceTrackerCustomizer.h"

namespace sof { namespace framework {

using namespace sof::framework;

/**
 * The <code>ILocalServiceTrackerCustomizer</code> class provides the same
 * functionality as the <code>IServiceTrackerCustomizer</code> class. The only
 * difference is the class name which makes clear that the
 * <code>ILocalServiceTrackerCustomizer</code> class is used for tracking local
 * services at the Remote SOF container.
 *
 * @author magr74
 */
class ILocalServiceTrackerCustomizer : public IServiceTrackerCustomizer
{
	public:

		/**
		 * Defines a constant pointer to the <code>IServiceTrackerCustomizer</code>
		 * object.
		 */
		typedef ILocalServiceTrackerCustomizer* const ConstPtr;
};

}}
#endif
