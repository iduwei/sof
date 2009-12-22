#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include "BaseTestClass.h"
#include <string>

using namespace std;

class TestClass : public BaseTestClass
{
	public:
		TestClass();
		string getText();
};





#endif