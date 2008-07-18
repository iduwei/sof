#ifndef ISERVICEA_H
#define ISERVICEA_H

#include "sof/framework/IService.h"

using namespace sof::framework;

class IServiceA : public IService
{
	public:
		virtual int getValue() = 0;
};

#endif