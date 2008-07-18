#include "TestClass.h"

#include "sof/instantiation/ObjectCreator.h"
#include "sof/instantiation/win/WinDllCreator.h"
#include "BaseTestClass.h"

using namespace sof::instantiation;
using namespace sof::instantiation::win;

TestClass::TestClass()
{
	
}


string TestClass::getText()
{
	return "foo";
}

REGISTER_CLASS( "TestClass",BaseTestClass,TestClass )