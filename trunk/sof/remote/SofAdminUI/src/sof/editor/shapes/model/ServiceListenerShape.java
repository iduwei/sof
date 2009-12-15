package sof.editor.shapes.model;

import org.eclipse.jface.viewers.ICellEditorValidator;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

public class ServiceListenerShape extends Shape
{
    /** A 16x16 pictogram of a rectangular shape. */
    private static final Image RECTANGLE_ICON = AbstractUIPlugin
		.imageDescriptorFromPlugin( "sof.admin.ui","resources/icons/rectangle16.gif" ).createImage();;

    private static final long serialVersionUID = 1;

    public static final String LISTEN_TO_SERVICE_NAME = "Listen to service name";

    private String serviceName = "";

    public ServiceListenerShape()
    {
        TextPropertyDescriptor propDesc = new TextPropertyDescriptor(LISTEN_TO_SERVICE_NAME, LISTEN_TO_SERVICE_NAME); 
        
        this.propertyDescriptorList.add( propDesc );
        
       
        propDesc.setValidator(new ICellEditorValidator() {
            public String isValid(Object value) {
                return null;
            }
        });
    }

    private String getServiceName()
    {
        return this.serviceName;
    }

    private void setServiceName( String name )
    {
        this.serviceName = name;
        firePropertyChange(LISTEN_TO_SERVICE_NAME, null, this.serviceName );
    }

    public Image getIcon() {
        return RECTANGLE_ICON;
    }

    public String toString() {
        return "ServiceListenerShape " + hashCode();
    }

    public Object getPropertyValue(Object propertyId) {
        if (LISTEN_TO_SERVICE_NAME.equals(propertyId)) {
            return this.getServiceName();
        }
        return super.getPropertyValue(propertyId);
    }

    public void setPropertyValue(Object propertyId, Object value) {
        if (LISTEN_TO_SERVICE_NAME.equals(propertyId)) {
            this.setServiceName( ( String ) value );        
        } else {
            super.setPropertyValue(propertyId, value);
        }
    }
}

/*
 * HISTORY:
 * $Log: not supported by cvs2svn $ 
 */ 