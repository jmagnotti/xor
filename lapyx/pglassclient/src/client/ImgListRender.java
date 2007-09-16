package client;

import java.awt.Color;
import java.awt.Component;

import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;


/**
 * Since a JList is nothing more than a bunch of JLabels with a renderer,
 * this class replaces the default so we can add pictures with our text and
 * even customize the highlight color(s).
 */
class ImgListRenderer extends JLabel implements ListCellRenderer {
	// alternating highlight colors
	private final Color VERYLIGHTGREY = new Color(237, 237, 237);
	private final Color VERYLIGHTGREEN = new Color(241, 247, 223);

	/**
	 * This default constructor does nothing more than to set the label to
	 * opaque
	 */
	public ImgListRenderer() {
		setOpaque(true);
	}

	/**
	 * This method is called by the JList (or something) every time a cell
	 * needs to be redrawn. It's the method responsible for our custom look.
	 * 
	 * @param list List this Component belongs to
	 * @param value Value of this Component in the list
	 * @param index Index (from 0) in the list
	 * @param isSelected Whether or not the user selected this item
	 * @param cellHasFocus
	 */
	public Component getListCellRendererComponent(JList list, Object value,
			int index, boolean isSelected, boolean cellHasFocus) {
		//DemoEntry entry = (DemoEntry) value;
		//setText(entry.getName());
		//setIcon(entry.getScreenshot());

		// alternate highlight colors, white if not selected
		if (isSelected)
			setBackground(index % 2 == 0 ? VERYLIGHTGREY : VERYLIGHTGREEN);
		else
			setBackground(Color.white);

		return this;
	}
}