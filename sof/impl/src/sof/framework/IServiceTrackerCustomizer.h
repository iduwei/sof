#ifndef ISERVICE_TRACKER_CUSTOMIZER_H
#define ISERVICE_TRACKER_CUSTOMIZER_H

#include "ServiceReference.h"

namespace sof { 
namespace framework {

using namespace sof::framework;

class IServiceTrackerCustomizer
{
	public:
		typedef IServiceTrackerCustomizer* const ConstPtr;
		virtual void addingService( const ServiceReference& ref ) = 0;
		virtual void removedService( const ServiceReference& ref ) = 0;
};

}}
#endif