package sof.diagnosis.namingservice.ui;

import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.SelectionChangedEvent;
import org.eclipse.jface.viewers.TreeViewer;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.ViewPart;
import org.osgi.framework.BundleContext;
import org.osgi.framework.ServiceReference;
import org.osgi.util.tracker.ServiceTracker;
import org.osgi.util.tracker.ServiceTrackerCustomizer;

import sof.common.Const;
import sof.common.ShapesPlugin;
import sof.diagnosis.CORBAOrbActivator;
import sof.diagnosis.namingservice.ProcessNode;
import sof.diagnosis.services.BundleViewService;
import sof.services.admin.remote.corba.generated.CORBAAdminService;


/**
 * Represents the process view which lists all available SOF processes
 * in a tree view.
 * 
 * @author magr74
 *
 */
public class SofProcessView extends ViewPart implements SelectionListener, ServiceTrackerCustomizer, ISelectionChangedListener
{

	/**
	 * The identifier of the SOF process view.
	 */
	public final static String ID = "sof.diagnosis.namingservice.ui.SofProcessView";
	
	/**
	 * The logger instance.
	 */
	private Logger logger;
	
	/**
	 * Tree view component which displays the SOF processes.
	 */
	private TreeViewer treeViewer;
	
	/**
	 * Activates the CORBA infrastructure for communicating with the SOF processes.
	 */
	private CORBAOrbActivator orbActivator;
	
	/**
	 * The bundle context.
	 */
	private BundleContext bundleContext;
	
	/**
	 * Communication interface between process and bundle data view.
	 */
	private BundleViewService bundleViewService;
	
	/**
	 * The currently selected process node.
	 */
	private ProcessNode currentProcessNode;
	
	/**
	 * Creates instances of class </code>SofProcessView</code>.
	 */
	public SofProcessView()
	{
		this.logger = Logger.getLogger( Const.LOG_PROCESS_VIEW );
		this.logger.log( Level.FINER, "[SofProcessView#ctor] Called." );
		this.bundleContext = ShapesPlugin.getDefault().getBundle().getBundleContext();
	}
	
	/**
	 * Creates the UI parts of the SOF process view.
	 */
	@Override
	public void createPartControl(Composite parent) {
		this.logger.log( Level.FINER, "[SofProcessView#createPartControl] Called." );
		this.orbActivator = new CORBAOrbActivator();
		this.orbActivator.startCORBA();
				
		this.createLayout( parent );
		this.createUpdateButton( parent );		
		this.createTreeViewer( parent );	
		
		ServiceTracker tracker = new ServiceTracker( this.bundleContext, BundleViewService.class.getName(), this );
		tracker.open();
	}

	/**
	 * Creates the layout of the passed component.
	 * 
	 * @param parent
	 * 				The parent component of the SOF process view.
	 * 				
	 */
	private void createLayout( Composite parent )
	{
		GridLayout layout = new GridLayout();
		layout.numColumns = 1;
		parent.setLayout( layout );
	}
	
	/**
	 * Creates the update button for updating the SOF process view.
	 * 
	 * @param parent
	 * 				The parent of the SOF process view.
	 */
	private void createUpdateButton( Composite parent )
	{
		Button updateButton = new Button( parent, SWT.PUSH );
		updateButton.setText( "Update View" );
		updateButton.addSelectionListener( this );
	}
	
	/**
	 * Creates the tree viewer component which displays the
	 * SOF processes as tree nodes.
	 * 
	 * @param parent
	 */
	private void createTreeViewer( Composite parent )
	{
		treeViewer = new TreeViewer(parent, SWT.PUSH );
		
		GridData gridData = new GridData();
		gridData.horizontalAlignment = GridData.FILL;
		gridData.horizontalSpan = 1;
		gridData.grabExcessHorizontalSpace = true;
		gridData.verticalAlignment = GridData.FILL;
		gridData.grabExcessVerticalSpace = true;
		treeViewer.getControl().setLayoutData(gridData);
				
		treeViewer.setContentProvider(new ProcessProvider());
		treeViewer.setLabelProvider(new ProcessLabelProvider());
		//treeViewer.setInput( this.orbActivator.getNamingServiceAccess().getRootNode() );
		treeViewer.expandAll();		
		treeViewer.addSelectionChangedListener( this );
	}
	

