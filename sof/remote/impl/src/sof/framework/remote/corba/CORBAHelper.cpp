#include "CORBAHelper.h"

using namespace std;

using namespace sof::framework::remote::corba;

const string CORBAHelper::REMOTE_REGISTRY_PATH = "remote_sof/registry";
const string CORBAHelper::REMOTE_ADMIN_PATH = "remote_sof/admin";
const string CORBAHelper::REMOTE_REGISTRY_NAME = "registry_object";

Logger& CORBAHelper::logger = LoggerFactory::getLogger( "Framework" );

CORBAHelper::CORBAHelper( const vector<string>& args )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#ctor] Called." );
	this->initORB( args );
}

CORBAHelper::~CORBAHelper()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#destructor] Called." );
	this->cleanUp();
}

CORBAHelper::CORBAHelper( const CORBAHelper& corbaHelper )
{
	// Should not be called!
}

CORBAHelper& CORBAHelper::operator=( const CORBAHelper& other)
{
	// Should not be called!
}

void CORBAHelper::initORB( const vector<string>& args )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Called." );
	int argc = args.size();
	char** argv = (char**)malloc( sizeof(char**) * argc ); 
	vector<string>::const_iterator iter;
	int counter = 0;
	for ( iter = args.begin(); iter != args.end(); iter++ )
	{
		argv[counter] = const_cast<char*> ( (*iter).c_str() );
		this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Argument: %1", (*iter) );
		counter++;
	}
	
	this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Initialize the ORB." );
	this->orb = CORBA::ORB_init( argc, argv);
	this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] ORB initialized." );

	free( argv );

    CORBA::Object_var poaobj =
		orb->resolve_initial_references("RootPOA");
    this->rootPOA = PortableServer::POA::_narrow( poaobj);
    this->rootPOAManager = rootPOA->the_POAManager();
	this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Creating the naming service accessor class." );
	this->ns = this->createNamingService();

	this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Creating the naming service accessor class - done." );

	try 
	{
		CORBA::PolicyList policies;
		policies.length(1);
		policies[0] = rootPOA->create_implicit_activation_policy( PortableServer::NO_IMPLICIT_ACTIVATION );

		this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Creating the POA instance." );
		this->explicitActPOA = this->rootPOA->create_POA("MyPOA", rootPOAManager, policies);
		this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] POA instance created." );
	  
		if (CORBA::is_nil(this->explicitActPOA))
		{
			this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] Explicit POA can't be created, POA is null." );
		}
		this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Activate root POA manager." );
		this->rootPOAManager->activate();
		this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Root POA manager activated" );
	} 
	catch (const PortableServer::POA::AdapterAlreadyExists& e)
	{
		this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] POA already exists." );	  
		try 
		{
			this->explicitActPOA = rootPOA->find_POA("MyPOA", 0);
		} 
		catch (const PortableServer::POA::AdapterNonExistent&)
		{
			this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] No POA found." );	  		
		}
	} 
	catch (const PortableServer::POA::InvalidPolicy& e)
	{
		// the choosen policy combination is invalid
		this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] Invalid policy used." );	  	
	}
	catch( const CORBA::UserException& userEx )
	{
		this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] CORBA UserException occurred: %1", string( userEx._repoid() ) );	  
	}
	catch( const CORBA::SystemException sysEx )
	{
		this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] CORBA SystemException occurred: %1", string( sysEx._repoid() ) );	  
	}
}

CORBANamingService* CORBAHelper::createNamingService()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#createNamingService] Called." );	
	try
	{
		return new CORBANamingServiceImpl( this->orb );	
	} 
	catch( std::exception& exc )
	{
		// Exception should not be catched here, but it is important for unit tests, because there 
		// is no naming service started.
		this->logger.log( Logger::ERROR_, "[CORBAHelper#createNamingService] No naming service available. OK for unit tests." );		
	}
	catch( ... )
	{
		// Exception should not be catched here, but it is important for unit tests, because there 
		// is no naming service started.
		this->logger.log( Logger::ERROR_, "[CORBAHelper#createNamingService] No naming service available. OK for unit tests." );
	}
}

void CORBAHelper::registerObject( CORBA::Object_var obj, const string& namingServicePath, const string& objectName )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#registerObject] Called, naming service path: %1, object name: %2", 
		namingServicePath, objectName );	
	this->ns->bindObject( namingServicePath, objectName, obj );
}

list<CORBA::Object_var> CORBAHelper::findObjects( const string& path)
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#findObjects] Called, path: %1", 
		path );	
	return this->ns->findObjects( path );
}

void CORBAHelper::deregisterObject( const string& namingServicePath, const string& objectName )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#deregisterObject] Called, path: %1, object name: %2", 
		namingServicePath, objectName );	
	this->ns->unbindObject( namingServicePath, objectName );
}
		

