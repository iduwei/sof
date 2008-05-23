// Standard Headers
#include <iostream>
#include <string>

// CppUnitLite Headers
#include "TestHarness.h"
#include "Test.h"

#include "sof/util/threading/SingleThreaded.h"
#include "sof/instantiation/NullCreator.h"

#include "UnitTestLogger.h"

// Standard namespaces
using namespace std;

using namespace sof::util::threading;
using namespace sof::instantiation;

template <template <class> class ThreadingModel>
class Foo : public ThreadingModel<string>
{
	public:
		void doAnything();
};


template <template <class> class ThreadingModel>
void Foo<ThreadingModel>::doAnything()
{
	cout << "[ThreadingTest#Foo#doAnything] Enter." << endl;
	string s;
	Lock l(s);
	cout << "[ThreadingTest#Foo#doAnything] Leave." << endl;
}

template <
	template <class> class ThreadingModel = SingleThreaded,
	template <class> class CreationPolicy = NullCreator>
class Bar
{
	private:
		Foo<ThreadingModel> foo;

	public:
		void callFoo();
		void createObjectFromDll( const string &path, const string &dllName, const string &className );
};

template <
	template <class> class ThreadingModel,
	template <class> class CreationPolicy>
void Bar<ThreadingModel,CreationPolicy>::callFoo()
{
	cout << "[ThreadingTest#Bar#callFoo] Enter." << endl;
	foo.doAnything();
	cout << "[ThreadingTest#Bar#callFoo] Leave." << endl;
}

template <
	template <class> class ThreadingModel,
	template <class> class CreationPolicy>
void Bar<ThreadingModel,CreationPolicy>::createObjectFromDll( const string &path, const string &dllName, const string &className )
{
	cout << "[ThreadingTest#Bar#createObjectFromDll] Enter." << endl;
	CreationPolicy<string>::createObjectFromDll( path, dllName, className );
	cout << "[ThreadingTest#Bar#createObjectFromDll] Leave." << endl;
}


TEST( SingleThreaded, threading1 )
{
	UnitTestLogger::getInstance().log( Logger::DEBUG, "[ThreadingTest] *** SingleThreaded-threading1 Test" );
	Bar<SingleThreaded,NullCreator> bar;
	bar.callFoo();	
	bar.createObjectFromDll( "a", "b", "c" );

	Bar<> bar2;
}

