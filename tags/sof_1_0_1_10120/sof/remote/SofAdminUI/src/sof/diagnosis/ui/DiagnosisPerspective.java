package sof.diagnosis.ui;

import org.eclipse.ui.IFolderLayout;
import org.eclipse.ui.IPageLayout;
import org.eclipse.ui.IPerspectiveFactory;

import sof.diagnosis.bundledata.ui.BundleDataView;
import sof.diagnosis.namingservice.ui.SofProcessView;

/**
 * The <code>DiagnosisPerspective</code> displays all components which are used
 * for diagnostic.
 * 
 * @author magr74
 *
 */
public class DiagnosisPerspective implements IPerspectiveFactory {

	/**
	 * Creates the initial layout.
	 * 
	 * @param layout
	 * 				The page layout.
	 */
	public void createInitialLayout(IPageLayout layout) {
		
		layout.addActionSet( "sof.diagnosis.actionSet" );

		String editorArea = layout.getEditorArea();
		layout.setEditorAreaVisible(false);
		IFolderLayout navFolder = layout.createFolder("SOF Processes", IPageLayout.LEFT, 0.3f, editorArea);
		navFolder.addView(SofProcessView.ID);
		
		IFolderLayout dataFolder = layout.createFolder("Data", IPageLayout.LEFT, 0.7f, editorArea);
		dataFolder.addView(BundleDataView.ID);
	}
}