void CORBAHelper::deactivateObject( CORBA::Object_var obj )
{		
	this->logger.log( Logger::DEBUG, "[CORBAHelper#deactivateObject] Called" );	
	try 
	{
		PortableServer::ObjectId_var oid = this->explicitActPOA->reference_to_id( obj );
		this->explicitActPOA->deactivate_object( oid );
		
	} catch (const PortableServer::POA::WrongPolicy& e){
		this->logger.log( Logger::ERROR_, "[CORBAHelper#deactivateObject] Wrong policy." );	
	} catch (const PortableServer::POA::ServantAlreadyActive&){
		this->logger.log( Logger::ERROR_, "[CORBAHelper#deactivateObject] Servant already active." );	
	}	
}

CORBA::Object_var CORBAHelper::activateObject( const PortableServer::Servant& servant )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#activateObject] Called" );	
	CORBA::Object_var obj;

	try 
	{	  
		this->logger.log( Logger::DEBUG, "[CORBAHelper#activateObject] Activate object." );	
		PortableServer::ObjectId_var oid = this->explicitActPOA->activate_object( servant );
		
		// get a reference
		obj = this->explicitActPOA->id_to_reference(oid);
		logger.log( Logger::DEBUG, "[CORBAHelper#activateObject] OID: %1", obj->_repoid() );
		if (CORBA::is_nil(obj))
		{
			logger.log( Logger::ERROR_, "[CORBAHelper#activateObject] Object is null." );
		}
	} catch (const PortableServer::POA::WrongPolicy& e){
		logger.log( Logger::ERROR_, "[CORBAHelper#activateObject] Wrong policy." );
	} catch (const PortableServer::POA::ServantAlreadyActive&){
		logger.log( Logger::ERROR_, "[CORBAHelper#activateObject] Servant already active." );
	}
	logger.log( Logger::DEBUG, "[CORBAHelper#activateObject] Return activated object." );

	return obj;
}

string CORBAHelper::objectToString( CORBA::Object_var obj )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#objectToString] Called" );	
	return this->orb->object_to_string( obj );
}

CORBA::Object_var CORBAHelper::stringToObject( string objString )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#stringToObject] Called" );	
	return this->orb->string_to_object( objString.c_str() );
}

void CORBAHelper::start()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#start] Called, creating thread for running orb in its own thread." );	
	pthread_t thread;
	pthread_create(&thread, NULL, ThreadStartup, this );	

	// TODO: Why this log message causes problems?
	// Note: Probably synchronisation problems at logger instance. Both
	// main thread and ORB runner thread use the same instance.
	
}

void CORBAHelper::startAndWait()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#startAndWait] Run the ORB." );		
	this->run_orb();
}

void *ThreadStartup(void *_tgtObject) {
  CORBAHelper *tgtObject = (CORBAHelper *)_tgtObject;

  // TODO: this log message causes problems
  //(*tgtObject).logger.log( Logger::DEBUG, "[CORBAHelper#ThreadStartup] Called, running ORB." );

  tgtObject->run_orb();
  return NULL;
}

void CORBAHelper::run_orb()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#run_orb] Called." );	
	this->orb->run();  
	this->logger.log( Logger::DEBUG, "[CORBAHelper#run_orb] Left" );	
}

void CORBAHelper::stop()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#stop] Called." );	
	this->logger.log( Logger::DEBUG, "[CORBAHelper#stop] Shutdown the ORB instance." );		
	this->orb->shutdown( true );
	
}

void CORBAHelper::cleanUp()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#cleanUp] Called." );	
	delete( this->ns );
	this->logger.log( Logger::DEBUG, "[CORBAHelper#cleanUp] Destroy POAs." );	
	this->explicitActPOA->destroy( true, true );	
	this->rootPOA->destroy( true, true );
	this->logger.log( Logger::DEBUG, "[CORBAHelper#cleanUp] Deactivate the POA manager." );	
	this->rootPOAManager->deactivate( true, true );
	this->logger.log( Logger::DEBUG, "[CORBAHelper#cleanUp] Destroy the ORBA instance." );		
	this->orb->destroy();
}

RemoteServiceInfo& CORBAHelper::convertToServiceInfo( const string& serviceName,
			CORBAService_ptr service, const CORBAServiceProps& props )
{	
	logger.log( Logger::DEBUG, "[CORBAHelper#convertToServiceInfo] Called, serviceName: %1", serviceName );
	string objID = this->objectToString( service );
	RemoteServiceInfo* info = new RemoteServiceInfo( serviceName, CORBAService::_duplicate( service ), 
		objID , this->convertServiceProperties( props ) );	
	logger.log( Logger::DEBUG, "[CORBAHelper#convertToServiceInfo] Return RemoteServiceInfo object." );	
	return (*info);
}

