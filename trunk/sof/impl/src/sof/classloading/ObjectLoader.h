#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H

#include <map>
#include <string>

#include "BaseFactory.h"
#include "ObjectLoadingException.h"
#include "../util/logging/Logger.h"
#include "../util/logging/LoggerFactory.h"

#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <sstream>
#include <exception>

using namespace std;

using namespace sof::util::logging;

namespace sof
{
namespace classloading
{

using namespace std;

template<typename BaseT>
class ObjectLoader
{
	private:		
		static map<string,BaseFactory<BaseT>* >* instanceMap;	
		bool localSearch;
		string path;
		string dllName;

	public:
		ObjectLoader();
		ObjectLoader( bool localSearch, const string &path, const string &dllName );
		void setSearchConfiguration( bool localSearch, const string &path, const string &dllName );
		BaseT* loadObject( const string &key );	
		static Logger& getLogger();
		static void addFactory( const string &key, BaseFactory<BaseT>* intantiator );
		static BaseT* loadLocalObject( const string &key );		
		static BaseT* loadObjectFromDll( const string &path, const string &dllName, const string &className );	
};

template<typename BaseT>
Logger& ObjectLoader<BaseT>::getLogger()
{
	static Logger& logger = LoggerFactory::getLogger( "Classloading" );
	return logger;
}

template<typename BaseT>
map<string,BaseFactory<BaseT>* >* ObjectLoader<BaseT>::instanceMap;	


template<typename BaseT>
ObjectLoader<BaseT>::ObjectLoader() : localSearch( true ), path( "" ), dllName( "" )
{	
	getLogger().log( Logger::DEBUG, "[ObjectLoader#ctor] Called" );
}

template<typename BaseT>
void ObjectLoader<BaseT>::setSearchConfiguration( bool searchLocal, const string &pathName, const string &libName )
{
	getLogger().log( Logger::DEBUG, "[ObjectLoader#setSearchConfiguration] Called, local search: %1", searchLocal );
	
	getLogger().log( Logger::DEBUG, "[ObjectLoader#setSearchConfiguration] Called, path name: %1, lib name: %2",
		pathName, libName );
	this->localSearch = searchLocal;
	this->path = pathName;
	this->dllName = libName;
}

template<typename BaseT>
ObjectLoader<BaseT>::ObjectLoader( bool doLocalSearch, const string &dllPath, const string &dll ) : 
	localSearch( doLocalSearch ), path( dllPath ), dllName( dll )
{
	getLogger().log( Logger::DEBUG, "[ObjectLoader#ctor] Called, local search: %1", doLocalSearch );
	
	getLogger().log( Logger::DEBUG, "[ObjectLoader#ctor] Called, dll path: %1, lib name: %2",
		dllPath, dll );
	
}

template<typename BaseT>
void ObjectLoader<BaseT>::addFactory( const string &key, BaseFactory<BaseT>* intantiator )
{
	if ( instanceMap == 0 )
	{
		getLogger().log( Logger::DEBUG, "[ObjectLoader#addFactory] Instance map is null, create it." );
		instanceMap = new map<string,BaseFactory<BaseT>* >;
	}
	getLogger().log( Logger::DEBUG, "[ObjectLoader#addFactory] Called, key: '%1'", key );
	(*instanceMap)[key] = intantiator;
	getLogger().log( Logger::DEBUG, "[ObjectLoader#addFactory] Factory for key '%1' added.", key );		
}

template<typename BaseT>
BaseT* ObjectLoader<BaseT>::loadObject( const string &key )
{	
	if ( this->localSearch )
	{
		getLogger().log( Logger::DEBUG, "[ObjectLoader#loadObjectFromDll] Do local search, path='%1', key='%2'", path, key);
		if ( ( path == "" ) && ( dllName == "" ) )
		{
			// do only local search
			getLogger().log( Logger::DEBUG, "[ObjectLoader#loadObjectFromDll] Do ONLY local search." );
			return loadLocalObject( key );
		}
		else
		{
			try
			{
				loadLocalObject( key );
			}
			catch( ObjectLoadingException &exc )
			{
				getLogger().log( Logger::DEBUG, "[ObjectLoader#loadObjectFromDll] Local search failed, load from DLL." );			
				return loadObjectFromDll( this->path, this->dllName, key );
			}			
		}
	}
	else
	{
		getLogger().log( Logger::DEBUG, "[ObjectLoader#loadObjectFromDll] Do NOT local search, but load directly from DLL." );			
		// search in DLL for loading object
		return loadObjectFromDll( this->path, this->dllName, key );
	}		
}

template<typename BaseT>
BaseT* ObjectLoader<BaseT>::loadLocalObject( const string &key )
{	
	BaseFactory<BaseT>* intantiator = (*ObjectLoader<BaseT>::instanceMap)[key];
	if ( intantiator == 0 )
	{
		ObjectLoadingException exc( "No intantiator for class available." );
		throw exc;
	}
	return intantiator->newInstance();
}

template<typename BaseT>
BaseT* ObjectLoader<BaseT>::loadObjectFromDll( const string &path, const string &dllName, const string &className )
{	
	typedef BaseT* (*DLLPROC) ( const string& );

	DLLPROC pFunc = NULL;

	ostringstream str;
	
	int pos = path.find_last_of( '/' );
	if ( pos == ( path.size() - 1 ) )
	{
		str << path << dllName;	
	}
	else
	{
		str << path << '/' << dllName;	
	}
	
	getLogger().log( Logger::DEBUG, "[ObjectLoader#loadObjectFromDll] Loading DLL: '%1'", str.str() );

	HMODULE hMod = NULL;
	try
	{
		hMod = LoadLibrary( str.str().c_str() );
	}
	catch( exception &exc )
	{
		getLogger().log( Logger::ERROR_, "[ObjectLoader#loadObjectFromDll] Error occurred during loading DLL: %1", exc.what() );
		hMod = NULL;
	}

	if ( hMod == NULL )
	{
		ObjectLoadingException exc( "Error during loading DLL." );
		throw exc;
	}
	
	try
	{
		pFunc = ( DLLPROC ) GetProcAddress(hMod, "loadObject"); 
	}
	catch( exception &exc)
	{
		getLogger().log( Logger::ERROR_, "[ObjectLoader#loadObjectFromDll] Error occurred during calling DLL entry method, %1", exc.what() );
		pFunc = NULL;
	}

	if ( pFunc == NULL )
	{
		ObjectLoadingException exc( "Error during loading object from DLL." );
		throw exc;
	}	
	return ((*pFunc)(className));
}

}}
#endif