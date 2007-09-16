package client;

/**
 * I'll use this space to discuss the general structure of the PhotoGlass
 * image up-loader. So We start with a frame that has a split pane in it.
 * In the left pane is a FileTree (custom class) wrapped in a scroll pane.
 * The FileTree is a child class of JTree.  This is actually an unnecessary 
 * class, and only serves for convenience and enhancement of readability.
 * 
 * The FileTree sets its model as the FileHierarchyModel, a custom class
 * subclassed from TreeModel.  This takes a file as a root point.  Since
 * the tree is made of of FileNodes, each which knows its own children, we
 * produce a tree model of the file system.
 * 
 * The ImageSelector is actually the model for a JList.  The JList resides
 * in the right pane wrapped in JScrollPane.It's perhaps the most 
 * complicated of the GUI components.  It's a TreeSelectionListener, 
 * enabling it to be informed of selections in the tree.  It also keeps a 
 * reference to the file tree to access FileNodes in it.  Upon selection
 * it rebuilds a vector of components that should be in the list, and fires
 * off events to listeners depicting the changes.  
 *  
 *  @author Kristopher Kalish
 *  @date 8/12/2007
 *  @version 1 a
 * 
 */

import javax.swing.JFrame;

public class Driver {

	//TODO: Write a method to create an applet
	
    /**
     * Simply creates a JFrame and adds all of our goodies to 
     * it. This is thrown into a separate function so we can
     * make a thread-safe call to it.
     */
    private static void createAndShowGUI() {
        JFrame frame = new JFrame("PhotoGlass Image Uploader");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        BrowsingPanes imageUploader = new BrowsingPanes();
        frame.getContentPane().add(imageUploader.getSplitPane());

        // display window
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        // Sweet thread-safe way to create a window
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }

}
