package sof.services.admin.remote.corba.generated;


/**
 * Generated from IDL interface "CORBAAdminService".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public interface CORBAAdminServiceOperations
{
	/* constants */
	/* operations  */
	java.lang.String[] getBundleNames();
	sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] getUsedServices(java.lang.String bundleName);
	sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] getRegisteredServices(java.lang.String bundleName);
	sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] getRegisteredServiceListeners(java.lang.String bundleName);
}
