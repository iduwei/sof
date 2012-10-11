package sof.services.admin.remote.corba.generated;


/**
 * Generated from IDL struct "CORBAAdminServiceProps".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServicePropsHelper
{
	private static org.omg.CORBA.TypeCode _type = null;
	public static org.omg.CORBA.TypeCode type ()
	{
		if (_type == null)
		{
			_type = org.omg.CORBA.ORB.init().create_struct_tc(sof.services.admin.remote.corba.generated.CORBAAdminServicePropsHelper.id(),"CORBAAdminServiceProps",new org.omg.CORBA.StructMember[]{new org.omg.CORBA.StructMember("keys", sof.services.admin.remote.corba.generated.CORBAPropertyKeysSequenceHelper.type(), null),new org.omg.CORBA.StructMember("values", sof.services.admin.remote.corba.generated.CORBAPropertyValuesSequenceHelper.type(), null)});
		}
		return _type;
	}

	public static void insert (final org.omg.CORBA.Any any, final sof.services.admin.remote.corba.generated.CORBAAdminServiceProps s)
	{
		any.type(type());
		write( any.create_output_stream(),s);
	}

	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceProps extract (final org.omg.CORBA.Any any)
	{
		return read(any.create_input_stream());
	}

	public static String id()
	{
		return "IDL:sof/services/admin/remote/corba/generated/CORBAAdminServiceProps:1.0";
	}
	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceProps read (final org.omg.CORBA.portable.InputStream in)
	{
		sof.services.admin.remote.corba.generated.CORBAAdminServiceProps result = new sof.services.admin.remote.corba.generated.CORBAAdminServiceProps();
		result.keys = sof.services.admin.remote.corba.generated.CORBAPropertyKeysSequenceHelper.read(in);
		result.values = sof.services.admin.remote.corba.generated.CORBAPropertyValuesSequenceHelper.read(in);
		return result;
	}
	public static void write (final org.omg.CORBA.portable.OutputStream out, final sof.services.admin.remote.corba.generated.CORBAAdminServiceProps s)
	{
		sof.services.admin.remote.corba.generated.CORBAPropertyKeysSequenceHelper.write(out,s.keys);
		sof.services.admin.remote.corba.generated.CORBAPropertyValuesSequenceHelper.write(out,s.values);
	}
}
