package sof.diagnosis.bundledata.ui;

import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.IStructuredContentProvider;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.ListViewer;
import org.eclipse.jface.viewers.SelectionChangedEvent;
import org.eclipse.jface.viewers.Viewer;
import org.eclipse.jface.viewers.ViewerSorter;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;

import sof.common.Const;

/**
 * The <code>BundleList</code> class represents the widget for
 * displaying the bundle names in a list.
 * 
 * @author magr74
 *
 */
public class BundleList 
{
	/**
	 * The logger instance.
	 */
	private Logger logger;
	
	/**
	 * The JFace list viewer widget.
	 */
	private ListViewer listViewer;

	/**
	 * Creates instances of class <code>BundleList</code>.
	 * 
	 * @param parent
	 * 			The parent component the bundle list belongs to.
	 */
	public BundleList( Composite parent )
	{
		this.logger = Logger.getLogger( Const.LOG_BUNDLE_VIEW );
		this.logger.log( Level.FINER, "[BundleList#ctor] Called." );
		this.listViewer = new ListViewer( parent, SWT.BORDER | SWT.SINGLE | SWT.V_SCROLL );
		this.listViewer.setContentProvider( new ContentProvider( this.logger ) );
		this.listViewer.setSorter( new BundleListSorter( this.logger ) );			
	}
	
	/** 
	 * Sets the content of the bundle list.
	 * 
	 * @param bundleNameSeq
	 * 				Encapsulates an array of bundle names.
	 */
	void setContent( String[] bundleNameSeq )
	{
		for ( String element : bundleNameSeq )
		{
			this.logger.log( Level.FINER, "[ContentProvider#setContent] Called, inputElement: {0}", element );
		}
		
		this.listViewer.setInput( bundleNameSeq );
	}
	
	/**
	 * Returns the list viewer widget.
	 * 
	 * @return
	 * 			The list viewer instance.
	 */
	ListViewer getWidget()
	{
		return this.listViewer;
	}
	
	
	/**
	 * Helper class for providing the content of the bunde list.
	 * 
	 * @author magr74
	 *
	 */
	private static class ContentProvider implements IStructuredContentProvider
	{
		/**
		 * The logger instance.
		 */
		private Logger logger;
		
		/**
		 * Creates instances of class <code>ContentProvider</code>.
		 * 
		 * @param logger
		 * 			The logger instance.
		 */
		public ContentProvider( Logger logger )
		{
			this.logger = logger;
			this.logger.log( Level.FINER, "[ContentProvider#ctor] Called." );
		}
		
		/**
		 * Returns the elements of the bundle list.
		 * 
		 * @param inputElement
		 * 				The input element.
		 * 
		 * @return	
		 * 				An array containing the elements of the list.
		 */
		public Object[] getElements(Object inputElement)
		{
			this.logger.log( Level.FINER, "[ContentProvider#getElements] Called, inputElement: {0}", inputElement );
			return ( ( String[] ) inputElement );
		}

		/**
		 * Disposes the content provider.
		 */
		public void dispose()
		{
			this.logger.log( Level.FINER, "[ContentProvider#dispose] Called." );			
		}

		/**
		 * Is called when content of the list has changed.
		 * 
		 * @param viewer
		 * 				The viewer component.
		 * 
		 * @param oldInput
		 * 				The old content.
		 * 
		 * @param newInput
		 * 				The new data.
		 */
		public void inputChanged(Viewer viewer, Object oldInput, Object newInput)
		{
			this.logger.log( Level.FINER, "[ContentProvider#inputChanged] Called, new: {0}",
					newInput );		
		}		
	}
	
	/**
	 * Sorter class which is responsible for sorting the elements
	 * of the bundle list in alphabetical order.
	 * 
	 * @author magr74
	 *
	 */
	private static class BundleListSorter extends ViewerSorter
	{
		/**
		 * The logger instance.
		 */
		private Logger logger;
		
		/**
		 * Creates instances of class <code>BundleListSorter</code>.
		 * 
		 * @param logger
		 * 				The logger instance.
		 */
		public BundleListSorter( Logger logger )
		{
			this.logger = logger;
			this.logger.log( Level.FINER, "[BundleListSorter#ctor] Called." );
		}
		
		/**
		 * Compares elements of the bundle list.
		 * 
		 * @param viewer
		 * 				The viewer component.
		 * 
		 * @param e1
		 * 				First element of comparison.
		 * 
		 * @param e2
		 * 				Second element of comparison.
		 */
		public int compare( Viewer viewer, Object e1, Object e2 ) 
		{
			Object[] params = new Object[] { e1, e2 };
			this.logger.log( Level.FINER, "[BundleListSorter#compare] Called, obj1: {0}, obj2: {1}",
					params );
	        return ( ( String ) e1 ).compareToIgnoreCase( ( ( String )e2 ) );
	      }
	}
}
