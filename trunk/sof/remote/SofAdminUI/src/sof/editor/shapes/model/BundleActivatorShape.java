

package sof.editor.shapes.model;

import org.eclipse.jface.viewers.ICellEditorValidator;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

public class BundleActivatorShape extends Shape
{
    /** A 16x16 pictogram of a rectangular shape. */
    private static final Image RECTANGLE_ICON = AbstractUIPlugin
		.imageDescriptorFromPlugin( "sof.admin.ui","resources/icons/rectangle16.gif" ).createImage();;

    private static final long serialVersionUID = 1;

    public static final String BUNDLE_ACTIVATOR_NAME = "BundleActivator name";

    private String bundleActivatorName = "Foo";

    public BundleActivatorShape()
    {
        TextPropertyDescriptor propDesc = new TextPropertyDescriptor(BUNDLE_ACTIVATOR_NAME, BUNDLE_ACTIVATOR_NAME); 
        
        this.propertyDescriptorList.add( propDesc );
        
       
        propDesc.setValidator(new ICellEditorValidator() {
            public String isValid(Object value) {
                return null;
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
        return "BundleActivatorShape " + hashCode();
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

/*
 * HISTORY:
 * $Log: not supported by cvs2svn $ 
 */ 