#ifndef ISERVICE_LISTENER_H
#define ISERVICE_LISTENER_H

#include "ServiceEvent.h"

namespace sof { namespace framework {

class IServiceListener
{
	public:
		typedef IServiceListener* const ConstPtr;
		virtual void serviceChanged( const ServiceEvent &serviceEvent ) = 0;
};

}}
#endif