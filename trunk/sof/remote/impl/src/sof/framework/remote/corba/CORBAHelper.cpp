#include "CORBAHelper.h"

#include <pthread.h>

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
    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow( poaobj);
    PortableServer::POAManager_var rootPOAManager = rootPOA->the_POAManager();
	this->ns = new CORBANamingServiceImpl( this->orb );	

	try {
	  CORBA::PolicyList policies;
	  policies.length(1);
	  policies[0] = rootPOA->create_implicit_activation_policy( PortableServer::NO_IMPLICIT_ACTIVATION );

	  this->logger.log( Logger::DEBUG, "[CORBAHelper#initORB] Creating the POA instance." );
	  this->explicitActPOA = rootPOA->create_POA("MyPOA", rootPOAManager, policies);

	  if (CORBA::is_nil(this->explicitActPOA)){
		// handle this error
	  }

	  // activate POA manager
	  rootPOAManager->activate();

	} catch (const PortableServer::POA::AdapterAlreadyExists& e){
		this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] POA already exists." );	  
		try {
			this->explicitActPOA = rootPOA->find_POA("MyPOA", 0);
		} catch (const PortableServer::POA::AdapterNonExistent&){
			this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] No POA found." );	  		
		}
		} catch (const PortableServer::POA::InvalidPolicy& e){
			// the choosen policy combination is invalid
			this->logger.log( Logger::ERROR_, "[CORBAHelper#initORB] Invalid policy used." );	  	
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
	try {
		PortableServer::ObjectId_var oid = this->explicitActPOA->reference_to_id( obj );
		this->explicitActPOA->deactivate_object( oid );
		
	} catch (const PortableServer::POA::WrongPolicy& e){
	  // TODO: handle error
		this->logger.log( Logger::ERROR_, "[CORBAHelper#deactivateObject] Wrong policy." );	
	} catch (const PortableServer::POA::ServantAlreadyActive&){
	  // TODO: handle error
		this->logger.log( Logger::ERROR_, "[CORBAHelper#deactivateObject] Servant already active." );	
	}	
}

CORBA::Object_var CORBAHelper::activateObject( const PortableServer::Servant& servant )
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#activateObject] Called" );	
	CORBA::Object_var obj;

	try {
	  
		this->logger.log( Logger::DEBUG, "[CORBAHelper#activateObject] Activate object." );	
		PortableServer::ObjectId_var oid = this->explicitActPOA->activate_object( servant );
		
		// get a reference
		obj = this->explicitActPOA->id_to_reference(oid);
		logger.log( Logger::DEBUG, "[CORBAHelper#activateObject] OID: %1", obj->_repoid() );
		if (CORBA::is_nil(obj)){
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
}

void CORBAHelper::startAndWait()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#startAndWait] Run the ORB." );		
	this->run_orb();
}

void *ThreadStartup(void *_tgtObject) {
  CORBAHelper *tgtObject = (CORBAHelper *)_tgtObject;
  tgtObject->run_orb();
  return NULL;
}

void CORBAHelper::run_orb()
{
	this->logger.log( Logger::DEBUG, "[CORBAHelper#run_orb] Called." );	
	this->orb->run();   
}

void CORBAHelper::stop()
{
	// TODO: implement
	this->logger.log( Logger::DEBUG, "[CORBAHelper#stop] Called." );	
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
	logger.log( Logger::DEBUG, "[CORBAHelper#convertServiceProperties] Lenght of keys: %1", len );
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