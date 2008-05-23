#ifndef NULL_CREATOR_H
#define NULL_CREATOR_H

#include <string>

#include "ObjectCreationException.h"

using namespace std;
using namespace sof::instantiation;

namespace sof { namespace instantiation {

template <typename BaseT>
class NullCreator
{
	public:
		static BaseT* createObjectFromDll( const string &path, const string &dllName, const string &className );
};

template <typename BaseT>
BaseT* NullCreator<BaseT>::createObjectFromDll( const string &path, const string &dllName, const string &className )
{
	//ObjectCreationException exc( "Not supported!" );
	//throw exc;
	return 0;
}

}}
#endif