package sof.services.admin.remote.corba.generated;


/**
 * Generated from IDL interface "CORBAAdminService".
 *
 * @author JacORB IDL compiler V 2.3.1, 27-May-2009
 * @version generated at 20.10.2009 05:58:10
 */

public class _CORBAAdminServiceStub
	extends org.omg.CORBA.portable.ObjectImpl
	implements sof.services.admin.remote.corba.generated.CORBAAdminService
{
	private String[] ids = {"IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0"};
	public String[] _ids()
	{
		return ids;
	}

	public final static java.lang.Class _opsClass = sof.services.admin.remote.corba.generated.CORBAAdminServiceOperations.class;
	public sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] getUsedServices(java.lang.String bundleName)
	{
		while(true)
		{
		if(! this._is_local())
		{
			org.omg.CORBA.portable.InputStream _is = null;
			org.omg.CORBA.portable.OutputStream _os = null;
			try
			{
				_os = _request( "getUsedServices", true);
				_os.write_string(bundleName);
				_is = _invoke(_os);
				sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] _result = sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoSequenceHelper.read(_is);
				return _result;
			}
			catch( org.omg.CORBA.portable.RemarshalException _rx ){}
			catch( org.omg.CORBA.portable.ApplicationException _ax )
			{
				String _id = _ax.getId();
					try
					{
							_ax.getInputStream().close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				throw new RuntimeException("Unexpected exception " + _id );
			}
			finally
			{
				if (_os != null)
				{
					try
					{
						_os.close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				}
				this._releaseReply(_is);
			}
		}
		else
		{
			org.omg.CORBA.portable.ServantObject _so = _servant_preinvoke( "getUsedServices", _opsClass );
			if( _so == null )
				throw new org.omg.CORBA.UNKNOWN("local invocations not supported!");
			CORBAAdminServiceOperations _localServant = (CORBAAdminServiceOperations)_so.servant;
			sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] _result;
			try
			{
				_result = _localServant.getUsedServices(bundleName);
			}
			finally
			{
				_servant_postinvoke(_so);
			}
			return _result;
		}

		}

	}

	public sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] getRegisteredServices(java.lang.String bundleName)
	{
		while(true)
		{
		if(! this._is_local())
		{
			org.omg.CORBA.portable.InputStream _is = null;
			org.omg.CORBA.portable.OutputStream _os = null;
			try
			{
				_os = _request( "getRegisteredServices", true);
				_os.write_string(bundleName);
				_is = _invoke(_os);
				sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] _result = sof.services.admin.remote.corba.generated.CORBAAdminServiceInfoSequenceHelper.read(_is);
				return _result;
			}
			catch( org.omg.CORBA.portable.RemarshalException _rx ){}
			catch( org.omg.CORBA.portable.ApplicationException _ax )
			{
				String _id = _ax.getId();
					try
					{
							_ax.getInputStream().close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				throw new RuntimeException("Unexpected exception " + _id );
			}
			finally
			{
				if (_os != null)
				{
					try
					{
						_os.close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				}
				this._releaseReply(_is);
			}
		}
		else
		{
			org.omg.CORBA.portable.ServantObject _so = _servant_preinvoke( "getRegisteredServices", _opsClass );
			if( _so == null )
				throw new org.omg.CORBA.UNKNOWN("local invocations not supported!");
			CORBAAdminServiceOperations _localServant = (CORBAAdminServiceOperations)_so.servant;
			sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo[] _result;
			try
			{
				_result = _localServant.getRegisteredServices(bundleName);
			}
			finally
			{
				_servant_postinvoke(_so);
			}
			return _result;
		}

		}

	}

	public sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] getRegisteredServiceListeners(java.lang.String bundleName)
	{
		while(true)
		{
		if(! this._is_local())
		{
			org.omg.CORBA.portable.InputStream _is = null;
			org.omg.CORBA.portable.OutputStream _os = null;
			try
			{
				_os = _request( "getRegisteredServiceListeners", true);
				_os.write_string(bundleName);
				_is = _invoke(_os);
				sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] _result = sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfoSequenceHelper.read(_is);
				return _result;
			}
			catch( org.omg.CORBA.portable.RemarshalException _rx ){}
			catch( org.omg.CORBA.portable.ApplicationException _ax )
			{
				String _id = _ax.getId();
					try
					{
							_ax.getInputStream().close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				throw new RuntimeException("Unexpected exception " + _id );
			}
			finally
			{
				if (_os != null)
				{
					try
					{
						_os.close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				}
				this._releaseReply(_is);
			}
		}
		else
		{
			org.omg.CORBA.portable.ServantObject _so = _servant_preinvoke( "getRegisteredServiceListeners", _opsClass );
			if( _so == null )
				throw new org.omg.CORBA.UNKNOWN("local invocations not supported!");
			CORBAAdminServiceOperations _localServant = (CORBAAdminServiceOperations)_so.servant;
			sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo[] _result;
			try
			{
				_result = _localServant.getRegisteredServiceListeners(bundleName);
			}
			finally
			{
				_servant_postinvoke(_so);
			}
			return _result;
		}

		}

	}

	public java.lang.String[] getBundleNames()
	{
		while(true)
		{
		if(! this._is_local())
		{
			org.omg.CORBA.portable.InputStream _is = null;
			org.omg.CORBA.portable.OutputStream _os = null;
			try
			{
				_os = _request( "getBundleNames", true);
				_is = _invoke(_os);
				java.lang.String[] _result = sof.services.admin.remote.corba.generated.CORBABundleNameSequenceHelper.read(_is);
				return _result;
			}
			catch( org.omg.CORBA.portable.RemarshalException _rx ){}
			catch( org.omg.CORBA.portable.ApplicationException _ax )
			{
				String _id = _ax.getId();
					try
					{
							_ax.getInputStream().close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				throw new RuntimeException("Unexpected exception " + _id );
			}
			finally
			{
				if (_os != null)
				{
					try
					{
						_os.close();
					}
					catch (java.io.IOException e)
					{
					throw new RuntimeException("Unexpected exception " + e.toString() );
					}
				}
				this._releaseReply(_is);
			}
		}
		else
		{
			org.omg.CORBA.portable.ServantObject _so = _servant_preinvoke( "getBundleNames", _opsClass );
			if( _so == null )
				throw new org.omg.CORBA.UNKNOWN("local invocations not supported!");
			CORBAAdminServiceOperations _localServant = (CORBAAdminServiceOperations)_so.servant;
			java.lang.String[] _result;
			try
			{
				_result = _localServant.getBundleNames();
			}
			finally
			{
				_servant_postinvoke(_so);
			}
			return _result;
		}

		}

	}

}
