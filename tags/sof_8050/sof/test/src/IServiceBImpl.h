#ifndef ISERVICE_B_IMPL_H
#define ISERVICE_B_IMPL_H

#include "IServiceB.h"

using namespace sof::framework;

class IServiceBImpl : public IServiceB
{

	public:
		int getValue();
};
#endif