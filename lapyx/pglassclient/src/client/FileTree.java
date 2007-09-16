package client;

/**
 * A convenience class for making a file browser. It takes
 * care of setting its own selection mode and model.
 * 
 * @author Kristopher Kalish
 * @date 8/12/2007
 */

import java.io.File;

import javax.swing.JTree;
import javax.swing.tree.TreeSelectionModel;

public class FileTree extends JTree {
	
	/**
	 * Creates a file browser in JTree form.
	 * 
	 * @param rootFile Where the tree should start branching from
	 */
	public FileTree(File rootFile) {

		this.setModel(new FileHierarchyModel(rootFile));
	    //Create a tree that allows one selection at a time.
	    this.getSelectionModel().setSelectionMode
	            (TreeSelectionModel.SINGLE_TREE_SELECTION);
		
	}
}
