package sof.diagnosis.namingservice;

import org.omg.CosNaming.NamingContext;

/**
 * Represents a folder node element of the SOF process view.
 * 
 * @author magr74
 *
 */
public class NameNode extends Node 
{
	/**
	 * The CORBA naming context.
	 */
	private NamingContext ctxt;
	
	/**
	 * Creates instances of class <code>NameNode</code>.
	 * 
	 * @param name
	 * 				The name of the node.
	 * 
	 * @param ctxt
	 * 				The CORBA naming context.
	 * 
	 * @param parentNode
	 * 				The parent of this node.
	 */
	public NameNode( String name, NamingContext ctxt, Node parentNode )
	{
		super( name, parentNode );
		this.ctxt = ctxt;
	}
	
	/**
	 * Returns the naming context object.
	 * 
	 * @return
	 * 			The naming context object.
	 */
	public NamingContext getNamingContext()
	{
		return this.ctxt;
	}
	
	
}
