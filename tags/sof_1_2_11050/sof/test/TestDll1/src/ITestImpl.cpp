#include "ITestImpl.h"

#include "sof/instantiation/ObjectCreator.h"

using namespace sof::instantiation;

int ITestImpl::getValue()
{
	return 69;
}

REGISTER_CLASS("ITestImpl",ITest,ITestImpl )