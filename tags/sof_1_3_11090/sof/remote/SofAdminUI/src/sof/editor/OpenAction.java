/*******************************************************************************
 * Copyright (c) 2005 Chris Aniszczyk
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Chris Aniszczyk - initial API and implementation
 *    IBM Corporation
 *******************************************************************************/

package sof.editor;

import org.eclipse.core.runtime.Path;
import org.eclipse.jface.action.Action;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.PartInitException;

public class OpenAction extends Action {
	
	IWorkbenchWindow workbenchWindow;
	
	public OpenAction(IWorkbenchWindow window) {
		setId("Open a Shapes Diagram");
		setText("Open");
		workbenchWindow = window;
	}
	
	public void run() {
		String path = openFileDialog();
		if (path != null) {
			IEditorInput input = new ShapesEditorInput(new Path(path));
			
			try {
				workbenchWindow.getActivePage().openEditor(
						input, 
						ShapesEditor.ID, 
						true);
			} catch (PartInitException e) {
				e.printStackTrace();
			}
		}
		
	}
	
	private String openFileDialog() {
		FileDialog dialog = new FileDialog(workbenchWindow.getShell(), SWT.OPEN);
		dialog.setText("New Shapes Diagram");
		dialog.setFilterExtensions(new String[] { "*.shapes" });
		return dialog.open();
	}
}
