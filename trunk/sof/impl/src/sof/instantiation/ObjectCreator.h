#ifndef OBJECT_CREATOR_H
#define OBJECT_CREATOR_H

#include <map>
#include <string>

#include "BaseFactory.h"
#include "Factory.h"
#include "ObjectCreationException.h"
#include "../util/logging/Logger.h"
#include "../util/logging/LoggerFactory.h"

#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <sstream>
#include <exception>

using namespace std;

using namespace sof::util::logging;

namespace sof { namespace instantiation {

using namespace std;

/**
 * The <code>ObjectCreator</code> class allows to create instances of
 * classes by name.<p>
 * 
 * Example:<p>
 *
 * ObjectCreator<IBundleActivator> OC;<br>
 * IBundleActivator* activator = OC.createObject( "TestBundleActivator" );<p>
 *
 * First an instance of the template based class <code>ObjectCreator</code> has to be
 * created where the base type of the class which will be created is specified 
 * (here <code>IBundleActivator</code>).<br>
 * Afterwards the user object can be created by calling the <code>createObject</code> 
 * whereas the name of the class must be specified (here 'TestBundleActivator').<br>
 * The <code>ObjectCreator</code> class needs the knowledge about what object for what
 * class name must be created. This knowledge is set by the <code>REGISTER</code> macro
 * which is always defined in 'ObjectCreator.h'.<p>
 *
 * Example:<p>
 * REGISTER("TestBundleActivator",IBundleActivator,TestBundleActivator)<p>
 * 
 * The REGISTER macro registers a factory object of class <code>Factory</code> with
 * the <code>ObjectCreator</code> instance.<br>
 * Furthermore the <code>ObjectCreator</code> is able to create objects from DLLs too:<p>
 *
 * IBundleActivator* activator = OC.createObjectFromDll( "c:/libraries", "test.dll", "TestBundleActivator" );<p>
 */

template<typename BaseT>
class ObjectCreator
{
	private:	

		/**
		 * The map which stores factory objects. The factory objects are responsible for
		 * creating instances of a certain type.
		 */
		static map<string,BaseFactory<BaseT>* >* instanceMap;	

		/**
		 * The flag indicates whether the <code>ObjectCreator</code> instance only tries to
		 * create 'local' (not from DLL) objects.
		 */
		bool localSearch;

		/**
		 * The DLL path.
		 */
		string path;

		/**
		 * The name of the DLL from which a object is created.
		 */
		string dllName;

	public:

		/**
		 * The default constructor which creates instances of class <code>ObjectCreator</code>. 
		 * <code>ObjectCreator</code> instances which are created by default constructor do only
		 * allow creating local objects.
		 */
		ObjectCreator();

		/**
		 * Creates instances of class <code>ObjectCreator</code>.
		 *
		 * @param localSearch
		 *				Indicates whether the object creator only allows creating local objects.
		 *
		 * @param path
		 *				The path to the DLL from which objects are created.
		 *
		 * @param dllName
		 *				The name of the DLL from which objects are created.
		 */
		ObjectCreator( bool localSearch, const string &path, const string &dllName );

		/**
		 * Sets the configuration for creating objects.
		 *
		 * @param localSearch
		 *				Indicates whether the object creator only allows creating local objects.
		 *
		 * @param path
		 *				The path to the DLL from which objects are created.
		 *
		 * @param dllName
		 *				The name of the DLL from which objects are created.
		 */
		void setSearchConfiguration( bool localSearch, const string &path, const string &dllName );

		/**
		 * Creates an object of type <code>BaseT</code>.
		 *
		 * @param key
		 *			Defines which type of object is created (the name of the class).
		 * 
		 * @return
		 *			The created object of type <code>BaseT</code>.
		 */
		BaseT* createObject( const string &key );	
	
		/**
		 * Provides the logger instance.
		 */
		static Logger& getLogger();

		/**
		 * Adds a factory object for a certain class name. This method is only called
		 * by <code>REGISTER</code> macro.
		 *
		 * @param key
		 *			The name of the class.
		 *
		 * @param intantiator
		 *			The factory object which creates objects of classes whose name is specified by
		 *			first parameter.
		 */
		static void addFactory( const string &key, BaseFactory<BaseT>* intantiator );

		/**
		 * Creates only 'local' objects of classes.
		 * 
		 * @param key
		 *			The name of the class.
		 */
		static BaseT* createLocalObject( const string &key );		

