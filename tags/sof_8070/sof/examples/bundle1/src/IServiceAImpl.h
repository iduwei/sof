#ifndef ISERVICEAIMPL_H
#define ISERVICEAIMPL_H

#include <iostream>

using namespace std;

class IServiceAImpl : public IServiceA
{	
	public:
		virtual int getValue();
};

int IServiceAImpl::getValue() 
{
	cout << "[IServiceAImpl#getValue] Called." << endl;
	return 4711;
}

#endif