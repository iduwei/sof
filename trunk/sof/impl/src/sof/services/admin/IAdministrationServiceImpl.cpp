#include "IAdministrationServiceImpl.h"

#include <iostream>

#include "../../framework/BundleInfo.h"
#include "../../config/BundleConfiguration.h"
#include "../../config/ConfigFileReader.h"
#include "../../util/helper/StringTokenizer.h"
#include "DumpBundleInfoCmd.h"
#include "StartBundleCmd.h"
#include "StartBundleFromDLLCmd.h"
#include "StopBundleCmd.h"
#include "StartBundlesFromFileCmd.h"

using namespace std;
using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::services::admin;
using namespace sof::util::helper;

Logger& IAdministrationServiceImpl::logger = LoggerFactory::getLogger( "services" );

IAdministrationServiceImpl::IAdministrationServiceImpl( Launcher* launch ) : launcher( launch )
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#ctor] Called." );
}

vector<string> IAdministrationServiceImpl::getBundleNames()
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#getBundleNames] Called." );
	return this->launcher->getBundleNames();
}

string IAdministrationServiceImpl::dumpBundleInfo( const string& bundleName )
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#dumpBundleInfo] Called, bundle name: %1", bundleName );
	return this->launcher->dumpBundleInfo( bundleName );
}

void IAdministrationServiceImpl::stopBundle( const string& bundleName )
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#stopBundle] Called, bundle name: %1", bundleName );
	this->launcher->stopBundle( bundleName );
}

void IAdministrationServiceImpl::stopAllBundles()
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#stopAllBundles] Called." );
	this->launcher->stop();
}

void IAdministrationServiceImpl::startBundleFromDLL( const string& bundleName, const string& className, const string& libPath, const string& libName )
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#startBundleFromDLL] Called, bundle name: %1, class name: %2", bundleName, className );
	BundleConfiguration bundleConf( bundleName, className, libPath, libName );
	vector<BundleConfiguration> vec;
	vec.push_back( bundleConf );
	this->launcher->start( vec );
}

void IAdministrationServiceImpl::startBundle( const string& bundleName, const string& className )
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#startBundle] Called, bundle name: %1, class name: %2", bundleName, className );
	BundleConfiguration bundleConf( bundleName, className );
	vector<BundleConfiguration> vec;
	vec.push_back( bundleConf );
	this->launcher->start( vec );
}

void IAdministrationServiceImpl::startBundlesFromConfigFile( const string& configFile )
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#startBundles] Called, configFile: %1", configFile );
	vector<BundleConfiguration> bundleConfVec = ConfigFileReader::readFromFile( configFile );
	this->launcher->start( bundleConfVec );
}

void IAdministrationServiceImpl::startConsole()
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#startConsole] Called." );

	DumpBundleInfoCmd dumpBundleCmd;
	this->cmdMap[dumpBundleCmd.getName()] = &dumpBundleCmd;

	StartBundleCmd startBundleCmd;
	this->cmdMap[startBundleCmd.getName()] = &startBundleCmd;
	
	StopBundleCmd stopBundleCmd;
	this->cmdMap[stopBundleCmd.getName()] = &stopBundleCmd;
	
	StartBundleFromDLLCmd startBundleFromDLLCmd;
	this->cmdMap[startBundleFromDLLCmd.getName()] = &startBundleFromDLLCmd;	

	StartBundlesFromFileCmd startBundlesFromFile;
	this->cmdMap[startBundlesFromFile.getName()] = &startBundlesFromFile;	
	
	string input;
	vector<string> tokens;

	cout << "-------------------------------------------------------------" << endl;
	cout << "|                       SOF console                         |" << endl;
	cout << "-------------------------------------------------------------" << endl << endl;
	
	cout << ">";
	while( getline(cin,input) ) 
	{
		tokens.clear();
		logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#startConsole] Input: %1", input );
			
		StringTokenizer::tokenize( input, tokens );
		if ( tokens.size() >=1 )
		{
			if ( tokens[0] == "exit" )
			{
				cout << endl << "Bye." << endl;
				break;
			}
			
			if ( tokens[0] == "help" )
			{
				cout << endl << "Available commands:" << endl;
				map<string,ConsoleCommand*>::iterator iter;
				for ( iter = this->cmdMap.begin(); iter != this->cmdMap.end(); iter++ )
				{
					cout << iter->second->getName() << "\t\t - " << iter->second->getDescription() << endl;
				}
				cout << ">";
				continue;
			}

			logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#startConsole] Token: %1", tokens[0] );
			ConsoleCommand* cmd = this->cmdMap[tokens[0]];
			if ( cmd == 0 )
			{
				cout << "!Unknown command" << endl;
			} 
			else if ( cmd->getParameterNum() != (tokens.size() -1) )
			{
				cout << "!Command requires " << cmd->getParameterNum() << " parameter(s)" << endl;
			}
			else
			{
				tokens.erase( tokens.begin() );
				cout << cmd->execute( this, tokens ) << endl;
			}
		}
		cout << ">";
	}
}

void IAdministrationServiceImpl::stopConsole()
{
	logger.log( Logger::DEBUG, "[IAdministrationServiceImpl#stopConsole] Called." );
}


		