	/**
	 * Is called when a node of the process tree view is selected.
	 * 
	 * @see org.eclipse.jface.viewers.ISelectionChangedListener#selectionChanged(org.eclipse.jface.viewers.SelectionChangedEvent)
	 */
	public void selectionChanged(SelectionChangedEvent event)
	{
		this.logger.log( Level.FINER, "[SofProcessView#selectionChanged] Called, event: {0}", event );
		
	       if( event.getSelection().isEmpty() ) {
	    	   this.logger.log( Level.FINER, "[SofProcessView#selectionChanged] Selection is empty, return" );	   		
	           return;
	       }
	       
	       if( event.getSelection() instanceof IStructuredSelection ) 
	       {
	           IStructuredSelection selection = ( IStructuredSelection ) event.getSelection();
	           Object obj = selection.getFirstElement();
	           this.logger.log( Level.FINER, "[SofProcessView#selectionChanged] Selected object: {0}", obj );	 
	           if ( obj instanceof ProcessNode )
	           {
	        	   this.currentProcessNode = ( ProcessNode ) obj; 
	        	   if ( this.bundleViewService != null )
	        	   {
	        		   this.logger.log( Level.FINER, "[SofProcessView#selectionChanged] Forward bundle names to BundleViewService." );	 
	        		   this.bundleViewService.setSelectedProcessNode( this.currentProcessNode );
	        	   }
	        	   else
	        	   {
	        		   this.logger.log( Level.FINER, "[SofProcessView#selectionChanged] BundleViewService is null, do nothing." );	 	        		   
	        	   }
	           }	 
	           else
	           {
	        	   this.currentProcessNode = null;
	           }
	       }		
	}
		
	/**
	 * @see org.eclipse.ui.part.WorkbenchPart#setFocus()
	 */
	@Override
	public void setFocus() {
		// TODO Auto-generated method stub
		
	}

	/**
	 * @see org.eclipse.swt.events.SelectionListener#widgetDefaultSelected(org.eclipse.swt.events.SelectionEvent)
	 */
	public void widgetDefaultSelected(SelectionEvent e)
	{
		// TODO Auto-generated method stub
		
	}

	/**
	 * Is called when 'update' button in SOF process view on the left side
	 * of the workbench is pressed.
	 * 
	 * @param e
	 * 			The selection event.
	 *
	 * @see org.eclipse.swt.events.SelectionListener#widgetSelected(org.eclipse.swt.events.SelectionEvent)
	 */
	public void widgetSelected(SelectionEvent e)
	{
		this.logger.log( Level.FINER, "[SofProcessView#widgetSelected] Called, event: {0}", e );
		treeViewer.setInput( this.orbActivator.getNamingServiceAccess().update() );
	}

	/**
	 * @see org.osgi.util.tracker.ServiceTrackerCustomizer#addingService(org.osgi.framework.ServiceReference)
	 */
	public Object addingService(ServiceReference reference)
	{
		this.logger.log( Level.FINER, "[SofProcessView#addingService] Called, reference: {0}", reference );
		Object obj = this.bundleContext.getService( reference );
		if ( obj instanceof BundleViewService )			
		{
			this.logger.log( Level.FINER, "[SofProcessView#addingService] BundleViewService instance found." );
			
			this.bundleViewService = ( BundleViewService ) obj;
			if ( this.currentProcessNode != null )
			{
				this.logger.log( Level.FINER, "[SofProcessView#addingService] Set process node: {0}", 
						this.currentProcessNode );
				this.bundleViewService.setSelectedProcessNode( this.currentProcessNode );
			}
			return this.bundleViewService;
		}
		return null;
	}

	/**
	 * @see org.osgi.util.tracker.ServiceTrackerCustomizer#modifiedService(org.osgi.framework.ServiceReference, java.lang.Object)
	 */
	public void modifiedService(ServiceReference reference, Object service)
	{
		this.logger.log( Level.FINER, "[SofProcessView#modifiedService] Called, reference: {0}", reference );
		
	}

	/**
	 * @see org.osgi.util.tracker.ServiceTrackerCustomizer#removedService(org.osgi.framework.ServiceReference, java.lang.Object)
	 */
	public void removedService(ServiceReference reference, Object service) 
	{
		this.logger.log( Level.FINER, "[SofProcessView#removedService] Called, reference: {0}", reference );
		Object obj = this.bundleContext.getService( reference );
		if ( obj instanceof BundleViewService )			
		{
			this.logger.log( Level.FINER, "[SofProcessView#addingService] BundleViewService instance found." );
			
			this.bundleViewService = null;
		}				
	}
}
