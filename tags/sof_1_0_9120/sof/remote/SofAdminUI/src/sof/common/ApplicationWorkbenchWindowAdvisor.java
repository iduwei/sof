package sof.common;

import org.eclipse.swt.graphics.Point;
import org.eclipse.ui.application.ActionBarAdvisor;
import org.eclipse.ui.application.IActionBarConfigurer;
import org.eclipse.ui.application.IWorkbenchWindowConfigurer;
import org.eclipse.ui.application.WorkbenchWindowAdvisor;

/**
 * The application workbench advisor is responsible for configuring a workbench
 * window.
 * 
 * @author magr74
 *
 */
public class ApplicationWorkbenchWindowAdvisor extends WorkbenchWindowAdvisor {

	/**
	 * Creates instances of class <code>ApplicationWorkbenchAdvisor</code> types.
	 * 
	 * @param configurer
	 * 				The workbench window configurer.
	 */
    public ApplicationWorkbenchWindowAdvisor(IWorkbenchWindowConfigurer configurer) {
        super(configurer);
    }

    /**
     * Creates the action bar advisor instance.
     * 
     * @param configurer
     * 				The action bar configurer.
     */
    public ActionBarAdvisor createActionBarAdvisor(IActionBarConfigurer configurer) {
        return new ApplicationActionBarAdvisor(configurer);
    }
    
    /**
     * Initializes the workbench window before it is opened.
     */
    public void preWindowOpen() {
        IWorkbenchWindowConfigurer configurer = getWindowConfigurer();
        configurer.setInitialSize(new Point(1000, 800));
        configurer.setShowCoolBar(true);
        configurer.setShowStatusLine(true);        
        configurer.setShowMenuBar( true );
        configurer.setShowPerspectiveBar(true);
    }
    
}
