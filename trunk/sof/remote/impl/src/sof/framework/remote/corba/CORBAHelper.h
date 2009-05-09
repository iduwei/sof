#ifndef CORBA_HELPER_H
#define CORBA_HELPER_H

#include <CORBA.h>
#include <mico/poa_base.h>

#include <string>
#include <vector>

#include "sof/framework/ServiceEvent.h"
#include "sof/util/logging/Logger.h"
#include "sof/util/logging/LoggerFactory.h"

#include "RemoteServiceReference.h"
#include "RemoteServiceInfo.h"
#include "RemoteServiceListenerInfo.h"

#include "./namingservice/CORBANamingService.h"
#include "./namingservice/CORBANamingServiceImpl.h"
#include "./generated/CORBAObjects.h"

extern "C" void *ThreadStartup(void *);

namespace sof { namespace framework { namespace remote { namespace corba { 

using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::framework::remote::corba::namingservice;
using namespace sof::framework::remote::corba::generated;

/**
 * Helper class which provides convenience methods for CORBA related
 * tasks like activating/deactivating CORBA objects.
 */
class CORBAHelper
{
	private:

		/**
		 * The CORBA orb instance.
		 */
		CORBA::ORB_var orb;

		/**
		 * Initializes the CORBA orb.
		 *
		 * @param args 
		 *			The command line arguments.
		 */
		void initORB( const vector<string>& args );

		/**
		 * The naming service component which provides helper methods
		 * for accessing the CORBA naming service.
		 */
		CORBANamingService* ns;

		/**
		 * The CORBA POA instance.
		 */
		PortableServer::POA_var explicitActPOA;		

		/**
		 * The logger instance.
		 */
		static Logger& logger;

	public:
		
		/**
		 * Constant string value representing the path to
		 * the remote registry component at CORBA naming service.
		 */
		static const string REMOTE_REGISTRY_PATH;

		/**
		 * Constant string value representing the name of the remote
		 * registry component at CORBA naming service.
		 */
		static const string REMOTE_REGISTRY_NAME;

		/**
		 * Creates instances of class <code>CORBAHelper</code>.
		 *
		 * @param args
		 *			The arguments for initializing the CORBA orb.
		 */
		CORBAHelper( const vector<string>& args );

		/** 
		 * Creates an activates a CORBA object.
		 *
		 * @param servant
		 *			The implementation of the CORBA object.
		 *
		 * @return 
		 *			The created and activated CORBA object.
		 */
		CORBA::Object_var activateObject( const PortableServer::Servant& servant );

		/**
		 * Deactivates a CORBA object.
		 *
		 * @param obj
		 *			The CORBA object which is deactivated.		 
		 */
		void deactivateObject( CORBA::Object_var obj );
		
		/**
		 * Registers a CORBA object at the naming service.
		 *
		 * @param obj
		 *			The CORBA object which is registered.
		 *
		 * @param namingServicePath
		 *			The directory at naming service where the CORBA object
		 *			is registered (e.g. 'foo/bar/xy')
		 *
		 * @param objectName
		 *			The name of the CORBA object.		 		
		 */
		void registerObject( CORBA::Object_var obj, const string& namingServicePath, const string& objectName );

		/**
		 * Deregisters a CORBA object at naming service.
		 *
		 * @param namingServicePath
		 *				The directory at naming service where the CORBA object
		 *				is deregistered.
		 *
		 * @param objectName
		 *				The name of the CORBA object which is deregistered.
		 */
		void deregisterObject( const string& namingServicePath, const string& objectName );

		/**
		 * Lists all CORBA objects which are registered at naming service under
		 * specified path.
		 *
		 * @param path
		 *			The path at CORBA naming service where CORBA objects are searched for.
		 *
		 * @return 
		 *			Returns a list of CORBA objects which were found under specified
		 *			path at naming service.
		 */
		list<CORBA::Object_var> findObjects( const string& path);

		/**
		 * Helper method for converting a CORBA object to a string
		 * representation.
		 *
		 * @param obj
		 *			The CORBA object.
		 *
		 * @return 
		 *			The string representation of the CORBA object.
		 */
		string objectToString( CORBA::Object_var obj );

		/**
		 * Helper method for converting the string representatio of a CORBA
		 * object into a CORBA object instance.
		 *
		 * @param objString
		 *				The string representation of the CORBA object.
		 *
		 * @return
		 *				The CORBA object.
		 */
		CORBA::Object_var stringToObject( string objString );

