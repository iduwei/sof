package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL struct "CORBAAdminServiceInfo".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceInfo
	implements org.omg.CORBA.portable.IDLEntity
{
	public CORBAAdminServiceInfo(){}
	public java.lang.String serviceName = "";
	public sof.services.admin.remote.corba.generated.CORBAAdminServiceProps properties;
	public java.lang.String objID = "";
	public CORBAAdminServiceInfo(java.lang.String serviceName, sof.services.admin.remote.corba.generated.CORBAAdminServiceProps properties, java.lang.String objID)
	{
		this.serviceName = serviceName;
		this.properties = properties;
		this.objID = objID;
	}
}
