package sof.common;

import org.eclipse.jface.action.ICoolBarManager;
import org.eclipse.jface.action.IMenuManager;
import org.eclipse.jface.action.IToolBarManager;
import org.eclipse.jface.action.ToolBarContributionItem;
import org.eclipse.jface.action.ToolBarManager;
import org.eclipse.swt.SWT;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.application.ActionBarAdvisor;
import org.eclipse.ui.application.IActionBarConfigurer;

/**
 * An action bar advisor is responsible for creating, adding, and disposing of the
 * actions added to a workbench window. Each window will be populated with
 * new actions.
 * 
 * @author magr74
 */
public class ApplicationActionBarAdvisor extends ActionBarAdvisor {


	/**
	 * Creates instances of type <code>ApplicationActionBarAdvisor</code>.
	 * 
	 * @param configurer
	 * 				The action bar configurer.
	 */
    public ApplicationActionBarAdvisor(IActionBarConfigurer configurer) {
        super(configurer);
    }

    /**
     * Creates actions.
     * 
     * @param window	
     * 				The workbench window.
     */
    protected void makeActions(final IWorkbenchWindow window) {

    }

    /**
     * Fills the menu bar.
     * 
     * @param menuBar	
     * 				The menu manager.
     */
    protected void fillMenuBar(IMenuManager menuBar) {
 
    }

    /**
     * Fills the cool bar.
     * 
     * @param coolBar
     * 			The cool bar manager.
     */
    protected void fillCoolBar(ICoolBarManager coolBar) {
        IToolBarManager toolbar = new ToolBarManager(SWT.FLAT | SWT.RIGHT);

        coolBar.add(new ToolBarContributionItem(toolbar, "main"));  
    }


}
