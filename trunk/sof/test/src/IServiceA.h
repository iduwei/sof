#ifndef ISERVICE_A_H
#define ISERVICE_A_H

#include "sof/framework/IService.h"

using namespace sof::framework;

class IServiceA : public IService
{
	public:
		virtual int getValue() = 0;
};
#endif