#ifndef ISERVICE_REGISTRATION_H
#define ISERVICE_REGISTRATION_H

namespace sof { namespace framework {

class IServiceRegistration
{
	public:
		typedef IServiceRegistration* const ConstPtr;
		virtual void unregister() = 0;
};

}}

#endif