

package sof.editor.shapes.figure;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.RectangleFigure;
import org.eclipse.draw2d.ToolbarLayout;
import org.eclipse.swt.graphics.Color;


public class ServiceListenerFigure extends RectangleFigure
{

    private Label serviceNameLabel;
    
    public ServiceListenerFigure()
    {
        ToolbarLayout layout = new ToolbarLayout( false );        
        layout.setStretchMinorAxis( true );
        this.setLayoutManager( layout );
        this.serviceNameLabel = new Label( "" );
        this.serviceNameLabel.setTextAlignment( PositionConstants.LEFT ); 
        this.add( new Label( "Service Listener" ) );
        this.add( this.serviceNameLabel );
        this.setBackgroundColor( ColorConstants.yellow );        
    }

    public void setServiceName( String str )
    {
        this.serviceNameLabel.setText( str );
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