#ifndef MULTIPLIER_IMPL_H
#define MULTIPLIER_IMPL_H

#include "Multiplier.h"

using namespace std;

/**
 * Represents a service class for test cases. Instances of
 * <code>MultiplierImpl</code> are registered and tracked.
 */
class MultiplierImpl : virtual public POA_Multiplier
{
public:

	/**
	 * Multiplies two values and returns the result.
	 */
	virtual CORBA::Long multiply( CORBA::Long x, CORBA::Long y );

private:

};

#endif
