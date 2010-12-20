package sof.editor.shapes.model;

import org.eclipse.jface.viewers.ICellEditorValidator;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

public class ServiceShape extends Shape
{
    /** A 16x16 pictogram of a rectangular shape. */
    private static final Image RECTANGLE_ICON = AbstractUIPlugin
		.imageDescriptorFromPlugin( "sof.admin.ui","resources/icons/rectangle16.gif" ).createImage();;

    private static final long serialVersionUID = 1;

    public static final String SERVICE_NAME = "Service name";
    public static final String PROPERTIES = "Properties";

    private String serviceName = "";
    private String properties = "";
    
    public ServiceShape()
    {
        TextPropertyDescriptor propDesc = new TextPropertyDescriptor(SERVICE_NAME, SERVICE_NAME);         
        this.propertyDescriptorList.add( propDesc );
        
        propDesc = new TextPropertyDescriptor(PROPERTIES, PROPERTIES);
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
        firePropertyChange(SERVICE_NAME, null, this.serviceName );
    }

    private String getProperties()
    {
        return this.properties;
    }
    
    private void setProperties( String props )
    {
        this.properties = props;
        firePropertyChange( PROPERTIES, null, this.properties );
    }
    
    public Image getIcon() {
        return RECTANGLE_ICON;
    }

    public String toString() {
        return "ServiceName " + hashCode();
    }

    public Object getPropertyValue(Object propertyId) {
        if (SERVICE_NAME.equals(propertyId)) {
            return this.getServiceName();
        }
        else if ( PROPERTIES.equals( propertyId ) )
        {
            return this.getProperties();
        }
        return super.getPropertyValue(propertyId);
    }

    public void setPropertyValue(Object propertyId, Object value) {
        if (SERVICE_NAME.equals(propertyId)) {
            this.setServiceName( ( String ) value );        
        }
        else if ( PROPERTIES.equals( propertyId ) )
        {
            this.setProperties( ( String  ) value );
        }
        else {
            super.setPropertyValue(propertyId, value);
        }
    }
}

/*
 * HISTORY:
 * $Log: not supported by cvs2svn $ 
 */ 