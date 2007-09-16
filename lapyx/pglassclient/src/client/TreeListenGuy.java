package client;
/** NOT A REAL CLASS JUST AN EXAMPLE */
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;

public class TreeListenGuy implements TreeSelectionListener {
	private JTree tree;
	public TreeListenGuy(JTree tree) {
		this.tree = tree;
		this.tree.addTreeSelectionListener(this);
	}

	public void valueChanged(TreeSelectionEvent e) {
		//Returns the last path element of the selection.
		//This method is useful only when the selection model allows a single selection.
		    DefaultMutableTreeNode node = (DefaultMutableTreeNode)
		                       tree.getLastSelectedPathComponent();

		    if (node == null)
		    //Nothing is selected.	
		    return;

		    Object nodeInfo = node.getUserObject();
		    if (node.isLeaf()) {
		        // do something
		    } else {
		        // do something else
		    }
	}
}