RemoteServiceListenerInfo& CORBAHelper::convertToServiceListenerInfo( const string& bundleName,
			const string& serviceName,
			CORBAServiceListener_ptr service )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#convertToServiceListenerInfo] Called, bundle name: %1, service name: %2",
		bundleName, serviceName );	
	RemoteServiceListenerInfo* info = new RemoteServiceListenerInfo( bundleName, serviceName, CORBAServiceListener::_duplicate( service ),
		this->objectToString( service ) );
	return (*info);
}

RemoteServiceReference* CORBAHelper::convertServiceReference( const CORBAServiceReference& ref )
{
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceReference] Called." );
	Properties properties = this->convertServiceProperties( ref.props );

	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceReference] Called." );
	
	string ior = this->orb->object_to_string( CORBAService::_duplicate( ref.service ) );

	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceReference] IOR: %1", ior );
	
	return new RemoteServiceReference( CORBA::string_dup( ref.serviceName ), properties, CORBAService::_duplicate( ref.service ), ior );
}


CORBAServiceProps CORBAHelper::convertServiceProperties( const Properties& props )
{
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Called, properties: %1",
		props.toString() );
	int size = props.getSize();

	CORBAServiceProps remoteServiceProps;

	CORBAServiceProps::_keys_seq keys( size );
	keys.length( size );
	
	CORBAServiceProps::_values_seq values( size );
	values.length( size );
	
	int counter = 0; 

	map<string,string>::const_iterator iter;
	for ( iter = props.begin(); iter != props.end(); iter++ )
	{		
		keys[counter] = CORBA::string_dup( (iter->first).c_str() );
		values[counter] = CORBA::string_dup( (iter->second).c_str() );
		counter++;
	}

	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Iterating finished." );

	remoteServiceProps.keys = keys;
	remoteServiceProps.values = values;

	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Left." );
	return remoteServiceProps;
}

Properties CORBAHelper::convertServiceProperties( const CORBAServiceProps& props )
{
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Called." );
	CORBAServiceProps::_keys_seq keys = props.keys;
	CORBAServiceProps::_values_seq values = props.values;

	
	int len = keys.length();
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Length of keys: %1", len );
	Properties properties;
	
	for ( int i=0; i< len; i++ )
	{
		logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Put key '%1' and value '%2'", keys[i], values[i] );
		properties.put( CORBA::string_dup( keys[i] ), CORBA::string_dup( values[i] ) );
	}
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Left." );
	return properties;
}

CORBAServiceReference CORBAHelper::convertServiceReference( const RemoteServiceReference& reference )
{	
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceReference] Called, RemoteServiceReference object: %1", reference.toString() );
	CORBAServiceProps remoteServiceProps = this->convertServiceProperties( reference.getServiceProperties() );
	
	CORBAServiceReference remoteRef;
	
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceReference] Filling CORBAServiceReference object." );
	
	remoteRef.props = remoteServiceProps;
	remoteRef.serviceName = CORBA::string_dup( reference.getServiceName().c_str() );
	remoteRef.service = CORBAService::_duplicate( reference.getRemoteService() );

	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceReference] Return CORBAServiceReference object." );
	
	return remoteRef;
}

ServiceEvent CORBAHelper::convertEvent( const CORBAServiceEvent& eventObj )
{
	logger.log( Logger::DEBUG, "[CORBAHelper#convertEvent] Called." );
	
	RemoteServiceReference* corbaServiceReference = this->convertServiceReference( eventObj.serviceRef );
	logger.log( Logger::DEBUG, "[CORBAHelper#convertEvent] RemoteServiceReference object created." );
	ServiceEvent serviceEvent( eventObj.serviceType, (*corbaServiceReference) ); 
	logger.log( Logger::DEBUG, "[CORBAHelper#convertEvent] ServiceEvent object created." );
	
	return serviceEvent;
}

CORBAServiceEvent CORBAHelper::convertEvent( const ServiceEvent& eventObj )
{
	logger.log( Logger::DEBUG, "[CORBAHelper#convertEvent] Called, service event: %1", eventObj.toString() );
	CORBAServiceEvent remoteServiceEvent;
	logger.log( Logger::DEBUG, "[CORBAHelper#convertEvent] Create RemoteServiceReference object." );	
	RemoteServiceReference* corbaServiceReference = dynamic_cast<RemoteServiceReference*> ( &( eventObj.getReference()) );
	remoteServiceEvent.serviceRef = this->convertServiceReference( *corbaServiceReference );
	remoteServiceEvent.serviceType = eventObj.getType();
	logger.log( Logger::DEBUG, "[CORBAHelper#convertEvent] Return CORBAServiceEvent object." );	
	return remoteServiceEvent;
}