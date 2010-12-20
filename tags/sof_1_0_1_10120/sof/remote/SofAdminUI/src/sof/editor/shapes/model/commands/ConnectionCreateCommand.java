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
package sof.editor.shapes.model.commands;

import java.util.Iterator;

import org.eclipse.gef.commands.Command;

import sof.editor.shapes.model.BundleActivatorShape;
import sof.editor.shapes.model.Connection;
import sof.editor.shapes.model.ServiceListenerShape;
import sof.editor.shapes.model.ServiceShape;
import sof.editor.shapes.model.Shape;


/**
 * A command to create a connection between two shapes.
 * The command can be undone or redone.
 * <p>
 * This command is designed to be used together with a GraphicalNodeEditPolicy.
 * To use this command properly, following steps are necessary:
 * </p>
 * <ol>
 * <li>Create a subclass of GraphicalNodeEditPolicy.</li>
 * <li>Override the <tt>getConnectionCreateCommand(...)</tt> method, 
 * to create a new instance of this class and put it into the CreateConnectionRequest.</li>
 * <li>Override the <tt>getConnectionCompleteCommand(...)</tt>  method,
 * to obtain the Command from the ConnectionRequest, call setTarget(...) to set the
 * target endpoint of the connection and return this command instance.</li>
 * </ol>
 * @see sof.editor.shapes.parts.examples.shapes.parts.ShapeEditPart#createEditPolicies() for an
 * 			 example of the above procedure.
 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy
 * @author  
 */
public class ConnectionCreateCommand extends Command {
/** The connection instance. */
private Connection connection;
/** The desired line style for the connection (dashed or solid). */
private final int lineStyle;

/** Start endpoint for the connection. */
private final Shape source;
/** Target endpoint for the connection. */
private Shape target;

/**
 *	Instantiate a command that can create a connection between two shapes.
 * @param source the source endpoint (a non-null Shape instance)
 * @param lineStyle the desired line style. See Connection#setLineStyle(int) for details
 * @throws IllegalArgumentException if source is null
 * @see Connection#setLineStyle(int)
 */
public ConnectionCreateCommand(Shape source, int lineStyle) {
	if (source == null) {
		throw new IllegalArgumentException();
	}
	setLabel("connection creation");
	this.source = source;
	this.lineStyle = lineStyle;
}

/* (non-Javadoc)
 * @see org.eclipse.gef.commands.Command#canExecute()
 */
public boolean canExecute() {
    
    System.out.println( "[ConnectionCreateCommand#canExecute] Source: " + this.source + ", target: " + this.target );

    // BundleActivatorShape must not be a target
    System.out.println( "[ConnectionCreateCommand#canExecute] #1" );
    
    if ( this.target != null && 
                    this.target.getClass().getName().equals( BundleActivatorShape.class.getName() ) )
    {
        System.out.println( "[ConnectionCreateCommand#canExecute] BundleActivatorShape must not be a target." );
        return false;
    }
    
    if ( this.source != null && this.source.getClass().getName().equals( ServiceShape.class.getName() ) )
    {
        System.out.println( "[ConnectionCreateCommand#canExecute] ServiceShape must not be a source." );
        return false;
    }
    
    if ( this.source != null && this.source.getClass().getName().equals( ServiceListenerShape.class.getName() ) )
    {
        System.out.println( "[ConnectionCreateCommand#canExecute] ServiceListenerShape must not be a source." );
        return false;
    }
    
    System.out.println( "[ConnectionCreateCommand#canExecute] #2" );
    // disallow source -> source connections
	if (source.equals(target)) {
	    System.out.println( "[ConnectionCreateCommand#canExecute] Source -> Source connection not allowed." );
		return false;
	}
	// return false, if the source -> target connection exists already
	for (Iterator iter = source.getSourceConnections().iterator(); iter.hasNext();) {
		Connection conn = (Connection) iter.next();
		if (conn.getTarget().equals(target)) {
		      System.out.println( "[ConnectionCreateCommand#canExecute] Source -> target connection already exists." );
			return false;
		}
	}
	return true;
}

/* (non-Javadoc)
 * @see org.eclipse.gef.commands.Command#execute()
 */
public void execute() {
	// create a new connection between source and target
	connection = new Connection(source, target);
	// use the supplied line style
	connection.setLineStyle(lineStyle);
}

/* (non-Javadoc)
 * @see org.eclipse.gef.commands.Command#redo()
 */
public void redo() {
	connection.reconnect();
}

/**
 * Set the target endpoint for the connection.
 * @param target that target endpoint (a non-null Shape instance)
 * @throws IllegalArgumentException if target is null
 */
public void setTarget(Shape target) {
	if (target == null) {
		throw new IllegalArgumentException();
	}
	this.target = target;
}

/* (non-Javadoc)
 * @see org.eclipse.gef.commands.Command#undo()
 */
public void undo() {
	connection.disconnect();
}
}
