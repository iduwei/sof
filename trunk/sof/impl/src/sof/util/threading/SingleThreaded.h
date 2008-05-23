#ifndef SINGLE_THREADED_H
#define SINGLE_THREADED_H

#include <iostream>

using namespace std;

namespace sof { namespace util { namespace threading {

template <class T>
class SingleThreaded
{

public:
	class Lock
	{
		public:
			Lock( T )
			{
				cout << "[SingleThreaded#Lock#ctor] Enter." << endl;
			}
			
	};
};

}}}
#endif