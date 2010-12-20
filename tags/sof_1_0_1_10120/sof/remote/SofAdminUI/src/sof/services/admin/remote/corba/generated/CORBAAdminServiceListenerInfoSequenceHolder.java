package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL alias "CORBAAdminServiceListenerInfoSequence".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceListenerInfoSequenceHolder
	implements org.omg.CORBA.portable.Streamable
{
	public sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] value;

	public CORBAAdminServiceListenerInfoSequenceHolder ()
	{
	}
	public CORBAAdminServiceListenerInfoSequenceHolder (final sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type ()
	{
		return CORBAAdminServiceListenerInfoSequenceHelper.type ();
	}
	public void _read (final org.omg.CORBA.portable.InputStream in)
	{
		value = CORBAAdminServiceListenerInfoSequenceHelper.read (in);
	}
	public void _write (final org.omg.CORBA.portable.OutputStream out)
	{
		CORBAAdminServiceListenerInfoSequenceHelper.write (out,value);
	}
}
