#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include <string>
#include <vector>

namespace sof { namespace util { namespace helper {

using namespace std;

class StringTokenizer
{
	private:
		StringTokenizer();
	public:
		static void tokenize( const string& str, vector<string>& tokens, 
										  const string& delimiters = " " );
};

}}}
#endif