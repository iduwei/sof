#ifndef OBJECT_LOADING_EXCEPTION_H
#define OBJECT_LOADING_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace sof
{
namespace classloading
{

using namespace std;

class ObjectLoadingException : public exception
{
	private:
		string message;

	public:
		ObjectLoadingException( const string &msg );
		const char* what() const;
};

}}
#endif