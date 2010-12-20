#include "ITestImpl.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/instantiation/win/WinDllCreator.h"

using namespace sof::instantiation;
using namespace sof::instantiation::win;

int ITestImpl::getValue()
{
	return 69;
}

REGISTER_CLASS("ITestImpl",ITest,ITestImpl )