#ifndef IDIVIDER_H
#define IDIVIDER_H

#include "sof/framework/IService.h"

using namespace sof::framework;

class IDivider : public IService
{
	public:
		virtual double divide( double x, double y ) = 0;
};

#endif
