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
package sof.editor;

import org.eclipse.gef.palette.CombinedTemplateCreationEntry;
import org.eclipse.gef.palette.ConnectionCreationToolEntry;
import org.eclipse.gef.palette.MarqueeToolEntry;
import org.eclipse.gef.palette.PaletteContainer;
import org.eclipse.gef.palette.PaletteDrawer;
import org.eclipse.gef.palette.PaletteGroup;
import org.eclipse.gef.palette.PaletteRoot;
import org.eclipse.gef.palette.PaletteSeparator;
import org.eclipse.gef.palette.PanningSelectionToolEntry;
import org.eclipse.gef.palette.ToolEntry;
import org.eclipse.gef.requests.CreationFactory;
import org.eclipse.gef.requests.SimpleFactory;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.ui.plugin.AbstractUIPlugin;

import sof.common.ShapesPlugin;
import sof.editor.shapes.model.BundleActivatorShape;
import sof.editor.shapes.model.Connection;
import sof.editor.shapes.model.ServiceListenerShape;
import sof.editor.shapes.model.ServiceShape;

/**
 * Utility class that can create a GEF Palette.
 * @see #createPalette() 
 * @author  
 */
final class ShapesEditorPaletteFactory {

/** Preference ID used to persist the palette location. */
private static final String PALETTE_DOCK_LOCATION = "ShapesEditorPaletteFactory.Location";
/** Preference ID used to persist the palette size. */
private static final String PALETTE_SIZE = "ShapesEditorPaletteFactory.Size";
/** Preference ID used to persist the flyout palette's state. */
private static final String PALETTE_STATE = "ShapesEditorPaletteFactory.State";

/** Create the "Shapes" drawer. */
private static PaletteContainer createShapesDrawer() {
	PaletteDrawer componentsDrawer = new PaletteDrawer("Shapes");

	// TODO: remove unused code
//	CombinedTemplateCreationEntry component = new CombinedTemplateCreationEntry(
//			"Ellipse", 
//			"Create an elliptical shape", 
//			EllipticalShape.class,
//			new SimpleFactory(EllipticalShape.class), 
//			ImageDescriptor.createFromFile(ShapesPlugin.class, "icons/ellipse16.gif"), 
//			ImageDescriptor.createFromFile(ShapesPlugin.class, "icons/ellipse24.gif"));
//	componentsDrawer.add(component);
//
//	component = new CombinedTemplateCreationEntry(
//			"Rectangle",
//			"Create a rectangular shape", 
//			RectangularShape.class,
//			new SimpleFactory(RectangularShape.class), 
//			ImageDescriptor.createFromFile(ShapesPlugin.class, "icons/rectangle16.gif"), 
//			ImageDescriptor.createFromFile(ShapesPlugin.class, "icons/rectangle24.gif"));
//	componentsDrawer.add(component);
	
	    
	CombinedTemplateCreationEntry component = new CombinedTemplateCreationEntry(
        "Bundle Activator",
        "Create a bundle activator shape", 
        BundleActivatorShape.class,
        new SimpleFactory(BundleActivatorShape.class), 
        AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/rectangle16.gif" ),       
        AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/rectangle24.gif"));
    componentsDrawer.add(component);

    component = new CombinedTemplateCreationEntry(
        "Service Listener",
        "Create a service listener shape", 
        ServiceListenerShape.class,
        new SimpleFactory(ServiceListenerShape.class), 
        AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/rectangle16.gif"), 
        AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/rectangle24.gif"));
    componentsDrawer.add(component);

    component = new CombinedTemplateCreationEntry(
        "Service",
        "Create a service shape", 
        ServiceShape.class,
        new SimpleFactory(ServiceShape.class), 
        AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/rectangle16.gif"), 
        AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/rectangle24.gif"));
    componentsDrawer.add(component);

	return componentsDrawer;
}
	
/**
 * Creates the PaletteRoot and adds all palette elements.
 * Use this factory method to create a new palette for your graphical editor.
 * @return a new PaletteRoot
 */
static PaletteRoot createPalette() {
	PaletteRoot palette = new PaletteRoot();
	palette.add(createToolsGroup(palette));
	palette.add(createShapesDrawer());
	return palette;
}

/** Create the "Tools" group. */
private static PaletteContainer createToolsGroup(PaletteRoot palette) {
	PaletteGroup toolGroup = new PaletteGroup("Tools");

	// Add a selection tool to the group
	ToolEntry tool = new PanningSelectionToolEntry();
	toolGroup.add(tool);
	palette.setDefaultEntry(tool);
	
	// Add a marquee tool to the group
	toolGroup.add(new MarqueeToolEntry());

	// Add a (unnamed) separator to the group
	toolGroup.add(new PaletteSeparator());

	// Add (solid-line) connection tool 
	tool = new ConnectionCreationToolEntry(
			"Solid connection",
			"Create a solid-line connection",
			new CreationFactory() {
				public Object getNewObject() { return null; }
				// see ShapeEditPart#createEditPolicies() 
				// this is abused to transmit the desired line style 
				public Object getObjectType() { return Connection.SOLID_CONNECTION; }
			},
			AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/connection_s16.gif"),
			AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/connection_s24.gif"));
	toolGroup.add(tool);
	
	// Add (dashed-line) connection tool
	tool = new ConnectionCreationToolEntry(
			"Dashed connection",
			"Create a dashed-line connection",
			new CreationFactory() {
				public Object getNewObject() { return null; }
				// see ShapeEditPart#createEditPolicies()
				// this is abused to transmit the desired line style 
				public Object getObjectType() { return Connection.DASHED_CONNECTION; }
			},
			AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/connection_d16.gif"),
			AbstractUIPlugin.imageDescriptorFromPlugin( "sof.admin.ui", "resources/icons/connection_d24.gif"));
	toolGroup.add(tool);

	return toolGroup;
}

/** Utility class. */
private ShapesEditorPaletteFactory() {
	// Utility class
}

}