#ifndef OBJECT_H
#define OBJECT_H
#include "ObjectLoader.h"
#include "Factory.h"



#define REGISTER_CLASS(key,baseType,subType) \
class Register##baseType##with##subType \
	{ \
		public: \
			Register##baseType##with##subType () \
			{\
			ObjectLoader<baseType>::addFactory( key, new Factory<baseType,subType> );\
			} \
	} Register##baseType##with##subType##Instance; \

	

//#define CLASS(key,baseType,subType) ObjectLoader<baseType>::addFactory( key, new Factory<baseType,subType> );

#endif