		/**
		 * Starts the CORBA orb whereas the orb runs in a separate thread.
		 */
		void start();

		/**
		 * Starts the CORBA orb and blocks the current thread.
		 */
		void startAndWait();

		/**
		 * Runs the CORBA orb instance. Is called from <code>start()</code>
		 * or <code>startAndWait()</code>.
		 */
		void run_orb();

		/**
		 * Stops the CORBA orb. 
		 */
		void stop();		

		/**
		 * TODO: check if returning a pointer is necessary.
		 *
		 * Converts a <code>CORBAServiceReference</code> object into a 
		 * <code>RemoteServiceReference</code> object.
		 *
		 * @param reference
		 *			The <code>CORBAServiceReference</code> object.
		 *
		 * @return
		 *			The pointer to the <code>RemoteServiceReference</code> object.
		 *			
		 */
		RemoteServiceReference* convertServiceReference( const CORBAServiceReference& reference );

		/**		 
		 * Converts a <code>RemoteServiceReference</code> object into a 
		 * <code>CORBAServiceReference</code> object.
		 *
		 * @param reference
		 *			The <code>RemoteServiceReference</code> object.
		 *
		 * @return
		 *			The <code>CORBAServiceReference</code> object.
		 *			
		 */
		CORBAServiceReference convertServiceReference( const RemoteServiceReference& reference );
		
		/**		 
		 * Converts a <code>CORBAServiceEvent</code> object into a 
		 * <code>ServiceEvent</code> object.
		 *
		 * @param reference
		 *			The <code>CORBAServiceEvent</code> object.
		 *
		 * @return
		 *			The <code>ServiceEvent</code> object.
		 *			
		 */
		ServiceEvent convertEvent( const CORBAServiceEvent& servEvent );

		/**		 
		 * Converts a <code>ServiceEvent</code> object into a 
		 * <code>CORBAServiceEvent</code> object.
		 *
		 * @param reference
		 *			The <code>ServiceEvent</code> object.
		 *
		 * @return
		 *			The <code>CORBAServiceEvent</code> object.
		 *			
		 */
		CORBAServiceEvent convertEvent( const ServiceEvent& servEvent );

		/**		 
		 * Converts a <code>Properties</code> object into a 
		 * <code>CORBAServiceProps</code> object.
		 *
		 * @param reference
		 *			The <code>Properties</code> object.
		 *
		 * @return
		 *			The <code>CORBAServiceProps</code> object.
		 *			
		 */
		CORBAServiceProps convertServiceProperties( const Properties& props );

		/**		 
		 * Converts a <code>CORBAServiceProps</code> object into a 
		 * <code>Properties</code> object.
		 *
		 * @param reference
		 *			The <code>CORBAServiceProps</code> object.
		 *
		 * @return
		 *			The <code>Properties</code> object.
		 *			
		 */
	    Properties convertServiceProperties( const CORBAServiceProps& props );

		/**
		 * TODO: check if returning a reference is necessary.
		 *
		 * Creates a <code>RemoteServiceInfo</code> object from the service name,
		 * the CORBA service object and the CORBA properties object.
		 *
		 * @param serviceName
		 *				The name of the CORBA service.
		 *
		 * @param service
		 *				The CORBA service object.
		 *
		 * @param props
		 *				The properties object.
		 *
		 * @return
		 *				The created <code>RemoteServiceInfo</code> object.
		 */
		RemoteServiceInfo& convertToServiceInfo( const string& serviceName,
			CORBAService_ptr service, const CORBAServiceProps& props );

		/**
		 * TODO: check if returning a reference is necessary.

		 * Creates a <code>RemoteServiceListenerInfo</code> object from the bundle name,
		 * the service namet and the CORBA service listener object.
		 *
		 * @param bundleName
		 *				The bundle name.
		 *
		 * @param serviceName
		 *				The name of the CORBA service object.
		 *
		 * @param serviceListener
		 *				The CORBA service listener object.
		 *
		 * @return
		 *				The created <code>RemoteServiceListenerInfo</code> object.
		 */
		RemoteServiceListenerInfo& convertToServiceListenerInfo( const string& bundleName,
			const string& serviceName,
			CORBAServiceListener_ptr serviceListener );
};


}}}}
#endif