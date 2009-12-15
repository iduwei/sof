package sof.common;

import java.util.Properties;

import sof.services.admin.remote.corba.generated.CORBAAdminServiceProps;

/**
 * The <code>DataConverter</code> class defines only static helper methods and
 * converts CORBA specific types to Java types and vice versa.
 * 
 * @author magr74
 *
 */
public abstract class DataConverter
{
	/**
	 * Converts instances of type <code>CORBAAdminServiceProps</code> to 
	 * <code>Properties</code> objects.
	 * 
	 * @param corbaProps
	 * 				The CORBA properties object.
	 * @return
	 * 				The Java properties object.
	 */
	public static Properties convert( CORBAAdminServiceProps corbaProps )
	{
		Properties props = new Properties();
		for ( int i=0; i<corbaProps.keys.length; i++ )
		{
			props.put( corbaProps.keys[i], corbaProps.values[i] );
		}
		return props;
	}
}