		/**
		 * Creates only objects of classes which are located in a DLL.
		 *
		 * @param path
		 *			The path to the DLL.
		 *
		 * @param dllName
		 *			The name of the DLL where the class is located.
		 *
		 * @param className
		 *			The name of the class which is intantiated.
		 */
		static BaseT* createObjectFromDll( const string &path, const string &dllName, const string &className );	
};

template<typename BaseT>
Logger& ObjectCreator<BaseT>::getLogger()
{
	static Logger& logger = LoggerFactory::getLogger( "ObjectCreation" );
	return logger;
}

template<typename BaseT>
map<string,BaseFactory<BaseT>* >* ObjectCreator<BaseT>::instanceMap;	


template<typename BaseT>
ObjectCreator<BaseT>::ObjectCreator() : localSearch( true ), path( "" ), dllName( "" )
{	
	getLogger().log( Logger::DEBUG, "[ObjectCreator#ctor] Called" );
}

template<typename BaseT>
void ObjectCreator<BaseT>::setSearchConfiguration( bool searchLocal, const string &pathName, const string &libName )
{
	getLogger().log( Logger::DEBUG, "[ObjectCreator#setSearchConfiguration] Called, local search: %1", searchLocal );
	
	getLogger().log( Logger::DEBUG, "[ObjectCreator#setSearchConfiguration] Called, path name: %1, lib name: %2",
		pathName, libName );
	this->localSearch = searchLocal;
	this->path = pathName;
	this->dllName = libName;
}

template<typename BaseT>
ObjectCreator<BaseT>::ObjectCreator( bool doLocalSearch, const string &dllPath, const string &dll ) : 
	localSearch( doLocalSearch ), path( dllPath ), dllName( dll )
{
	getLogger().log( Logger::DEBUG, "[ObjectCreator#ctor] Called, local search: %1", doLocalSearch );
	
	getLogger().log( Logger::DEBUG, "[ObjectCreator#ctor] Called, dll path: %1, lib name: %2",
		dllPath, dll );
	
}

template<typename BaseT>
void ObjectCreator<BaseT>::addFactory( const string &key, BaseFactory<BaseT>* intantiator )
{
	if ( instanceMap == 0 )
	{
		getLogger().log( Logger::DEBUG, "[ObjectCreator#addFactory] Instance map is null, create it." );
		instanceMap = new map<string,BaseFactory<BaseT>* >;
	}
	getLogger().log( Logger::DEBUG, "[ObjectCreator#addFactory] Called, key: '%1'", key );
	(*instanceMap)[key] = intantiator;
	getLogger().log( Logger::DEBUG, "[ObjectCreator#addFactory] Factory for key '%1' added.", key );		
}

template<typename BaseT>
BaseT* ObjectCreator<BaseT>::createObject( const string &key )
{	
	if ( this->localSearch )
	{
		getLogger().log( Logger::DEBUG, "[ObjectCreator#createObject] Do local search, path='%1', key='%2'", path, key);
		if ( ( path == "" ) && ( dllName == "" ) )
		{
			// do only local search
			getLogger().log( Logger::DEBUG, "[ObjectCreator#createObject] Do ONLY local search." );
			return createLocalObject( key );
		}
		else
		{
			try
			{
				createLocalObject( key );
			}
			catch( ObjectCreationException &exc )
			{
				getLogger().log( Logger::DEBUG, "[ObjectCreator#createObject] Local search failed, load from DLL." );			
				return createObjectFromDll( this->path, this->dllName, key );
			}			
		}
	}
	else
	{
		getLogger().log( Logger::DEBUG, "[ObjectCreator#createObject] Do NOT local search, but load directly from DLL." );			
		// search in DLL for loading object
		return createObjectFromDll( this->path, this->dllName, key );
	}		
}

template<typename BaseT>
BaseT* ObjectCreator<BaseT>::createLocalObject( const string &key )
{	
	BaseFactory<BaseT>* intantiator = (*ObjectCreator<BaseT>::instanceMap)[key];
	if ( intantiator == 0 )
	{
		ObjectCreationException exc( "No intantiator for class available." );
		throw exc;
	}
	return intantiator->newInstance();
}

template<typename BaseT>
BaseT* ObjectCreator<BaseT>::createObjectFromDll( const string &path, const string &dllName, const string &className )
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
	
	getLogger().log( Logger::DEBUG, "[ObjectCreator#createObjectFromDll] Loading DLL: '%1'", str.str() );

	HMODULE hMod = NULL;
	try
	{
		hMod = LoadLibrary( str.str().c_str() );
	}
	catch( exception &exc )
	{
		getLogger().log( Logger::ERROR_, "[ObjectCreator#createObjectFromDll] Error occurred during loading DLL: %1", exc.what() );
		hMod = NULL;
	}

	if ( hMod == NULL )
	{
		ObjectCreationException exc( "Error during loading DLL." );
		throw exc;
	}
	
	try
	{
		pFunc = ( DLLPROC ) GetProcAddress(hMod, "createObject"); 
	}
	catch( exception &exc)
	{
		getLogger().log( Logger::ERROR_, "[ObjectCreator#createObjectFromDll] Error occurred during calling DLL entry method, %1", exc.what() );
		pFunc = NULL;
	}

	if ( pFunc == NULL )
	{
		ObjectCreationException exc( "Error during loading object from DLL." );
		throw exc;
	}	
	return ((*pFunc)(className));
}

#define REGISTER_CLASS(key,baseType,subType) \
class Register##baseType##with##subType \
	{ \
		public: \
			Register##baseType##with##subType () \
			{\
			ObjectCreator<baseType>::addFactory( key, new Factory<baseType,subType> );\
			} \
	} Register##baseType##with##subType##Instance; \

}}
#endif