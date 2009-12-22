package sof.diagnosis.namingservice;

import sof.diagnosis.namingservice.Node;
import sof.services.admin.remote.corba.generated.CORBAAdminService;

/**
 * The <code>ProcessNode</code> class extends the <code>Node</code> class
 * and represents a SOF process in the process view.
 * 
 * @author magr74
 *
 */
public class ProcessNode extends Node
{
	/**
	 * The CORBA interface of a SOF process which provides bundle info data.
	 */
	protected CORBAAdminService adminService;
	
	/**
	 * Creates instances of class <code>ProcessNode</code>.
	 * 
	 * @param name
	 * 				The name of the process node.
	 * 
	 * @param service
	 * 				The CORBA administration interface for a SOF process.
	 * 
	 * @param parentNode
	 * 				The parent node.
	 */
	public ProcessNode( String name, CORBAAdminService service, Node parentNode )
	{
		super( name, parentNode );
		this.adminService = service;
	}
	
	/**
	 * Returns the CORBA administration object.
	 * 	
	 * @return
	 * 			The CORBA administration object.
	 */
	public CORBAAdminService getCORBAObject()
	{
		return this.adminService;
	}
	
	/**
	 * Returns the string representation of the process node.
	 * 
	 * @return
	 * 			The string representation of the process node.
	 */
	public String toString()
	{
		StringBuffer buffer = new StringBuffer( 100 );
		buffer.append( "ProcessNode:" );
		buffer.append( "name=" );
		buffer.append( this.name );
		buffer.append( ", adminServiceObj=" );
		buffer.append( this.adminService );
		buffer.append( ", parent=" );
		buffer.append( this.parentNode );
		return buffer.toString();
	}
}

