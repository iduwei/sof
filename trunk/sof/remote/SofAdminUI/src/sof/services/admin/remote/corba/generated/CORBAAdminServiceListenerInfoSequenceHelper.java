package sof.services.admin.remote.corba.generated;

/**
 * Generated from IDL alias "CORBAAdminServiceListenerInfoSequence".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceListenerInfoSequenceHelper
{
	private static org.omg.CORBA.TypeCode _type = null;

	public static void insert (org.omg.CORBA.Any any, sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] s)
	{
		any.type (type ());
		write (any.create_output_stream (), s);
	}

	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] extract (final org.omg.CORBA.Any any)
	{
		return read (any.create_input_stream ());
	}

	public static org.omg.CORBA.TypeCode type ()
	{
		if (_type == null)
		{
			_type = org.omg.CORBA.ORB.init().create_alias_tc(sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoSequenceHelper.id(), "CORBAAdminServiceListenerInfoSequence",org.omg.CORBA.ORB.init().create_sequence_tc(0, sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoHelper.type()));
		}
		return _type;
	}

	public static String id()
	{
		return "IDL:sof/services/admin/remote/corba/generated/CORBAAdminServiceListenerInfoSequence:1.0";
	}
	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] read (final org.omg.CORBA.portable.InputStream _in)
	{
		sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] _result;
		int _l_result3 = _in.read_long();
		try
		{
			 int x = _in.available();
			 if ( x > 0 && _l_result3 > x )
				{
					throw new org.omg.CORBA.MARSHAL("Sequence length too large. Only " + x + " available and trying to assign " + _l_result3);
				}
		}
		catch (java.io.IOException e)
		{
		}
		_result = new sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[_l_result3];
		for (int i=0;i<_result.length;i++)
		{
			_result[i]=sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoHelper.read(_in);
		}

		return _result;
	}

	public static void write (final org.omg.CORBA.portable.OutputStream _out, sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] _s)
	{
		
		_out.write_long(_s.length);
		for (int i=0; i<_s.length;i++)
		{
			sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoHelper.write(_out,_s[i]);
		}

	}
}
