
package sof.editor.shapes.figure;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.RectangleFigure;
import org.eclipse.draw2d.ToolbarLayout;
import org.eclipse.swt.graphics.Color;


public class ServiceFigure extends RectangleFigure
{

    private Label serviceNameLabel;
    private Label propertiesLabel;
    
    public ServiceFigure()
    {
        ToolbarLayout layout = new ToolbarLayout( false );        
        layout.setStretchMinorAxis( true );
        this.setLayoutManager( layout );
        this.serviceNameLabel = new Label( "" );
        this.propertiesLabel = new Label( "" );
        this.serviceNameLabel.setTextAlignment( PositionConstants.LEFT ); 
        this.propertiesLabel.setTextAlignment( PositionConstants.LEFT );
        this.add( new Label( "Service" ) );
        this.add( this.serviceNameLabel );
        this.add( this.propertiesLabel );
        this.setBackgroundColor( ColorConstants.green );        
    }

    public void setServiceName( String str )
    {
        this.serviceNameLabel.setText( str );
    }
    
    public void setProperties( String props )
    {
        this.propertiesLabel.setText( props );
    }
    
    public void setBackgroundColor(Color bg) {
        System.out.println( "[ServiceListenerFigure#setBackgroundColor] Color: " + bg );
        super.setBackgroundColor( bg );
    }
}


/*
 * HISTORY:
 * $Log: not supported by cvs2svn $ 
 */ 