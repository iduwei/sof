#ifndef IBUNDLE_CONTEXT_H
#define IBUNDLE_CONTEXT_H

#include <string>

#include "IService.h"   
#include "Properties.h"
#include "IServiceListener.h"
#include "IServiceRegistration.h"

namespace sof { 
namespace framework {

using namespace std;
using namespace sof::framework;

class IBundleContext
{
	public:
		typedef IBundleContext* const ConstPtr;
		virtual ~IBundleContext() {};
		virtual IServiceRegistration::ConstPtr registerService( const string &className, IService::ConstPtr service, const Properties &dict ) = 0;
		virtual void addServiceListener( IServiceListener::ConstPtr serviceListener, const string &serviceName ) = 0;
		virtual void removeServiceListener( IServiceListener::ConstPtr serviceListener ) = 0;
};

}}
#endif