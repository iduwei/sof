/*******************************************************************************
 * Copyright (c) 2004, 2005   and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *      - initial API and implementation
 *******************************************************************************/
package sof.editor.shapes.parts;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPartFactory;

import sof.editor.shapes.model.Connection;
import sof.editor.shapes.model.Shape;
import sof.editor.shapes.model.ShapesDiagram;

/**
 * Factory that maps model elements to edit parts.
 * @author  
 */
public class ShapesEditPartFactory implements EditPartFactory {

/*
 * (non-Javadoc)
 * @see org.eclipse.gef.EditPartFactory#createEditPart(org.eclipse.gef.EditPart, java.lang.Object)
 */
public EditPart createEditPart(EditPart context, Object modelElement) {
	// get EditPart for model element
	EditPart part = getPartForElement(modelElement);
	// store model element in EditPart
	part.setModel(modelElement);
	return part;
}

/**
 * Maps an object to an EditPart. 
 * @throws RuntimeException if no match was found (programming error)
 */
private EditPart getPartForElement(Object modelElement) {
	if (modelElement instanceof ShapesDiagram) {
		return new DiagramEditPart();
	}
	if (modelElement instanceof Shape) {
		return new ShapeEditPart();
	}
	if (modelElement instanceof Connection) {
		return new ConnectionEditPart();
	}
	throw new RuntimeException(
			"Can't create part for model element: "
			+ ((modelElement != null) ? modelElement.getClass().getName() : "null"));
}

}