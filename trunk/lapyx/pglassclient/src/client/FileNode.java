package client;

/**
 * FileNode is an essential class in getting the FileTree to work.
 * Each File node is created from a File.  It used that File to
 * figure out its children.  I've also added a method to retrieve
 * this file in case we need to do something with it. IE read it
 * from the disk.
 * 
 * @author Kris Kalish
 * @date 8/13/2007
 */

import java.io.File;
import java.util.Enumeration;
import java.util.Vector;

import javax.swing.tree.TreeNode;


class FileNode implements TreeNode { 
    private File   			 file;     // the actual file this node represents
    private Vector<TreeNode> children;
    private TreeNode         parent;
    private boolean          isLeaf;
    private int              childCount;


    /**
     * Constructor for the root FileNode.
     * Also called by the other constructor
     * as shorthand.
     */
    public FileNode(File file) {
    	childCount = 0;
    	this.file = file;
    	children = new Vector<TreeNode>();
    	isLeaf = false;
    }
    
    /**
     * Constructor for child nodes
     * @param file - File that this node represents
     * @param parent - Node spawning this node
     * @param isLeaf - leaves are the end of a tree
     */
    public FileNode(File file, TreeNode parent, boolean isLeaf) {
    	this(file);
    	this.parent = parent;
    	this.isLeaf = isLeaf; 
    }


    //--------------------------------------
    // Methods from the TreeNode interface
    // Docs grabbed from the API
    //--------------------------------------
    
    /**
     * Returns the children of the receiver as an Enumeration.
     */
    public Enumeration children() {
    	if(children.isEmpty())
    		buildChildren();

    	return children.elements();
    }
    
    /**
     * Returns true if the receiver allows children.
     */
    public boolean getAllowsChildren() {
    	return false;
    	//return (this.getChildCount() > 0);
    }
    
    /**
     * Returns the child TreeNode at index childIndex.
     */
    public TreeNode getChildAt(int childIndex) {
    	return children.elementAt(childIndex);
    }
    
    /**
     * Returns the number of children TreeNodes the receiver contains.
     */
    public int getChildCount() {
    	if(children.isEmpty())
    		buildChildren();
    	
    	return childCount;
    }
    
    /**
     * Returns the index of node in the receivers children. If the 
     * receiver does not contain node, -1 will be returned.
     */
    public int getIndex(TreeNode node) {
    	int index = -1;
    	//TODO: this surely could be optimized
    	for(int ii = 0; ii < children.size(); ii++) {
    		if(children.elementAt(ii) == node) {
    			index = ii;
    			break;
    		}
    	}
    	
    	return index;
    }

    /**
     * Returns the parent TreeNode of the receiver.
     */
    public TreeNode getParent() {
    	return parent;
    }

    /**
     * Returns true if the receiver is a leaf.
     */
    public boolean isLeaf() {
    	return isLeaf;
    }
    
    //-----------------------------------
    // Methods outside of the TreeNode interface
    //-----------------------------------
    public String toString() {
        return file.getName();
    }
    
    /**
     * @return The File this node represents.
     */
    public File getFile() {
    	return file;
    }
    
    /**
     * Builds up a vector of children that are subordinate
     * to this node by using the File class.
     */
    private void buildChildren() {
    	// build a vector of children if we haven't already
    	if(children.isEmpty()) {
    		
    		String childNames[]; // will store children file/direc names
    		
    		childNames = file.list();
    		//file.listFiles(FilenameFilter filter)
    		if(childNames != null)
    		{
    			childCount = childNames.length;
	    		for(int ii = 0; ii < childNames.length; ii++) {
	    			File childFile;
	    			FileNode childNode;
	    			
	    			// create the child file by using parent File 
	    			// paired with child name
	    			childFile = new File(file, childNames[ii]);
	    			//System.out.println("Adding child " + childNames[ii] + " to " +
	    			//		file.getName());
	    			if(childFile.isFile())
	    				childNode = new FileNode(childFile, this, true);
	    			else
	    				childNode = new FileNode(childFile, this, false); 
	    			children.add(childNode);
	    		}
    		}
    	}
    }
}