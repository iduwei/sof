package sof.diagnosis;

import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.omg.CORBA.ORB;

import sof.common.Const;
import sof.diagnosis.namingservice.NamingServiceAccess;

/**
 * The <code>CORBAOrbActivator</code> class is responsible for starting and 
 * stopping the CORBA infrastructure.
 * 
 * @author magr74
 *
 */
public class CORBAOrbActivator 
{

	/**
	 * The logger instance.
	 */
	private Logger log;
	
	/**
	 * The thread which runs the CORBA ORB.
	 */
	private Thread thread;	
	
	/**
	 * The runnable object.
	 */
	private ORBRunner runner;
	
	/**
	 * Only for testing the CORBA ORB.
	 * 
	 * @param args
	 * 				Command line arguments.
	 */
	public static void main( String args[] )
	{		
		CORBAOrbActivator act = new CORBAOrbActivator();
		act.startCORBA();
		act.getNamingServiceAccess().update();	
	}
	
	/**
	 * Creates instances of class <code>CORBAOrbActivator</code>.
	 */
	public CORBAOrbActivator()
	{		
		log = Logger.getLogger( Const.LOG_CORBA );
		this.log.log( Level.FINER, "[CORBAOrbActivator#ctor] Called." );
	}
	
	/**
	 * Starts the CORBA infrastructure.
	 */
	public void startCORBA()
	{
		this.log.log( Level.FINER, "[CORBAOrbActivator#startCORBA] Called." );
		
		this.runner = new ORBRunner( this.log );
				
		this.thread = new Thread( this.runner );
		this.thread.start();
		this.runner.waitForCompletion();
	}
	
	/**
	 * Stops the CORBA ORB.
	 */
	public void stopCORBA()
	{
		this.log.log( Level.FINER, "[CORBAOrbActivator#stopCORBA] Called." );
		this.runner.stop();
	}
	
	/**
	 * Returns the naming service access component.
	 * 
	 * @return
	 * 			Component for accessing the CORBA naming service.
	 */
	public NamingServiceAccess getNamingServiceAccess()
	{
		return this.runner.getNamingServiceAccess();
	}
		
	/**
	 * Implements the <code>Runnable</code> interface and runs
	 * the CORBA ORB.
	 *  
	 * @author magr74
	 *
	 */
	private static final class ORBRunner implements Runnable
	{
		/**
		 * The CORBA ORB.
		 */
		private ORB orb;
		
		/**
		 * The logger instance.
		 */
		private Logger log;
		
		/**
		 * Indicates that the CORBA ORB is started.
		 */
		private boolean isStarted = false;
		
		/**
		 * The naming service access object.
		 */
		private NamingServiceAccess namingServiceAccess;
		
		/**
		 * Creates instances of class <code>ORBRunner</code>.
		 * 
		 * @param log
		 * 				The logger instance.
		 */
		public ORBRunner( Logger log )
		{
			this.log = log;
			this.log.log( Level.FINER, "[ORBRunner#ctor] Called." );
		}
		
		/**
		 * Runs the ORB.
		 */
		public void run()
		{
			this.log.log( Level.FINER, "[ORBRunner#run] Called." );
			// -ORBInitRef.NameService=corbaloc::localhost:5000/NameService
	        // args:-ORBInitRef.NameService=corbaloc::localhost:5000/NameService
	        Properties props = new Properties();
	        props.put( "org.omg.CORBA.ORBClass", "org.jacorb.orb.ORB" );
	        props.put( "org.omg.CORBA.ORBSingletonClass","org.jacorb.orb.ORBSingleton" );
	        String[] args = new String[] {"-ORBInitRef.NameService=corbaloc::localhost:5000/NameService"};
	        try 
	        {
		        this.orb = ORB.init(args, props);	        
		        
		        this.namingServiceAccess = new NamingServiceAccess( this.orb );
		        this.log.log( Level.FINER, "[ORBRunner#run] Running ORB." );
		        this.setStarted( true );
		        this.orb.run();		        
	        }
	        catch( Exception e )
	        {
	        	e.printStackTrace();
	        	this.stop();
	        }
	        this.log.log( Level.FINER, "[ORBRunner#run] Left." );
		}
		
		/**
		 * Returns the naming service access component.
		 * 
		 * @return
		 * 			Component for accessing the CORBA naming service.
		 */
		private NamingServiceAccess getNamingServiceAccess()
		{
			return this.namingServiceAccess;
		}
		
		/**
		 * Sets the information that the CORBA ORB is started.
		 * 
		 * @param flag
		 * 			True, if the ORB is started otherwise false.
		 */
		private synchronized void setStarted( boolean flag )
		{
			this.log.log( Level.FINER, "[ORBRunner#setStarted] Called, flag: {0}", flag );
			this.isStarted = flag;
			notify();
		}
		
		/**
		 * Returns if the CORBA ORB is started.
		 * 
		 * @return
		 * 			True if the CORBA infrastructure is started, otherwise false.
		 */
		private synchronized boolean isStarted()
		{
			this.log.log( Level.FINER, "[ORBRunner#isStarted] Called, flag: {0}", this.isStarted );
			return this.isStarted;
		}
		
		/**
		 * Waits for completion of CORBA ORB startup.
		 */
		private synchronized void waitForCompletion()
		{
			this.log.log( Level.FINER, "[ORBRunner#waitForCompletion] Called." );
			while( !this.isStarted() )
			{
				try
				{
					this.log.log( Level.FINER, "[ORBRunner#waitForCompletion] Wait..." );
					wait();
				}
				catch( InterruptedException e )
				{
					e.printStackTrace();
				}
			}
			this.log.log( Level.FINER, "[ORBRunner#waitForCompletion] Left." );
		}
		
		/**
		 * Stops the CORBA ORB.
		 */
		public void stop()
		{
			this.log.log( Level.FINER, "[ORBRunner#stop] Called." );
			if ( this.orb != null )
			{
				this.orb.destroy();
			}
			this.setStarted( false );
		}
		
	}
	
}
