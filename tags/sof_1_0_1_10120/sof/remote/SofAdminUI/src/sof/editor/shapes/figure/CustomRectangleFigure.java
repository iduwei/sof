
package sof.editor.shapes.figure;

import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.RectangleFigure;
import org.eclipse.draw2d.ToolbarLayout;


public class CustomRectangleFigure extends RectangleFigure
{

    public CustomRectangleFigure()
    {
        ToolbarLayout layout = new ToolbarLayout( false );
        layout.setStretchMinorAxis( true );
        this.setLayoutManager( layout );
        Label lblName = new Label( "Test" );
        lblName.setTextAlignment( PositionConstants.CENTER ); 
        this.add( lblName );
    }
}


/*
 * HISTORY:
 * $Log: not supported by cvs2svn $ 
 */ 