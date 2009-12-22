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
package sof.editor.shapes.model;

import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.plugin.AbstractUIPlugin;

/**
 * An elliptical shape.
 * @author  
 */
public class EllipticalShape extends Shape {

/** A 16x16 pictogram of an elliptical shape. */
private static final Image ELLIPSE_ICON = AbstractUIPlugin
	.imageDescriptorFromPlugin( "sof.admin.ui","resources/icons/ellipse16.gif" ).createImage();

private static final long serialVersionUID = 1;

public Image getIcon() {
	return ELLIPSE_ICON;
}

public String toString() {
	return "Ellipse " + hashCode();
}
}
