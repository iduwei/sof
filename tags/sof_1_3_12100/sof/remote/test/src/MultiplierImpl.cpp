#include <CORBA.h>
#include "MultiplierImpl.h"

#include <iostream>

using namespace std;

CORBA::Long MultiplierImpl::multiply( CORBA::Long x, CORBA::Long y )
{
	cout << "Multiplier called. " << endl;   	
	return x*y;
}