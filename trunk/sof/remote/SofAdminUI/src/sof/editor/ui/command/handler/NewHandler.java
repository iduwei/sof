package sof.editor.ui.command.handler;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.runtime.Path;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.PartInitException;

import sof.common.ShapesPlugin;
import sof.editor.ShapesEditor;
import sof.editor.ShapesEditorInput;

public class NewHandler extends AbstractHandler
{

	public Object execute(ExecutionEvent event) throws ExecutionException
	{
		String path = openFileDialog();
		if (path != null) {
			IEditorInput input = new ShapesEditorInput(new Path(path));
			
			try {
				ShapesPlugin.getDefault().getWorkbench().getActiveWorkbenchWindow().getActivePage().openEditor(
						input, 
						ShapesEditor.ID, 
						true);
			} catch (PartInitException e) {
				e.printStackTrace();
			}
		}
		return null;
	}
	
	private String openFileDialog() {
		FileDialog dialog = new FileDialog(
				ShapesPlugin.getDefault().getWorkbench().getActiveWorkbenchWindow().getShell(), SWT.OPEN);
		dialog.setText("New Shapes Diagram");
		dialog.setFilterExtensions(new String[] { ".shapes" });
		return dialog.open();
	}
}
