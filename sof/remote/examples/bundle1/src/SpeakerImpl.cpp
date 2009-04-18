#include <CORBA.h>
#include "SpeakerImpl.h"

#include <iostream>

using namespace std;

void SpeakerImpl::sayHello( const char* text )
{
	cout << "Text: " << text << endl;    
}