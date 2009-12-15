package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL interface "CORBAAdminService".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceHolder	implements org.omg.CORBA.portable.Streamable{
	 public CORBAAdminService value;
	public CORBAAdminServiceHolder()
	{
	}
	public CORBAAdminServiceHolder (final CORBAAdminService initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type()
	{
		return CORBAAdminServiceHelper.type();
	}
	public void _read (final org.omg.CORBA.portable.InputStream in)
	{
		value = CORBAAdminServiceHelper.read (in);
	}
	public void _write (final org.omg.CORBA.portable.OutputStream _out)
	{
		CORBAAdminServiceHelper.write (_out,value);
	}
}
