#include "DataConverter.h"

#include "sof/framework/Properties.h"

#include "./generated/CORBAAdminObjects.h"

using namespace sof::framework;
using namespace sof::services::admin::remote::corba;
using namespace sof::services::admin::remote::corba::generated;

Logger& DataConverter::logger = LoggerFactory::getLogger( "Remote-Framework" );

CORBABundleNameSequence* DataConverter::convert( const vector<string>& bundleNames )
{
	logger.log( Logger::DEBUG, "[DataConverter#convert] Called." );
	CORBABundleNameSequence* sequence = new CORBABundleNameSequence();

	sequence->length( bundleNames.size() );
	
	int counter = 0;
	vector<string>::const_iterator iter;

	logger.log( Logger::DEBUG, "[DataConverter#convert] Iterate..." );
	for ( iter = bundleNames.begin(); iter != bundleNames.end(); iter++ )
	{		
		logger.log( Logger::DEBUG, "[DataConverter#convert] Bundle name: %1", (*iter) );
		(*sequence)[counter] = CORBA::string_dup( iter->c_str() );	
		counter++;
	}
	logger.log( Logger::DEBUG, "[DataConverter#convert] Return CORBABundleNameSequence object." );
	return sequence;
}


CORBAAdminServiceProps* DataConverter::convert( const Properties& props )
{
	CORBAAdminServiceProps* adminServiceProps = new CORBAAdminServiceProps();
	
	CORBAPropertyKeysSequence* keys = new CORBAPropertyKeysSequence();
	keys->length( props.getSize() );

	CORBAPropertyValuesSequence* values = new CORBAPropertyValuesSequence();
	values->length( props.getSize() );

	int counter = 0;
	map<string,string>::const_iterator iter;
	for ( iter = props.begin(); iter != props.end(); iter++ )
	{				
		(*keys)[counter] = CORBA::string_dup( (iter->first).c_str() );
		(*values)[counter] = CORBA::string_dup( (iter->second).c_str() );
		counter++;
	}

	adminServiceProps->keys = (*keys);
	adminServiceProps->values = (*values);

	return adminServiceProps;
}

CORBAAdminServiceInfo* DataConverter::convert( const RemoteServiceInfo& serviceInfo )
{
	logger.log( Logger::DEBUG, "[DataConverter#convert] Called." );
	CORBAAdminServiceInfo* corbaAdminServiceInfo = new CORBAAdminServiceInfo();
	logger.log( Logger::DEBUG, "[DataConverter#convert] Called, ID: %1, service name: %2", 
		serviceInfo.getRemoteServiceID(), serviceInfo.getServiceName() );
	corbaAdminServiceInfo->objID = CORBA::string_dup( serviceInfo.getRemoteServiceID().c_str() );
	corbaAdminServiceInfo->properties = ( * ( convert( serviceInfo.getProperties() ) ) );
	corbaAdminServiceInfo->serviceName = CORBA::string_dup( serviceInfo.getServiceName().c_str() );
	return corbaAdminServiceInfo;
}

CORBAAdminServiceListenerInfo* DataConverter::convert( const RemoteServiceListenerInfo& serviceListenerInfo )
{
	logger.log( Logger::DEBUG, "[DataConverter#convert] Called, serviceListenerInfo: %1", serviceListenerInfo.toString() );
	CORBAAdminServiceListenerInfo* corbaAdminServiceListenerInfo = new CORBAAdminServiceListenerInfo();
	corbaAdminServiceListenerInfo->serviceName = CORBA::string_dup( serviceListenerInfo.getServiceName().c_str() );	
	return corbaAdminServiceListenerInfo;
}

CORBAAdminServiceInfoSequence* DataConverter::convert( const vector<ServiceInfo*>& serviceInfo )
{
	logger.log( Logger::DEBUG, "[DataConverter#convert] Called." );
	CORBAAdminServiceInfoSequence* seq = new CORBAAdminServiceInfoSequence();
	seq->length( serviceInfo.size() );
	vector<ServiceInfo*>::const_iterator it;
	int counter = 0;
	for( it = serviceInfo.begin(); it != serviceInfo.end(); it++ )
	{
		RemoteServiceInfo* servInfoObj = dynamic_cast<RemoteServiceInfo*>(*it);
		logger.log( Logger::DEBUG, "[DataConverter#convert] ServiceInfo object: %1", (*servInfoObj).toString() );
		(*seq)[counter] = ( * ( convert( (*servInfoObj) ) ) );
		counter++;
	}
	return seq;
}

CORBAAdminServiceListenerInfoSequence* DataConverter::convert( const vector<ServiceListenerInfo*>& serviceListenerInfo )
{
	CORBAAdminServiceListenerInfoSequence* seq = new CORBAAdminServiceListenerInfoSequence();
	seq->length( serviceListenerInfo.size() );
	vector<ServiceListenerInfo*>::const_iterator it;
	int counter = 0;
	for( it = serviceListenerInfo.begin(); it != serviceListenerInfo.end(); it++ )
	{
		RemoteServiceListenerInfo* servListenerInfoObj = dynamic_cast<RemoteServiceListenerInfo*>(*it);
		(*seq)[counter] = ( * ( convert( (*servListenerInfoObj) ) ) );
		counter++;
	}
	return seq;
}


