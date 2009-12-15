package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL alias "CORBAAdminServiceInfoSequence".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceInfoSequenceHolder
	implements org.omg.CORBA.portable.Streamable
{
	public sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] value;

	public CORBAAdminServiceInfoSequenceHolder ()
	{
	}
	public CORBAAdminServiceInfoSequenceHolder (final sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type ()
	{
		return CORBAAdminServiceInfoSequenceHelper.type ();
	}
	public void _read (final org.omg.CORBA.portable.InputStream in)
	{
		value = CORBAAdminServiceInfoSequenceHelper.read (in);
	}
	public void _write (final org.omg.CORBA.portable.OutputStream out)
	{
		CORBAAdminServiceInfoSequenceHelper.write (out,value);
	}
}
