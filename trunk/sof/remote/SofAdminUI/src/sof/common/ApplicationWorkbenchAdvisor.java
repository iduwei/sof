package sof.common;

import org.eclipse.ui.application.IWorkbenchWindowConfigurer;
import org.eclipse.ui.application.WorkbenchAdvisor;
import org.eclipse.ui.application.WorkbenchWindowAdvisor;


/**
 * This workbench advisor creates the window advisor, and specifies
 * the perspective id for the initial window.
 * 
 * @author magr74
 */
public class ApplicationWorkbenchAdvisor extends WorkbenchAdvisor {
	
	/**
	 * The ID of the initial perspective.
	 */
	private static final String PERSPECTIVE_ID = "sof.diagnosis.perspective";

	/**
	 * Creates instances of type <code>WorkbenchWindowAdvisor</code>.
	 * 
	 * @param configurer
	 * 				The configurer.
	 */
    public WorkbenchWindowAdvisor createWorkbenchWindowAdvisor(IWorkbenchWindowConfigurer configurer) {
        return new ApplicationWorkbenchWindowAdvisor(configurer);
    }

	public String getInitialWindowPerspectiveId() {
		return PERSPECTIVE_ID;
	} 
	
}
