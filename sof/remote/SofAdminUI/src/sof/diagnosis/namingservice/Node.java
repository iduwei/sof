package sof.diagnosis.namingservice;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents the base class for all types of nodes which are
 * displayed in SOF process view.
 * 
 * @author magr74
 *
 */
public class Node {

	/**
	 * The parent of this node.
	 */
	protected Node parentNode;
	
	/**
	 * An array containing the children of this node.
	 */
	protected ArrayList<Node> nodes;
	
	/**
	 * The name of the node.
	 */
	protected String name;
	
	/**
	 * Creates instances of class <code>Node</code>.
	 * 
	 * @param name
	 * 				The name of the node.
	 * @param parent
	 * 				The parent of the node.
	 */
	public Node( String name, Node parent )
	{
		this.name = name;
		this.nodes = new ArrayList<Node>();
		this.parentNode = parent;
	}
	
	/**
	 * Adds a child node to this node.
	 * 
	 * @param node
	 * 				The child node.
	 */
	public void addNode( Node node )
	{
		this.nodes.add( node );
	}
	
	/**
	 * Returns the child nodes of this node.
	 * 
	 * @return
	 * 			A list containing the child nodes.
	 */
	public List<Node> getNodes()
	{
		return this.nodes;
	}
	
	/**
	 * The parent node.
	 * 
	 * @return
	 * 			The parent node.
	 */
	public Node getParentNode()
	{
		return this.parentNode;
	}
	
	/**
	 * Returns the node name.
	 * 
	 * @return
	 * 			The name of the node.
	 */
	public String getName()
	{
		return this.name;
	}
	
	/**
	 * Returns the string representation of the node.
	 * 
	 * @return
	 * 			The string representation of the node.
	 */
	public String toString()
	{
		StringBuffer buffer = new StringBuffer( 100 );
		buffer.append( "ProcessNode:" );
		buffer.append( "name=" );
		buffer.append( this.name );
		buffer.append( ", parent=" );
		buffer.append( this.parentNode );
		return buffer.toString();
	}
	
}
