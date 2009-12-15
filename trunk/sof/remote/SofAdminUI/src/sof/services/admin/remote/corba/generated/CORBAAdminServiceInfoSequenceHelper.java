package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL alias "CORBAAdminServiceInfoSequence".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceInfoSequenceHelper
{
	private static org.omg.CORBA.TypeCode _type = null;

	public static void insert (org.omg.CORBA.Any any, sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] s)
	{
		any.type (type ());
		write (any.create_output_stream (), s);
	}

	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] extract (final org.omg.CORBA.Any any)
	{
		return read (any.create_input_stream ());
	}

	public static org.omg.CORBA.TypeCode type ()
	{
		if (_type == null)
		{
			_type = org.omg.CORBA.ORB.init().create_alias_tc(sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoSequenceHelper.id(), "CORBAAdminServiceInfoSequence",org.omg.CORBA.ORB.init().create_sequence_tc(0, sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoHelper.type()));
		}
		return _type;
	}

	public static String id()
	{
		return "IDL:sof/services/admin/remote/corba/generated/CORBAAdminServiceInfoSequence:1.0";
	}
	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] read (final org.omg.CORBA.portable.InputStream _in)
	{
		sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] _result;
		int _l_result2 = _in.read_long();
		try
		{
			 int x = _in.available();
			 if ( x > 0 && _l_result2 > x )
				{
					throw new org.omg.CORBA.MARSHAL("Sequence length too large. Only " + x + " available and trying to assign " + _l_result2);
				}
		}
		catch (java.io.IOException e)
		{
		}
		_result = new sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[_l_result2];
		for (int i=0;i<_result.length;i++)
		{
			_result[i]=sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoHelper.read(_in);
		}

		return _result;
	}

	public static void write (final org.omg.CORBA.portable.OutputStream _out, sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] _s)
	{
		
		_out.write_long(_s.length);
		for (int i=0; i<_s.length;i++)
		{
			sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoHelper.write(_out,_s[i]);
		}

	}
}
