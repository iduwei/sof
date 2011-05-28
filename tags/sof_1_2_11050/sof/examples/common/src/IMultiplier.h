#ifndef IMULTIPLIER_H
#define IMULTIPLIER_H

#include "sof/framework/IService.h"

using namespace sof::framework;

class IMultiplier : public IService
{
	public:
		virtual int multiply( int x, int y ) = 0;
};

#endif