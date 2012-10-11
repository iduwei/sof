/*
 * 
 * NAME: CustomRectangleFigure.java
 * CREATED BY: magr2419
 * DATE: 06.10.2008
 * 
 * $Id: BundleActivatorFigure.java,v 1.1 2009-12-15 17:29:11 magr74 Exp $
 */

package sof.editor.shapes.figure;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.RectangleFigure;
import org.eclipse.draw2d.ToolbarLayout;


public class BundleActivatorFigure extends RectangleFigure
{

    private Label bundleActivatorLabel;
    private Label bundleActivatorNameLabel;
    
    
    public BundleActivatorFigure()
    {
        ToolbarLayout layout = new ToolbarLayout( false );
        layout.setStretchMinorAxis( true );
        this.setLayoutManager( layout );
        this.bundleActivatorLabel = new Label( "Bundle Activator" );      
        System.out.println( "Font: " + this.bundleActivatorLabel.getFont() );
        this.bundleActivatorLabel.setTextAlignment( PositionConstants.CENTER ); 
        this.bundleActivatorNameLabel = new Label( "" );
        this.bundleActivatorNameLabel.setTextAlignment( PositionConstants.LEFT ); 
        this.add( this.bundleActivatorLabel );
        this.add( this.bundleActivatorNameLabel );
        this.setBackgroundColor( ColorConstants.lightBlue );
    }

    public void setText( String str )
    {
        this.bundleActivatorNameLabel.setText( str );
    }
}


/*
 * HISTORY:
 * $Log: not supported by cvs2svn $ 
 */ 