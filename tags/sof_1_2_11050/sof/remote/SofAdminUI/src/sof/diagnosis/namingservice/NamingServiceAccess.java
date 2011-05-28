package sof.diagnosis.namingservice;

import java.util.logging.Level;
import java.util.logging.Logger;

import org.omg.CORBA.ORB;
import org.omg.CORBA.ORBPackage.InvalidName;
import org.omg.CosNaming.Binding;
import org.omg.CosNaming.BindingIteratorHolder;
import org.omg.CosNaming.BindingListHolder;
import org.omg.CosNaming.BindingType;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextHelper;

import sof.common.Const;
import sof.services.admin.remote.corba.generated.CORBAAdminService;
import sof.services.admin.remote.corba.generated.CORBAAdminServiceHelper;

/**
 * The <code>NamingServiceAccess</code> class reads all data from the
 * CORBA naming service process and builds a tree of all SOF process. Each
 * SOF process represents a tree node.
 * 
 * @author magr74
 *
 */
public class NamingServiceAccess {

	/**
	 * The CORBA ORB instance.
	 */
	private ORB orb;
	
	/**
	 * The root node of the SOF process tree view.
	 */
	private NameNode rootNameNode;
	
	/**
	 * The logger instance.
	 */
	private Logger logger;
	
	/**
	 * Creates instances of class <code>NamingServiceAccess</code>.
	 * 
	 * @param orb
	 * 				The CORBA ORB instance.
	 */
	public NamingServiceAccess( ORB orb )
	{
		this.logger = Logger.getLogger( Const.LOG_CORBA );
		this.logger.log( Level.FINER, "[NamingServiceAccess#ctor] Called." );		
        this.orb = orb;		
	}
	
	/**
	 * Updates the SOF process tree.
	 * 
	 * @return
	 * 			Returns the root node of the SOF process tree view.
	 */
	public NameNode update()
	{
		org.omg.CORBA.Object o = null;
		try
		{
			o = this.orb.resolve_initial_references("NameService");
		} catch (InvalidName e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        NamingContext nc = NamingContextHelper.narrow( o );
        this.rootNameNode = new NameNode( "Root", nc, null );
        
		this.logger.log( Level.FINER, "[NamingServiceAccess#update] Called." );
		this.update( this.rootNameNode );
		return this.rootNameNode;
	}
	
	/**
	 * Helper method for building the tree nodes.
	 * 
	 * @param node
	 * 				The tree node which contains further tree nodes.
	 */
	private void update( Node node )
    {
		this.logger.log( Level.FINER, "[NamingServiceAccess#update] Called, node: {0}", node );
        try
        {         
        	NameNode nameNode = ( NameNode ) node;
            BindingListHolder blsoh = new BindingListHolder();
            BindingIteratorHolder bioh = new BindingIteratorHolder();
            
            nameNode.getNamingContext().list( 100, blsoh, bioh);
            Binding[] bindings = blsoh.value;            
                
            for( int i = 0; i < bindings.length; i++ )
            {               
                if( bindings[i].binding_type == BindingType.ncontext )
                {
                	this.logger.log( Level.FINER, "[NamingServiceAccess#update] Context found: {0}",  bindings[i].binding_name[0].id );
                    NamingContext ctxt = NamingContextHelper.narrow(
                    		nameNode.getNamingContext().resolve(bindings[i].binding_name) );
                    
                    NameNode newNode = new NameNode( bindings[i].binding_name[0].id, ctxt, nameNode );
                    nameNode.addNode( newNode );
                    update( newNode );
                }
                else
                {             
                	try 
                	{
                		this.logger.log( Level.FINER, "[NamingServiceAccess#update] Object found: {0}",  bindings[i].binding_name[0].id );             
                		if ( nameNode.getNamingContext().resolve( bindings[i].binding_name )._is_a( "IDL:sof/services/admin/remote/corba/generated/CORBAAdminService:1.0" ) )
                		{
                			this.logger.log( Level.FINER, "[NamingServiceAccess#update] CORBAAdminService found." );    
                			CORBAAdminService adminService = CORBAAdminServiceHelper.narrow( nameNode.getNamingContext().resolve( bindings[i].binding_name ) );
                    		nameNode.addNode( new ProcessNode( bindings[i].binding_name[0].id, adminService, nameNode ) );       
                		}
                		else
                		{
                			this.logger.log( Level.FINER, "[NamingServiceAccess#update] Ignore CORBA object (not a type of CORBAAdminService)." );    
                		}
                		         		
                	}
                	catch ( Exception e )
                	{
                		this.logger.log( Level.SEVERE, "[NamingServiceAccess#update] Narrow error!", e );
                	}
                }
            }
        }
        catch( Exception e )
        {
        	this.logger.log( Level.SEVERE, "[NamingServiceAccess#update] Error occured!", e );
        }
    }
}
