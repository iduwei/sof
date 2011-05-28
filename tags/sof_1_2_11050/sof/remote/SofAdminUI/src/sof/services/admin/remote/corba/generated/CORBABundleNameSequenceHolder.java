package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL alias "CORBABundleNameSequence".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBABundleNameSequenceHolder
	implements org.omg.CORBA.portable.Streamable
{
	public java.lang.String[] value;

	public CORBABundleNameSequenceHolder ()
	{
	}
	public CORBABundleNameSequenceHolder (final java.lang.String[] initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type ()
	{
		return CORBABundleNameSequenceHelper.type ();
	}
	public void _read (final org.omg.CORBA.portable.InputStream in)
	{
		value = CORBABundleNameSequenceHelper.read (in);
	}
	public void _write (final org.omg.CORBA.portable.OutputStream out)
	{
		CORBABundleNameSequenceHelper.write (out,value);
	}
}
