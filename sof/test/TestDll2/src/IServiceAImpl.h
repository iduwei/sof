#ifndef ISERVICE_A_IMPL_H
#define ISERVICE_A_IMPL_H

#include "IServiceA.h"

using namespace sof::framework;

class IServiceAImpl : public IServiceA
{

	public:
		int getValue();
};
#endif