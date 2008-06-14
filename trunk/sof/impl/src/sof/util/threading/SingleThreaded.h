#ifndef SINGLE_THREADED_H
#define SINGLE_THREADED_H

#include <iostream>

using namespace std;

namespace sof { namespace util { namespace threading {

class SingleThreaded
{

public:
	class Lock
	{
		public:
			Lock()
			{
				cout << "[SingleThreaded#Lock#ctor] Called." << endl;
			}

			virtual ~Lock()
			{
				cout << "[SingleThreaded#Lock#destructor] Called." << endl;
			}			
	};
};

}}}
#endif