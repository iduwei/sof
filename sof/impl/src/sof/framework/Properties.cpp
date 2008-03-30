#include "Properties.h"

#include <sstream>

using namespace std;

using namespace sof::framework;

void Properties::put( const string &key, const string &value )
{
	this->mapper[key] = value;
}

string Properties::get( const string &key )
{
	return this->mapper[key];
}

string Properties::toString() const
{
	map<string,string>::const_iterator iter;
	
	ostringstream propsStream;
	propsStream << "properties={";
	for( iter = mapper.begin(); iter != mapper.end(); iter++ ) 
	{
		propsStream << "[" << iter->first << "," << iter->second << "], ";		
	}
	propsStream << "}";
	return propsStream.str();
}

bool Properties::operator==( const Properties& props )
{
	if ( this->mapper == props.mapper )
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Properties::getSize()
{
	return this->mapper.size();
}