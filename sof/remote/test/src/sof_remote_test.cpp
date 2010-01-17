#include "TestHarness.h"

#include <string>
#include <iostream>

using namespace std;

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/IBundleActivator.h"

#include "UnitTestLogger.h"

using namespace sof::instantiation;
using namespace sof::framework;

int main()
{	
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[sof_remote_test#main] *** Begin tests...." );
    TestResult tr;
    TestRegistry::runAllTests(tr);
	return 0;
}
