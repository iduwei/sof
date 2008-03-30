#ifndef IBUNDLE_ACTIVATOR_H
#define IBUNDLE_ACTIVATOR_H

#include "IBundleContext.h"

namespace sof { 
namespace framework {

using namespace sof::framework;

class IBundleActivator
{
	public:
		virtual ~IBundleActivator() {};
		virtual void start( IBundleContext::ConstPtr context ) = 0;
		virtual void stop( IBundleContext::ConstPtr context ) = 0;
};

} }

#endif