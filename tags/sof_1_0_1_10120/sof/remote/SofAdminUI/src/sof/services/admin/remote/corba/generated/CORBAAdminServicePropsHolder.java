package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL struct "CORBAAdminServiceProps".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServicePropsHolder
	implements org.omg.CORBA.portable.Streamable
{
	public sof.services.admin.remote.corba.generated.CORBAAdminServiceProps value;

	public CORBAAdminServicePropsHolder ()
	{
	}
	public CORBAAdminServicePropsHolder(final sof.services.admin.remote.corba.generated.CORBAAdminServiceProps initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type ()
	{
		return sof.services.admin.remote.corba.generated.CORBAAdminServicePropsHelper.type ();
	}
	public void _read(final org.omg.CORBA.portable.InputStream _in)
	{
		value = sof.services.admin.remote.corba.generated.CORBAAdminServicePropsHelper.read(_in);
	}
	public void _write(final org.omg.CORBA.portable.OutputStream _out)
	{
		sof.services.admin.remote.corba.generated.CORBAAdminServicePropsHelper.write(_out, value);
	}
}
