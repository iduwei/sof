package sof.services.admin.remote.corba.generated;

import org.omg.PortableServer.POA;

/**
 * Generated from IDL interface "CORBAAdminService".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public class CORBAAdminServicePOATie
	extends CORBAAdminServicePOA
{
	private CORBAAdminServiceOperations _delegate;

	private POA _poa;
	public CORBAAdminServicePOATie(CORBAAdminServiceOperations delegate)
	{
		_delegate = delegate;
	}
	public CORBAAdminServicePOATie(CORBAAdminServiceOperations delegate, POA poa)
	{
		_delegate = delegate;
		_poa = poa;
	}
	public sof.services.admin.remote.corba.generated.CORBAAdminService _this()
	{
		return sof.services.admin.remote.corba.generated.CORBAAdminServiceHelper.narrow(_this_object());
	}
	public sof.services.admin.remote.corba.generated.CORBAAdminService _this(org.omg.CORBA.ORB orb)
	{
		return sof.services.admin.remote.corba.generated.CORBAAdminServiceHelper.narrow(_this_object(orb));
	}
	public CORBAAdminServiceOperations _delegate()
	{
		return _delegate;
	}
	public void _delegate(CORBAAdminServiceOperations delegate)
	{
		_delegate = delegate;
	}
	public POA _default_POA()
	{
		if (_poa != null)
		{
			return _poa;
		}
		return super._default_POA();
	}
	public sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] getUsedServices(java.lang.String bundleName)
	{
		return _delegate.getUsedServices(bundleName);
	}

	public sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] getRegisteredServices(java.lang.String bundleName)
	{
		return _delegate.getRegisteredServices(bundleName);
	}

	public sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] getRegisteredServiceListeners(java.lang.String bundleName)
	{
		return _delegate.getRegisteredServiceListeners(bundleName);
	}

	public java.lang.String[] getBundleNames()
	{
		return _delegate.getBundleNames();
	}

}
