package sof.common;

import org.eclipse.core.runtime.Platform;
import org.eclipse.equinox.app.IApplication;
import org.eclipse.equinox.app.IApplicationContext;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.PlatformUI;

/**
 * This class controls all aspects of the application's execution
 * 
 * @author magr74
 */
public class Application implements IApplication {


	/**
	 * Starts the application.
	 * 
	 * @param context
	 * 				The application context.
	 */
	public Object start(IApplicationContext context) throws Exception
	{
		
		String[] args = ( String[] ) Platform.getApplicationArgs();
		for ( String arg : args )
		{
			System.out.println( "Program argument: " + arg );
		}
		Display display = PlatformUI.createDisplay();
		try {
			int returnCode = PlatformUI.createAndRunWorkbench(display, new ApplicationWorkbenchAdvisor());
			if (returnCode == PlatformUI.RETURN_RESTART) {
				return IApplication.EXIT_RESTART;
			}
			return IApplication.EXIT_OK;
		} finally {
			display.dispose();
		}
	}

	/**
	 * Stops the application's execution.
	 */
	public void stop()
	{
	}
}
