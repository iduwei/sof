#ifndef ISERVICE_B_H
#define ISERVICE_B_H

#include "sof/framework/IService.h"

using namespace sof::framework;

class IServiceB : public IService
{
	public:
		virtual int getValue() = 0;
};
#endif