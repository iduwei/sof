package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL alias "CORBAPropertyKeysSequence".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAPropertyKeysSequenceHolder
	implements org.omg.CORBA.portable.Streamable
{
	public java.lang.String[] value;

	public CORBAPropertyKeysSequenceHolder ()
	{
	}
	public CORBAPropertyKeysSequenceHolder (final java.lang.String[] initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type ()
	{
		return CORBAPropertyKeysSequenceHelper.type ();
	}
	public void _read (final org.omg.CORBA.portable.InputStream in)
	{
		value = CORBAPropertyKeysSequenceHelper.read (in);
	}
	public void _write (final org.omg.CORBA.portable.OutputStream out)
	{
		CORBAPropertyKeysSequenceHelper.write (out,value);
	}
}
