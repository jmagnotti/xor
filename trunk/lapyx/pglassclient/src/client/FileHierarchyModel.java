package client;

import java.io.File;

import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

public class FileHierarchyModel implements TreeModel {
	
	FileNode root;
	
	/**
	 * Creates a hierarchy of FileNodes starting with the 
	 * file passed in. Each node will take care of figuring
	 * out its own children.  Easy huh?
	 * 
	 * @param rootFile - The top of the hierarchy, usually / or c:/
	 */
	FileHierarchyModel(File rootFile) {
		root = new FileNode(rootFile);
	}
	
	//----------------------------------
	// The following methods are part of the TreeModel interface.
	// Documentation is from the Java Docs
	//----------------------------------
	/**
	 * Adds a listener for the TreeModelEvent  posted after the tree changes.
	 * @param l - the listener to add
	 */
	public void addTreeModelListener(TreeModelListener l) {
	}
	
	/**
     * Returns the child of parent at index index  in the parent's child array. 
     * parent must be a node previously obtained from this data source. This 
     * should not return null  if index  is a valid index for parent (that is 
     * index >= 0 &&  index < getChildCount(parent)).
     * @param parent - a node in the tree, obtained from this data source 
     * @return the child of parent at index index
     */
	public Object getChild(Object parent, int index) {
		TreeNode tnode = (TreeNode) parent;
		return tnode.getChildAt(index);
	}
	
	/**
     * Returns the number of children of parent. Returns 0 if the node is a 
     * leaf or if it has no children. Parent must be a node previously obtained 
     * from this data source.
     * 
     * @param parent - a node in the tree, obtained from this data source 
	 * @return the number of children of the node parent
     */
	public int getChildCount(Object parent) {
		TreeNode tnode = (TreeNode) parent;
		return tnode.getChildCount();
	}
	
	/**
	 * Returns the index of child in parent. If either parent  or child is null, 
	 * returns -1. If either parent or child don't belong to this tree model, 
	 * returns -1.
	 * @param parent - a note in the tree, obtained from this data source
	 * @param child - the node we are interested in
	 * @return the index of the child in the parent, or -1 if either child or 
	 * parent are null  or don't belong to this tree model
	 */
	public int getIndexOfChild(Object parent, Object child) {
		TreeNode pNode = (TreeNode) parent;
		TreeNode cNode = (TreeNode) child;
		
		return pNode.getIndex(cNode);
	}
	
	/**
	 * Returns the root of the tree. Returns null only if the tree has no nodes.
	 * @return the root of the tree
	 */
	public Object getRoot() {
		return root;
	}

	/**
	 * Returns true if node is a leaf. It is possible for this method to return 
	 * false  even if node has no children. A directory in a filesystem, for 
	 * example, may contain no files; the node representing the directory is 
	 * not a leaf, but it also has no children.
     * @param node - a node in the tree, obtained from this data source 
     * @return true if node is a leaf
	 */
	public boolean isLeaf(Object node) {
		// We must cast and store in order to use isLeaf()
		// Java doesn't like us casting and accessing 
		// isLeaf() in one line
		TreeNode tnode = (TreeNode) node;
		return tnode.isLeaf();
	}
	
	/**
	 * Removes a listener previously added with addTreeModelListener.
     * @param l - the listener to remove
	 */
	public void removeTreeModelListener(TreeModelListener l) {
		
	}
	
    /**
     * Messaged when the user has altered the value for the item identified by path 
     * to newValue. If newValue signifies a truly new value the model should post a 
     * treeNodesChanged event.
     * @param path - path to the node that the user has altered
     * @param newValue - the new value from the TreeCellEditor
     */
	public void valueForPathChanged(TreePath path, Object newValue) {
		
	}
 
}
