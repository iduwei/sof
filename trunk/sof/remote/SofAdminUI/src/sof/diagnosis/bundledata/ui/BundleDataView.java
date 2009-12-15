package sof.diagnosis.bundledata.ui;

import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.SelectionChangedEvent;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.ui.part.ViewPart;
import org.osgi.framework.BundleContext;

import sof.common.Const;
import sof.common.DataConverter;
import sof.common.ShapesPlugin;
import sof.diagnosis.namingservice.ProcessNode;
import sof.diagnosis.services.BundleViewService;
import sof.services.admin.remote.corba.generated.CORBAAdminServiceInfo;
import sof.services.admin.remote.corba.generated.CORBAAdminServiceListenerInfo;

/**
 * The <code>BundleDataView</code> class is responsible for displaying the
 * bundle data like the
 * <ul>
 * 	<li>The names of all running bundles.</li>
 * 	<li>The service listeners of the selected bundle.</li>
 * 	<li>The registered services of the selected bundle.</li>
 * 	<li>The used services of the selected bundle.</li>
 * </ul>
 * 
 * @author magr74
 *
 */
public class BundleDataView extends ViewPart implements BundleViewService, ISelectionChangedListener
{

	/**
	 * The ID of the bundle data view.
	 */
	public final static String ID = "sof.diagnosis.namingservice.ui.DataView";
		
	/**
	 * Indicates the vertical indent of components to other components.
	 */
	private static final int VERTICAL_INDENT_VALUE = 15;
	
	/**
	 * Indicates the horizontal indent of components to other components.
	 */
	private static final int HORIZONTAL_INDENT_VALUE = 15;
	
	/**
	 * The logger instance.
	 */
	private Logger logger;
	
	/**
	 * The bundle context instance.
	 */
	private BundleContext bundleContext;
	
	/**
	 * The UI component which shows a list of all running bundles.
	 */
	private BundleList bundleList;
	
	/**
	 * The current selected process at the <code>SofProcessView</code>.
	 */
	private ProcessNode currentProcess;
	
	/**
	 * UI table which shows the registered services of the selected bundle
	 * in bundle list.
	 */
	private Table registeredServicesTable;
	
	/**
	 * UI table which shows the registered service listeners of the selected bundle
	 * in bundle list.
	 */
	private List registeredListenersList;
	
	/**
	 * UI table which shows the used services of the selected bundle
	 * in bundle list.
	 */
	private Table usedServicesTable;
	
	/**
	 * Creates instances of class <code>BundleDataView</code>.
	 */
	public BundleDataView()
	{
		this.logger = Logger.getLogger( Const.LOG_BUNDLE_VIEW );
		this.logger.log( Level.FINER, "[DataView#ctor] Called." );
		this.bundleContext = ShapesPlugin.getDefault().getBundle().getBundleContext();
	}
	
	/**
	 * Creates the <code>BundleDataView</code> and its components.
	 * 
	 * @param parent
	 * 				The parent component.
	 */
	@Override
	public void createPartControl(Composite parent) {
		this.logger.log( Level.FINER, "[DataView#createPartControl] Called." );
		this.createLayout( parent );
		this.createComponents( parent );
		this.bundleContext.registerService( BundleViewService.class.getName(), this, null );		
	}
	
	/**
	 * Helper method for creating the layout of the UI components.
	 * 
	 * @param parent
	 * 			The parent component.
	 */
	private void createLayout( Composite parent )
	{
		GridLayout layout = new GridLayout();
		layout.numColumns = 2;
		parent.setLayout( layout );
	}
	
