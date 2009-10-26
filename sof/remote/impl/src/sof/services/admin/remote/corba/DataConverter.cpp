#include "DataConverter.h"

#include "sof/framework/Properties.h"

#include "./generated/CORBAAdminObjects.h"

using namespace sof::framework;
using namespace sof::services::admin::remote::corba;
using namespace sof::services::admin::remote::corba::generated;


CORBABundleNameSequence_var DataConverter::convert( const vector<string>& bundleNames )
{
	CORBABundleNameSequence_var sequence = new CORBABundleNameSequence();

	sequence->length( bundleNames.size() );
	
	int counter = 0;
	vector<string>::const_iterator iter;

	for ( iter = bundleNames.begin(); iter != bundleNames.end(); iter++ )
	{		
		(*sequence)[counter] = CORBA::string_dup( iter->c_str() );		
		counter++;
	}

	return sequence;
}


CORBAAdminServiceProps_var DataConverter::convert( const Properties& props )
{
	CORBAAdminServiceProps_var adminServiceProps = new CORBAAdminServiceProps();
	
	CORBAPropertyKeysSequence_var keys = new CORBAPropertyKeysSequence();
	keys->length( props.getSize() );

	CORBAPropertyValuesSequence_var values = new CORBAPropertyValuesSequence();
	values->length( props.getSize() );

	int counter = 0;
	map<string,string>::const_iterator iter;
	for ( iter = props.begin(); iter != props.end(); iter++ )
	{				
		(*keys)[counter] = CORBA::string_dup( (iter->first).c_str() );
		(*values)[counter] = CORBA::string_dup( (iter->second).c_str() );
		counter++;
	}

	adminServiceProps->keys = keys;
	adminServiceProps->values = values;

	return adminServiceProps;
}

CORBAAdminServiceInfo_var DataConverter::convert( const RemoteServiceInfo& serviceInfo )
{
	CORBAAdminServiceInfo_var corbaAdminServiceInfo = new CORBAAdminServiceInfo();
	corbaAdminServiceInfo->objID = CORBA::string_dup( serviceInfo.getRemoteServiceID().c_str() );
	corbaAdminServiceInfo->properties = convert( serviceInfo.getProperties() );
	corbaAdminServiceInfo->serviceName = CORBA::string_dup( serviceInfo.getServiceName().c_str() );
	return corbaAdminServiceInfo;
}

CORBAAdminServiceListenerInfo_var DataConverter::convert( const RemoteServiceListenerInfo& serviceListenerInfo )
{
	
	CORBAAdminServiceListenerInfo_var corbaAdminServiceListenerInfo = new CORBAAdminServiceListenerInfo();
	corbaAdminServiceListenerInfo->serviceName = CORBA::string_dup( serviceListenerInfo.getServiceName().c_str() );	
	return corbaAdminServiceListenerInfo;
}

CORBAAdminServiceInfoSequence_var DataConverter::convert( const vector<ServiceInfo*>& serviceInfo )
{
	CORBAAdminServiceInfoSequence_var seq = new CORBAAdminServiceInfoSequence();
	seq->length( serviceInfo.size() );
	vector<ServiceInfo*>::const_iterator it;
	int counter = 0;
	for( it = serviceInfo.begin(); it != serviceInfo.end(); it++ )
	{
		RemoteServiceInfo* servInfoObj = dynamic_cast<RemoteServiceInfo*>(*it);
		(*seq)[counter] = convert( (*servInfoObj) );
	}
	return seq;
}

CORBAAdminServiceListenerInfoSequence_var DataConverter::convert( const vector<ServiceListenerInfo*>& serviceListenerInfo )
{
	CORBAAdminServiceListenerInfoSequence_var seq = new CORBAAdminServiceListenerInfoSequence();
	seq->length( serviceListenerInfo.size() );
	vector<ServiceListenerInfo*>::const_iterator it;
	int counter = 0;
	for( it = serviceListenerInfo.begin(); it != serviceListenerInfo.end(); it++ )
	{
		RemoteServiceListenerInfo* servListenerInfoObj = dynamic_cast<RemoteServiceListenerInfo*>(*it);
		(*seq)[counter] = convert( (*servListenerInfoObj) );
	}
	return seq;
}


