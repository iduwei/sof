package sof.editor;

import org.eclipse.ui.IFolderLayout;
import org.eclipse.ui.IPageLayout;
import org.eclipse.ui.IPerspectiveFactory;



public class Perspective implements IPerspectiveFactory {

	public void createInitialLayout(IPageLayout layout) {
		String editorArea = layout.getEditorArea();
		
		layout.addActionSet( "sof.editor.actionSet" );
		
		layout.setEditorAreaVisible(false);
		IFolderLayout navFolder = layout.createFolder("navigation", IPageLayout.LEFT, 0.5f, editorArea);
		navFolder.addView(IPageLayout.ID_PROP_SHEET);
//        IFolderLayout navFolder = layout.createFolder("navigation", IPageLayout.LEFT, 0.5f, editorArea);
//        navFolder.addView(NavigationView.ID);
//        navFolder.addView(ModelBankView.ID);
//        navFolder.addView(LogChannelView.ID);
//        navFolder.addView(BundleView.ID);
//        navFolder.addView(CallbackView.ID);
//        navFolder.addView(DumpView.ID);
//        //navFolder.addView(ImageView.ID);
//
//		//layout.addStandaloneView(NavigationView.ID,  false, IPageLayout.LEFT, 0.25f, editorArea);
//        IFolderLayout folder = layout.createFolder("messages", IPageLayout.TOP, 0.5f, editorArea);
//        folder.addPlaceholder(View.ID + ":*");
//        folder.addView(View.ID);
//        folder.addView(LogMessagesView.ID);
//        folder.addView(ImageView.ID);
//        folder.addView( FileEditorView.ID );
//
//        layout.getViewLayout(View.ID).setCloseable(false);
//        layout.getViewLayout( FileEditorView.ID ).setCloseable( false );
//        layout.getViewLayout(LogMessagesView.ID).setCloseable(false);
//        layout.getViewLayout(NavigationView.ID).setCloseable(false);
//        layout.getViewLayout(ModelBankView.ID).setCloseable(false);
//        layout.getViewLayout( LogChannelView.ID ).setCloseable( false );
//        layout.getViewLayout( CallbackView.ID ).setCloseable( false );
//        layout.getViewLayout( DumpView.ID ).setCloseable( false );

	}
}