	/**
	 * Creates the UI component for the bundle data view.
	 * 
	 * @param parent
	 * 				The parent component.
	 */
	private void createComponents( Composite parent )
	{
		Label bundleNamesLabel = new Label( parent, SWT.NONE );
		bundleNamesLabel.setText( "Bundle Names:" );
		
		Label registeredServicesLabel = new Label( parent, SWT.NONE );
		GridData gridData = new GridData();
		gridData.horizontalIndent = HORIZONTAL_INDENT_VALUE;
		registeredServicesLabel.setText( "Registered Services:" );
		registeredServicesLabel.setLayoutData( gridData );		
		
		this.bundleList = new BundleList( parent );		 
		gridData = new GridData();
		gridData.verticalAlignment = GridData.FILL;
		gridData.verticalSpan = 5;
		gridData.grabExcessVerticalSpace = true;
		bundleList.getWidget().getList().setLayoutData( gridData );	
		bundleList.getWidget().addSelectionChangedListener( this );
		
		this.registeredServicesTable = new Table( parent, SWT.BORDER | SWT.SINGLE | SWT.V_SCROLL | SWT.H_SCROLL );	
		this.registeredServicesTable.setHeaderVisible( true );
		this.registeredServicesTable.setLinesVisible( true );
		String[] titles = { "Service Name", "Properties", "Object ID" };
		for( String title : titles )
		{
			TableColumn column = new TableColumn( this.registeredServicesTable, SWT.NONE );
			column.setText( title );
			column.pack();
		}		
		gridData = new GridData();
		this.fillGridHorizontalVertical( gridData );	
		this.registeredServicesTable.setLayoutData( gridData );		
				
		Label registeredListenerLabel = new Label( parent, SWT.NONE );
		gridData = new GridData();
		gridData.verticalIndent = VERTICAL_INDENT_VALUE;
		gridData.horizontalIndent = HORIZONTAL_INDENT_VALUE;
		registeredListenerLabel.setText( "Registered Listeners:" );
		registeredListenerLabel.setLayoutData( gridData );
		
		this.registeredListenersList = new List( parent, SWT.BORDER | SWT.SINGLE | SWT.V_SCROLL | SWT.H_SCROLL );		 
		gridData = new GridData();
		this.fillGridHorizontalVertical( gridData );		
		this.registeredListenersList.setLayoutData( gridData );		
		
		Label usedServicesLabel = new Label( parent, SWT.NONE );
		gridData = new GridData();
		gridData.verticalIndent = VERTICAL_INDENT_VALUE;
		gridData.horizontalIndent = HORIZONTAL_INDENT_VALUE;
		usedServicesLabel.setText( "Used Services:" );
		usedServicesLabel.setLayoutData( gridData );
		
		this.usedServicesTable = new Table( parent, SWT.BORDER | SWT.SINGLE | SWT.V_SCROLL | SWT.H_SCROLL );	
		this.usedServicesTable.setHeaderVisible( true );
		this.usedServicesTable.setLinesVisible( true );
		for( String title : titles )
		{
			TableColumn column = new TableColumn( this.usedServicesTable, SWT.NONE );
			column.setText( title );
			column.pack();
		}		
		gridData = new GridData();
		this.fillGridHorizontalVertical( gridData );	
		this.usedServicesTable.setLayoutData( gridData );	
	}
	
	/**
	 * Helper method for setting grid data values.
	 * 
	 * @param gridData
	 * 				The grid data for the grid layout.
	 */
	private void fillGridHorizontalVertical( GridData gridData )
	{
		gridData.horizontalAlignment = GridData.FILL;
		gridData.horizontalSpan = 1;
		gridData.grabExcessHorizontalSpace = true;
		gridData.verticalAlignment = GridData.FILL;
		gridData.verticalSpan = 1;
		gridData.grabExcessVerticalSpace= true;
		gridData.horizontalIndent = HORIZONTAL_INDENT_VALUE;
	}
	
	/**
	 * Sets the focus.
	 */
	@Override	
	public void setFocus() {
		this.logger.log( Level.FINER, "[BundleViewServiceImpl#setFocus] Called." );
	}
	
	/**
	 * Sets the process node which is selected in <code>SofProcessView</code>.
	 * 
	 * @param process
	 * 				The selected process.
	 * 
	 * @see sof.diagnosis.services.BundleViewService#setSelectedProcessNode(String[])
	 */
	public void setSelectedProcessNode( ProcessNode process )
	{
		this.logger.log( Level.FINER, "[BundleViewServiceImpl#setBundleNames] Called, process node: {0}",
				process );
		this.currentProcess = process;
		this.bundleList.setContent( this.currentProcess.getCORBAObject().getBundleNames() );
		this.registeredListenersList.removeAll();
		this.usedServicesTable.removeAll();
		this.registeredServicesTable.removeAll();
	}

