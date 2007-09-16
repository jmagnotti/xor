package client;

/**
 * This is essentially a throw-away class used to couple
 * the FileTree and ImageSelctor, two highly related
 * classes.  This is probably a bad thing. Must do more
 * research...
 * 
 * @author Kristopher Kalish
 * @date 8/23/2007
 */

import java.awt.Dimension;
import java.io.File;

import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


public class BrowsingPanes implements ListSelectionListener {

    private JSplitPane    splitPane;
    private FileTree      fileTree;
    private ImageSelector imageSelector;

    public BrowsingPanes() {
    	fileTree      = new FileTree(new File(File.separator));
    	imageSelector = new ImageSelector(fileTree);
    	
        JScrollPane listScrollPane = new JScrollPane(fileTree);

        JScrollPane pictureScrollPane = new JScrollPane(new JList(imageSelector));

        //Create a split pane with the two scroll panes in it.
        splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                                   listScrollPane, pictureScrollPane);
        splitPane.setOneTouchExpandable(true);
        
        // set a proportional divider location
        splitPane.setResizeWeight(.25);


        // Provide a preferred size for the split pane.
        splitPane.setPreferredSize(new Dimension(600, 400));
    }
    
    public JSplitPane getSplitPane() {
    	return splitPane;
    }


    public void valueChanged(ListSelectionEvent e) {
        if (e.getValueIsAdjusting())
            return;

        JList theList = (JList)e.getSource();
        if (theList.isSelectionEmpty()) {

        } else {
        }
    }
}


