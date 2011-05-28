package sof.services.admin.remote.corba.generated;


/**
 * Generated from IDL interface "CORBAAdminService".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public abstract class CORBAAdminServicePOA
	extends org.omg.PortableServer.Servant
	implements org.omg.CORBA.portable.InvokeHandler, sof.services.admin.remote.corba.generated.CORBAAdminServiceOperations
{
	static private final java.util.Hashtable m_opsHash = new java.util.Hashtable();
	static
	{
		m_opsHash.put ( "getUsedServices", new java.lang.Integer(0));
		m_opsHash.put ( "getRegisteredServices", new java.lang.Integer(1));
		m_opsHash.put ( "getRegisteredServiceListeners", new java.lang.Integer(2));
		m_opsHash.put ( "getBundleNames", new java.lang.Integer(3));
	}
	private String[] ids = {"IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0"};
	public sof.services.admin.remote.corba.generated.CORBAAdminService _this()
	{
		return sof.services.admin.remote.corba.generated.CORBAAdminServiceHelper.narrow(_this_object());
	}
	public sof.services.admin.remote.corba.generated.CORBAAdminService _this(org.omg.CORBA.ORB orb)
	{
		return sof.services.admin.remote.corba.generated.CORBAAdminServiceHelper.narrow(_this_object(orb));
	}
	public org.omg.CORBA.portable.OutputStream _invoke(String method, org.omg.CORBA.portable.InputStream _input, org.omg.CORBA.portable.ResponseHandler handler)
		throws org.omg.CORBA.SystemException
	{
		org.omg.CORBA.portable.OutputStream _out = null;
		// do something
		// quick lookup of operation
		java.lang.Integer opsIndex = (java.lang.Integer)m_opsHash.get ( method );
		if ( null == opsIndex )
			throw new org.omg.CORBA.BAD_OPERATION(method + " not found");
		switch ( opsIndex.intValue() )
		{
			case 0: // getUsedServices
			{
				java.lang.String _arg0=_input.read_string();
				_out = handler.createReply();
				sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoSequenceHelper.write(_out,getUsedServices(_arg0));
				break;
			}
			case 1: // getRegisteredServices
			{
				java.lang.String _arg0=_input.read_string();
				_out = handler.createReply();
				sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoSequenceHelper.write(_out,getRegisteredServices(_arg0));
				break;
			}
			case 2: // getRegisteredServiceListeners
			{
				java.lang.String _arg0=_input.read_string();
				_out = handler.createReply();
				sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoSequenceHelper.write(_out,getRegisteredServiceListeners(_arg0));
				break;
			}
			case 3: // getBundleNames
			{
				_out = handler.createReply();
				sof.services.admin.remote.corba.generated.CORBABundleNameSequenceHelper.write(_out,getBundleNames());
				break;
			}
		}
		return _out;
	}

	public String[] _all_interfaces(org.omg.PortableServer.POA poa, byte[] obj_id)
	{
		return ids;
	}
}
