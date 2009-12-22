package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL struct "CORBAAdminServiceListenerInfo".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceListenerInfoHolder
	implements org.omg.CORBA.portable.Streamable
{
	public sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo value;

	public CORBAAdminServiceListenerInfoHolder ()
	{
	}
	public CORBAAdminServiceListenerInfoHolder(final sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type ()
	{
		return sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoHelper.type ();
	}
	public void _read(final org.omg.CORBA.portable.InputStream _in)
	{
		value = sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoHelper.read(_in);
	}
	public void _write(final org.omg.CORBA.portable.OutputStream _out)
	{
		sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoHelper.write(_out, value);
	}
}
