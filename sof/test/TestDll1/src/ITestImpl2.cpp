#include "ITestImpl2.h"

#include "sof/instantiation/win/WinDllCreator.h" 
#include "sof/instantiation/ObjectCreator.h"

using namespace sof::instantiation;
using namespace sof::instantiation::win;

int ITestImpl2::getValue()
{
	return 42;
}

REGISTER_CLASS("ITestImpl2",ITest,ITestImpl2)
