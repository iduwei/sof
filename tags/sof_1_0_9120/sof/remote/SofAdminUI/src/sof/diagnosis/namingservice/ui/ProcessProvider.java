package sof.diagnosis.namingservice.ui;

import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.jface.viewers.ITreeContentProvider;
import org.eclipse.jface.viewers.Viewer;

import sof.common.Const;
import sof.diagnosis.namingservice.Node;

/**
 * The <code>ProcessProvider</code> class implements the 
 * <code>ITreeContentProvider</code> interface and provides the data
 * for the process view.
 * 
 * @author magr74
 *
 */
public class ProcessProvider implements ITreeContentProvider 
{

	/**
	 * The logger instance.
	 */
	private Logger logger;
	
	/**
	 * Creates instances of class <code>ProcessProvider</code>.
	 */
	public ProcessProvider()
	{
		this.logger = Logger.getLogger( Const.LOG_PROCESS_VIEW );
		this.logger.log( Level.FINER, "[ProcessProvider#ctor] Called." );
	}
		
	/**
	 * Returns the children of the passed parent element.
	 * 
	 * @param parentElement
	 * 				The parent element.
	 * 
	 * @return	
	 * 				An array containing the children of the parent element.
	 */
	public Object[] getChildren(Object parentElement) {
		Node node = ( Node ) parentElement;
		List<Node> nodes = node.getNodes();
		if ( nodes.size() > 0 ) 
		{
			return nodes.toArray( new Node[nodes.size()] );
		}
		else
		{
			return null;
		}
	}

	/**
	 * Returns the parent of a given element.
	 * 
	 * @param element	
	 * 				An element of the process view tree.
	 * 
	 * @return	
	 * 				The parent of the given object.	 
	 */
	public Object getParent(Object element) {
		Node node = ( Node ) element;
		return node.getParentNode();
	}

	/**
	 * Returns true if the given element has children.
	 * 
	 * @param element
	 * 				An element of the process view tree.
	 * 
	 * @return		
	 * 				True if the give element has children, otherwise
	 * 				false.
	 */
	public boolean hasChildren(Object element) {
		Node node = ( Node ) element;
		if ( node.getNodes().size() > 0 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @see #getChildren(Object)
	 */
	public Object[] getElements(Object inputElement) {
		return this.getChildren( inputElement );
	}

	/**
	 * Disposes the content provider.
	 */
	public void dispose() {
			
	}

	/**
	 * Notifies the content provider that input has changed.
	 */
	public void inputChanged(Viewer viewer, Object oldInput, Object newInput) {
		
	}

}
