#ifndef MULTIPLIER_IMPL_H
#define MULTIPLIER_IMPL_H

#include "Multiplier.h"

using namespace std;

class MultiplierImpl : virtual public POA_Multiplier
{
public:
	virtual CORBA::Long multiply( CORBA::Long x, CORBA::Long y );

private:

};

#endif
