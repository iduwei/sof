#include "TestHelper.h"


int TestHelper::isServiceListenerRegisteredByBundle( IRegistry& reg, const string& bundleName, const string& serviceName )
{
	BundleInfoBase* bi = reg.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return 0;
	}
	vector<ServiceListenerInfoPtr> serviceListenerInfos = bi->getRegisteredListeners();
	vector<ServiceListenerInfoPtr>::iterator iter;
	int counter = 0;
	for ( iter = serviceListenerInfos.begin(); iter != serviceListenerInfos.end(); ++iter )
	{
		if ( (*iter)->getBundleName() == bundleName &&
			(*iter)->getServiceName() == serviceName )
		{
			counter++;
		}
	}
	return counter;
}

int TestHelper::isServiceRegisteredByBundle( IRegistry& registry, const string& bundleName, const string& serviceName, int propsSize )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return 0;
	}
	vector<ServiceInfoPtr> serviceInfos = bi->getRegisteredServices();
	vector<ServiceInfoPtr>::iterator iter;
	int foundCounter = 0;
	for ( iter = serviceInfos.begin(); iter != serviceInfos.end(); ++iter )
	{
		if ( (*iter)->getServiceName() == serviceName &&
			(*iter)->getProperties().getSize() == propsSize )
		{
			foundCounter++;
		}
	}
	return foundCounter;
}

int TestHelper::isServiceUsedByBundle( IRegistry& registry, const string& bundleName, const string& serviceName, int propsSize )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return 0;
	}
	vector<ServiceInfoPtr> serviceInfos = bi->getUsedServices();
	vector<ServiceInfoPtr>::iterator iter;
	int foundCounter = 0;
	for ( iter = serviceInfos.begin(); iter != serviceInfos.end(); ++iter )
	{
		if ( (*iter)->getServiceName() == serviceName &&
			(*iter)->getProperties().getSize() == propsSize )
		{
			foundCounter++;
		}
	}
	return foundCounter;
}

int TestHelper::isServiceListenerRegisteredByBundle( IRegistry& reg, const string& bundleName )
{
	BundleInfoBase* bi = reg.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return 0;
	}
	vector<ServiceListenerInfoPtr> serviceListenerInfos = bi->getRegisteredListeners();
	return serviceListenerInfos.size();
}

bool TestHelper::isBundleStarted( IRegistry& reg, const string& bundleName )
{
	BundleInfoBase* bi = reg.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return false;
	} 
	else
	{
		return true;
	}
}

int TestHelper::isServiceRegisteredByBundle( IRegistry& registry, const string& bundleName )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return 0;
	}
	vector<ServiceInfoPtr> serviceInfos = bi->getRegisteredServices();
	return serviceInfos.size();
}

int TestHelper::isServiceUsedByBundle( IRegistry& registry, const string& bundleName )
{
	BundleInfoBase* bi = registry.getBundleInfo( bundleName );	
	if ( bi == 0 )
	{
		return 0;
	}
	vector<ServiceInfoPtr> serviceInfos = bi->getUsedServices();
	return serviceInfos.size();
}