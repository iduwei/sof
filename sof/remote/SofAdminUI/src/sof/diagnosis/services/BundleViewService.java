package sof.diagnosis.services;

import sof.diagnosis.namingservice.ProcessNode;

/**
 * This interface class provides methods for communication with
 * the bundle data view.
 * 
 * @author magr74
 *
 */
public interface BundleViewService
{
	/**
	 * Sets the selected SOF process to the
	 * bundle data view.
	 * 
	 * @param process
	 * 				The selected SOF process.
	 */
	void setSelectedProcessNode( ProcessNode process );
}
