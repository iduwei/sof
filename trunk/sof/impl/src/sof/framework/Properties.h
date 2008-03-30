#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <map>
#include <string>

namespace sof { namespace framework {

using namespace std;

class Properties
{
	private:
		map<string,string> mapper;

	public:
		void put( const string &key, const string &value );
		string get( const string &key );
		string toString() const;
		bool operator==( const Properties& props );
		int getSize();

};

}}
#endif