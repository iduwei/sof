package sof.services.admin.remote.corba.generated;


/**
 * Generated from IDL struct "CORBAAdminServiceInfo".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceInfoHelper
{
	private static org.omg.CORBA.TypeCode _type = null;
	public static org.omg.CORBA.TypeCode type ()
	{
		if (_type == null)
		{
			_type = org.omg.CORBA.ORB.init().create_struct_tc(sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoHelper.id(),"CORBAAdminServiceInfo",new org.omg.CORBA.StructMember[]{new org.omg.CORBA.StructMember("serviceName", org.omg.CORBA.ORB.init().create_string_tc(0), null),new org.omg.CORBA.StructMember("properties", sof.services.admin.remote.corba.generated.CORBAAdminServicePropsHelper.type(), null),new org.omg.CORBA.StructMember("objID", org.omg.CORBA.ORB.init().create_string_tc(0), null)});
		}
		return _type;
	}

	public static void insert (final org.omg.CORBA.Any any, final sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo s)
	{
		any.type(type());
		write( any.create_output_stream(),s);
	}

	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo extract (final org.omg.CORBA.Any any)
	{
		return read(any.create_input_stream());
	}

	public static String id()
	{
		return "IDL:sof/services/admin/remote/corba/generated/CORBAAdminServiceInfo:1.0";
	}
	public static sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo read (final org.omg.CORBA.portable.InputStream in)
	{
		sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo result = new sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo();
		result.serviceName=in.read_string();
		result.properties=sof.services.admin.remote.corba.generated.CORBAAdminServicePropsHelper.read(in);
		result.objID=in.read_string();
		return result;
	}
	public static void write (final org.omg.CORBA.portable.OutputStream out, final sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo s)
	{
		out.write_string(s.serviceName);
		sof.services.admin.remote.corba.generated.CORBAAdminServicePropsHelper.write(out,s.properties);
		out.write_string(s.objID);
	}
}
