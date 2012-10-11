package sof.diagnosis.ui.command.handler;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.InputDialog;
import org.eclipse.jface.window.Window;
import org.eclipse.swt.widgets.Display;

/**
 * The <code>ConnectionSettingsHandler</code> is responsible for
 * handling connection settings which are made by the user.
 * 
 * @author magr74
 *
 */
public class ConnectionSettingsHandler extends AbstractHandler
{

	/**
	 * Is called when user presses the OK button in connection settings
	 * dialog.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException
	{
		System.out.println( "ConnectionSettingsHandler called." );
		InputDialog dlg = new InputDialog( 
				Display.getCurrent().getActiveShell(),
	            "Connection Settings", "CORBA Naming Service Address:", 
	            "inet:localhost:5000", null);
	        if (dlg.open() == Window.OK) {
	          // User clicked OK; update the label with the input
	          System.out.println( "input:" + dlg.getValue());
	        }
		return null;
	}

}
