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

import org.eclipse.jface.viewers.ICellEditorValidator;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;


/**
 * A rectangular shape.
 * @author  
 */
public class RectangularShape extends Shape {
/** A 16x16 pictogram of a rectangular shape. */
private static final Image RECTANGLE_ICON = AbstractUIPlugin
	.imageDescriptorFromPlugin( "sof.admin.ui","resources/icons/rectangle16.gif" ).createImage();

private static final long serialVersionUID = 1;

private static final String BUNDLE_ACTIVATOR_NAME = "bundleActivatorName";

private String bundleActivatorName;

public RectangularShape()
{
    TextPropertyDescriptor propDesc = new TextPropertyDescriptor(BUNDLE_ACTIVATOR_NAME, "bundleActivatorName"); 
    
    this.propertyDescriptorList.add( propDesc );
    
   
    propDesc.setValidator(new ICellEditorValidator() {
        public String isValid(Object value) {
            return ( String ) value;
        }
    });
}

private String getBundleActivatorName()
{
    return this.bundleActivatorName;
}

private void setBundleActivatorName( String name )
{
    this.bundleActivatorName = name;
    firePropertyChange(BUNDLE_ACTIVATOR_NAME, null, this.bundleActivatorName );
}

public Image getIcon() {
	return RECTANGLE_ICON;
}

public String toString() {
	return "Rectangle " + hashCode();
}

public Object getPropertyValue(Object propertyId) {
    if (BUNDLE_ACTIVATOR_NAME.equals(propertyId)) {
        return this.getBundleActivatorName();
    }
    return super.getPropertyValue(propertyId);
}

public void setPropertyValue(Object propertyId, Object value) {
    if (BUNDLE_ACTIVATOR_NAME.equals(propertyId)) {
        this.setBundleActivatorName( ( String ) value );        
    } else {
        super.setPropertyValue(propertyId, value);
    }
}

}
