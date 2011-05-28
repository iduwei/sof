#include "TestClass.h"

#include "sof/instantiation/ObjectCreator.h"
#include "BaseTestClass.h"

using namespace sof::instantiation;

TestClass::TestClass()
{
	
}


string TestClass::getText()
{
	return "foo";
}

REGISTER_CLASS( "TestClass",BaseTestClass,TestClass )