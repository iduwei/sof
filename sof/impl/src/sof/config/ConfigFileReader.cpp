#include "ConfigFileReader.h"

#include <iostream>
#include <fstream>

#include "../util/helper/StringTokenizer.h"
#include "BundleConfiguration.h"
#include "ConfigurationException.h"

using namespace std;
using namespace sof::config;
using namespace sof::util::helper;
using namespace sof::util::logging;

Logger& ConfigFileReader::logger = LoggerFactory::getLogger( "Config" );

vector<BundleConfiguration> ConfigFileReader::readFromFile( const string& filename )
{
	ifstream fin( filename.c_str() );
	if (!fin)
	{
		ConfigurationException exc( "Error during loading configuration file: " + filename );
		throw exc;
	}
	string buffer;
	vector<BundleConfiguration> bundleConfigVec;
	vector<string> tokens;
	while (fin.good()) {
		getline(fin,buffer,'\n');
		logger.log( Logger::LOG_DEBUG, "[ConfigFileReader#readFromFile] Read line: %1", buffer );
		StringTokenizer::tokenize( buffer, tokens, "," );
		if ( tokens.size() == 2 )
		{
			BundleConfiguration config( tokens[0], tokens[1] );
			bundleConfigVec.push_back( config );
		}
		else if ( tokens.size() == 4 )
		{
			BundleConfiguration config( tokens[0], tokens[1], tokens[2], tokens[3] );
			bundleConfigVec.push_back( config );
		}
		else
		{
			logger.log( Logger::LOG_DEBUG, "[ConfigFileReader#readFromFile] Read line is ignored, no valid bundle configuration." );
		}
		tokens.clear();
	}

	fin.close();	

	return bundleConfigVec;
}