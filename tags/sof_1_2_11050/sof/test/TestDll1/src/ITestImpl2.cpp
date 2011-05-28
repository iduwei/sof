#include "ITestImpl2.h"

#include "sof/instantiation/ObjectCreator.h"

using namespace sof::instantiation;

int ITestImpl2::getValue()
{
	return 42;
}

REGISTER_CLASS("ITestImpl2",ITest,ITestImpl2)
