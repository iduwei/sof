#ifndef SPEAKER_IMPL_H
#define SPEAKER_IMPL_H

#include "Speaker.h"

using namespace std;

class SpeakerImpl : virtual public POA_Speaker
{
public:
    virtual void sayHello( const char* );

private:

};

#endif
