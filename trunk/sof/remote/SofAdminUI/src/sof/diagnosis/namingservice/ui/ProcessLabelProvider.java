package sof.diagnosis.namingservice.ui;

import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.plugin.AbstractUIPlugin;

import sof.common.Const;
import sof.diagnosis.namingservice.NameNode;
import sof.diagnosis.namingservice.Node;
import sof.diagnosis.namingservice.ProcessNode;

/**
 * The <code>ProcessLabelProvider</code> class defines the look of the
 * tree nodes of the process view.
 * 
 * @author magr74
 *
 */
public class ProcessLabelProvider extends LabelProvider 
{
	
	/**
	 * The logger instance.
	 */
	private Logger logger;
	
	/**
	 * Image for a folder node of the process view.
	 */
	private static final Image FOLDER_ICON = AbstractUIPlugin
		.imageDescriptorFromPlugin( "sof.admin.ui",
			"resources/icons/folder.gif" ).createImage();
	
	/**
	 * Image for a process node of the process view.
	 */
	private static final Image PROCESS_ICON = AbstractUIPlugin
		.imageDescriptorFromPlugin( "sof.admin.ui",
			"resources/icons/process.gif" ).createImage();

	/**
	 * Creates instances of class <code>ProcessLabelProvider</code>.
	 */
	public ProcessLabelProvider()	
	{
		this.logger = Logger.getLogger( Const.LOG_PROCESS_VIEW );
		this.logger.log( Level.FINER, "[ProcessLabelProvider#ctor] Called." );
	}
	
	/**
	 * Returns an image depending on the node type.
	 */
	public Image getImage(Object element) 
	{
	   if (element instanceof ProcessNode) 
	   {
		   return PROCESS_ICON;	   
	   } 
	   else if ( element instanceof NameNode )
	   {
		   return FOLDER_ICON;
		   
	   }
	   else 
	   {
	       return null;
	   }	   	  
	}

	/**
	 * Returns the text of a node element.
	 */
	public String getText(Object element) 
	{
		return ( ( Node ) element ).getName();
	}
			
}
