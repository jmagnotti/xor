package client;

import java.util.Enumeration;
import java.util.Vector;

import javax.swing.ListModel;
import javax.swing.event.ListDataEvent;
import javax.swing.event.ListDataListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;

public class ImageSelector implements ListModel, TreeSelectionListener {
	private FileTree         tree;
	
	private Vector<ListDataListener> listeners;
	
	private Vector<FileNode> selected; // all of the checked pictures
	private Vector<FileNode> visible;  // all of the visible pictures
	
	public ImageSelector(FileTree observerTree) {
		this.tree = observerTree;
		tree.addTreeSelectionListener(this);
		visible = new Vector<FileNode>();
		listeners = new Vector<ListDataListener>();
	}
	
	 public void addListDataListener(ListDataListener l) {
		 listeners.add(l);
	 }
	 
	 public Object getElementAt(int index) {
		 return visible.get(index);
     }
	 
	 public int getSize() {
		 return (visible != null ? visible.size() : 0);
     }

	 public void removeListDataListener(ListDataListener l) {
		 listeners.removeElement(l);
	 }

	 public void valueChanged(TreeSelectionEvent e) {
		 FileNode node = (FileNode) tree.getLastSelectedPathComponent();
		 if (node == null) // nothing was selected	
			 return;
		 cleanList(); 
		 //Object nodeInfo = node.getUserObject();
		 if (node.isLeaf()) {
			 System.out.println(node);
		 } else {
			 buildList(node.children());

			 System.out.println("Added elements to model...");
		 }
	 }
	 
	 /**
	  * Rebuilds the list from an Enumeration, and fires an
	  * event to all of the listeners.
	  */
	 private void buildList(Enumeration e) {
		 for (int i = 0; e.hasMoreElements() ; i++) {
			 ListDataEvent added = 
				 new ListDataEvent(this, ListDataEvent.INTERVAL_REMOVED, i, i + 1);
			 visible.add((FileNode) e.nextElement());
			 fireListDataEvent(added);
			 
		 }
	 }
	 
	 private void cleanList() {
		 ListDataEvent cleaned = 
			 new ListDataEvent(this, ListDataEvent.INTERVAL_REMOVED, 0, visible.size());
		 fireListDataEvent(cleaned);
		 visible.clear();
	 }
	 
	 /**
	  * Sends the ListDataEvent to all of the listeners
	  */
	 private void fireListDataEvent(ListDataEvent lde) {
	        for(int i = 0; i < listeners.size(); i++) {
	        	if(lde.getType() == ListDataEvent.CONTENTS_CHANGED) 
	        		listeners.get(i).contentsChanged(lde);
	        	if(lde.getType() == ListDataEvent.INTERVAL_ADDED)
	        		listeners.get(i).intervalAdded(lde);
	        	if(lde.getType() == ListDataEvent.INTERVAL_REMOVED)
	        		listeners.get(i).intervalRemoved(lde);
	        }
	 }

}
