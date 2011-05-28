package sof.services.admin.remote.corba.generated;


/**
 * Generated from IDL interface "CORBAAdminService".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public final class CORBAAdminServiceHelper
{
	public static void insert (final org.omg.CORBA.Any any, final sof.services.admin.remote.corba.generated.CORBAAdminService s)
	{
			any.insert_Object(s);
	}
	public static sof.services.admin.remote.corba.generated.CORBAAdminService extract(final org.omg.CORBA.Any any)
	{
		return narrow(any.extract_Object()) ;
	}
	public static org.omg.CORBA.TypeCode type()
	{
		return org.omg.CORBA.ORB.init().create_interface_tc("IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0", "CORBAAdminService");
	}
	public static String id()
	{
		return "IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0";
	}
	public static CORBAAdminService read(final org.omg.CORBA.portable.InputStream in)
	{
		return narrow(in.read_Object(sof.services.admin.remote.corba.generated._CORBAAdminServiceStub.class));
	}
	public static void write(final org.omg.CORBA.portable.OutputStream _out, final sof.services.admin.remote.corba.generated.CORBAAdminService s)
	{
		_out.write_Object(s);
	}
	public static sof.services.admin.remote.corba.generated.CORBAAdminService narrow(final org.omg.CORBA.Object obj)
	{
		if (obj == null)
		{
			return null;
		}
		else if (obj instanceof sof.services.admin.remote.corba.generated.CORBAAdminService)
		{
			return (sof.services.admin.remote.corba.generated.CORBAAdminService)obj;
		}
		else if (obj._is_a("IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0"))
		{
			sof.services.admin.remote.corba.generated._CORBAAdminServiceStub stub;
			stub = new sof.services.admin.remote.corba.generated._CORBAAdminServiceStub();
			stub._set_delegate(((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate());
			return stub;
		}
		else
		{
			throw new org.omg.CORBA.BAD_PARAM("Narrow failed");
		}
	}
	public static sof.services.admin.remote.corba.generated.CORBAAdminService unchecked_narrow(final org.omg.CORBA.Object obj)
	{
		if (obj == null)
		{
			return null;
		}
		else if (obj instanceof sof.services.admin.remote.corba.generated.CORBAAdminService)
		{
			return (sof.services.admin.remote.corba.generated.CORBAAdminService)obj;
		}
		else
		{
			sof.services.admin.remote.corba.generated._CORBAAdminServiceStub stub;
			stub = new sof.services.admin.remote.corba.generated._CORBAAdminServiceStub();
			stub._set_delegate(((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate());
			return stub;
		}
	}
}