	/**
	 * Is called when selection in list of bundles has changed. Fills the tables
	 * of services, service listeners and used services with new data of the current
	 * selected bundle.
	 * 
	 * @param event
	 * 			The selection event.
	 */
	public void selectionChanged(SelectionChangedEvent event) 
	{
		this.logger.log( Level.FINER, "[BundleList#selectionChanged] Called, event: {0}", event );
		IStructuredSelection selection = ( IStructuredSelection )event.getSelection();
		String bundleName = ( String ) selection.getFirstElement();		
		this.logger.log( Level.FINER, "[BundleList#selectionChanged] Called: {0}", bundleName );
		this.fillRegisteredServicesTable( this.currentProcess, bundleName );		
		this.fillRegisteredServiceListenersList( this.currentProcess, bundleName );
		this.fillUsedServicesTable( this.currentProcess, bundleName );
	}
	
	/**
	 * Fills the table of registered services with new data.
	 * 
	 * @param process
	 * 				The process which is currently selected.
	 * 
	 * @param bundleName
	 * 				The name of the bundle which is currently selected.
	 */
	private void fillRegisteredServicesTable( ProcessNode process, String bundleName )
	{
		this.logger.log( Level.FINER, "[BundleList#fillRegisteredServicesList] Called, process: {0}", process.getName() );
		this.logger.log( Level.FINER, "[BundleList#fillRegisteredServicesList] Called, bundleName: {0}", bundleName );
		CORBAAdminServiceInfo[] serviceInfo = this.currentProcess.getCORBAObject().getRegisteredServices( bundleName );
		this.registeredServicesTable.removeAll();
		for ( CORBAAdminServiceInfo info: serviceInfo )
		{
			this.logger.log( Level.FINER, "[BundleList#fillRegisteredServicesList] Table entry added." );
			
			TableItem item = new TableItem( this.registeredServicesTable, SWT.NULL );
			item.setText( 0, info.serviceName );
			item.setText( 1, DataConverter.convert( info.properties ).toString() );
			item.setText( 2, info.objID );
			this.registeredServicesTable.getColumn( 2 ).pack();
		}			
		this.resizeTableColumns( this.registeredServicesTable );
	}
	
	/**
	 * Fills the list of registered service listeners.
	 * 
	 * @param process
	 * 				The process which is currently selected.
	 * 
	 * @param bundleName
	 * 				The name of the bundle which is currently selected.
	 */
	private void fillRegisteredServiceListenersList( ProcessNode process, String bundleName )
	{
		this.logger.log( Level.FINER, "[BundleList#fillRegisteredServiceListenersList] Called, process: {0}", process.getName() );
		this.logger.log( Level.FINER, "[BundleList#fillRegisteredServiceListenersList] Called, bundleName: {0}", bundleName );
		CORBAAdminServiceListenerInfo[] serviceListenerInfos = this.currentProcess.getCORBAObject().getRegisteredServiceListeners( bundleName );
		this.registeredListenersList.removeAll();
		for ( CORBAAdminServiceListenerInfo info: serviceListenerInfos )
		{
			this.logger.log( Level.FINER, "[BundleList#fillRegisteredServiceListenersList] Item added: {0}", info.serviceName );
			
			this.registeredListenersList.add( info.serviceName );
		}	
	}
	
	/**
	 * Fills the table of used services.
	 * 
	 * @param process
	 * 				The process which is currently selected.
	 * 
	 * @param bundleName
	 * 				The name of the bundle which is currently selected.
	 */
	private void fillUsedServicesTable( ProcessNode process, String bundleName )
	{
		this.logger.log( Level.FINER, "[BundleList#fillUsedServicesList] Called, process: {0}", process.getName() );
		this.logger.log( Level.FINER, "[BundleList#fillUsedServicesList] Called, bundleName: {0}", bundleName );
		CORBAAdminServiceInfo[] serviceInfo = this.currentProcess.getCORBAObject().getUsedServices( bundleName );
		this.usedServicesTable.removeAll();
		for ( CORBAAdminServiceInfo info: serviceInfo )
		{
			this.logger.log( Level.FINER, "[BundleList#fillUsedServicesList] Table entry added." );
			
			TableItem item = new TableItem( this.usedServicesTable, SWT.NULL );
			item.setText( 0, info.serviceName );
			item.setText( 1, DataConverter.convert( info.properties ).toString() );
			item.setText( 2, info.objID );
		}		
		this.resizeTableColumns( this.usedServicesTable );
	}
	
	/**
	 * Helper method for resizing the table columns.
	 * 
	 * @param table
	 * 			The table instance.
	 */
	private void resizeTableColumns( Table table )
	{
		TableColumn[] cols = table.getColumns();
		for ( TableColumn col : cols )
		{
			col.pack();
		}
	}
}
