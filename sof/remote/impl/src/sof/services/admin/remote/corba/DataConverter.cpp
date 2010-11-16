#include "DataConverter.h"

#include "sof/framework/Properties.h"

#include "./generated/CORBAAdminObjects.h"

using namespace sof::framework;
using namespace sof::services::admin::remote::corba;
using namespace sof::services::admin::remote::corba::generated;

Logger& DataConverter::logger = LoggerFactory::getLogger( "Remote-Framework" );

CORBABundleNameSequence* DataConverter::convert( const vector<string>& bundleNames )
{
	logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Called." );
	CORBABundleNameSequence* sequence = new CORBABundleNameSequence();

	sequence->length( bundleNames.size() );
	
	int counter = 0;
	vector<string>::const_iterator iter;

	logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Iterate..." );
	for ( iter = bundleNames.begin(); iter != bundleNames.end(); ++iter )
	{		
		logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Bundle name: %1", (*iter) );
		(*sequence)[counter] = CORBA::string_dup( iter->c_str() );	
		counter++;
	}
	logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Return CORBABundleNameSequence object." );
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
	for ( iter = props.begin(); iter != props.end(); ++iter )
	{				
		(*keys)[counter] = CORBA::string_dup( (iter->first).c_str() );
		(*values)[counter] = CORBA::string_dup( (iter->second).c_str() );
		counter++;
	}

	adminServiceProps->keys = (*keys);
	adminServiceProps->values = (*values);

	return adminServiceProps;
}

CORBAAdminServiceInfo* DataConverter::convert( ServiceInfoPtr servInfo )
{
	logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Called." );
	RemoteServiceInfo* serviceInfo = dynamic_cast<RemoteServiceInfo*>(servInfo.GetRawPointer() );
	CORBAAdminServiceInfo* corbaAdminServiceInfo = new CORBAAdminServiceInfo();
	logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Called, ID: %1, service name: %2", 
		serviceInfo->getRemoteServiceID(), serviceInfo->getServiceName() );
	corbaAdminServiceInfo->objID = CORBA::string_dup( serviceInfo->getRemoteServiceID().c_str() );
	corbaAdminServiceInfo->properties = ( * ( convert( serviceInfo->getProperties() ) ) );
	corbaAdminServiceInfo->serviceName = CORBA::string_dup( serviceInfo->getServiceName().c_str() );
	return corbaAdminServiceInfo;
}

CORBAAdminServiceListenerInfo* DataConverter::convert( ServiceListenerInfoPtr serviceListenerInfo )
{
	logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Called, serviceListenerInfo: %1", serviceListenerInfo->toString() );
	CORBAAdminServiceListenerInfo* corbaAdminServiceListenerInfo = new CORBAAdminServiceListenerInfo();
	corbaAdminServiceListenerInfo->serviceName = CORBA::string_dup( serviceListenerInfo->getServiceName().c_str() );	
	return corbaAdminServiceListenerInfo;
}

CORBAAdminServiceInfoSequence* DataConverter::convert( const vector<ServiceInfoPtr>& serviceInfo )
{
	logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] Called." );
	CORBAAdminServiceInfoSequence* seq = new CORBAAdminServiceInfoSequence();
	seq->length( serviceInfo.size() );
	vector<ServiceInfoPtr>::const_iterator it;
	int counter = 0;
	for( it = serviceInfo.begin(); it != serviceInfo.end(); ++it )
	{
		// TODO: remove the following line no longer necessary
		//RemoteServiceInfoPtr servInfoObj = dynamic_cast<RemoteServiceInfoPtr>(*it);
		logger.log( Logger::LOG_DEBUG, "[DataConverter#convert] ServiceInfo object: %1", (*it)->toString() );
		(*seq)[counter] = ( * ( convert( (*it) ) ) );
		counter++;
	}
	return seq;
}

CORBAAdminServiceListenerInfoSequence* DataConverter::convert( const vector<ServiceListenerInfoPtr>& serviceListenerInfo )
{
	CORBAAdminServiceListenerInfoSequence* seq = new CORBAAdminServiceListenerInfoSequence();
	seq->length( serviceListenerInfo.size() );
	vector<ServiceListenerInfoPtr>::const_iterator it;
	int counter = 0;
	for( it = serviceListenerInfo.begin(); it != serviceListenerInfo.end(); ++it )
	{
		(*seq)[counter] = ( * ( convert( *it ) ) );
		counter++;
	}
	return seq;
}


