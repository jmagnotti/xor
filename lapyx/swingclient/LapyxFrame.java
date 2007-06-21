import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.HashMap;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListCellRenderer;

public class LapyxFrame extends JFrame 
{

	private JList demoList;

	private JScrollPane scrollableDemoList;

	LapyxFrame(Vector<DemoEntry> demoEntries) {
		super("Lapyx Launcher"); // title window
		setBounds(10, 10, 400, 460); // big window
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// fill the list up with demos
		populateList(demoEntries);

		addComponentsToPane(this.getContentPane());

		LapyxMouseCommands lmc = new LapyxMouseCommands();

		demoList.addMouseListener(lmc);

	}

	public void addComponentsToPane(Container pane) {

		if (!(pane.getLayout() instanceof BorderLayout)) {
			pane.add(new JLabel("Container doesn't use BorderLayout!"));
			return;
		}

		/*
		 * // All of the positions availible to me pane.add(button,
		 * BorderLayout.PAGE_START); pane.add(button, BorderLayout.CENTER);
		 * pane.add(button, BorderLayout.LINE_START); pane.add(button,
		 * BorderLayout.PAGE_END); pane.add(button, BorderLayout.LINE_END);
		 */

		scrollableDemoList = new JScrollPane(demoList);

		pane.add(scrollableDemoList, BorderLayout.CENTER);

		// pane.add(demoList, BorderLayout.CENTER);

	}

	private void populateList(Vector<DemoEntry> demoEntries) {

		// add them
		demoList = new JList(demoEntries);

		// now take care of some odds and ends
		demoList.setCellRenderer(new ImgTextCellRenderer()); // lets us use
		// imgs
		demoList.setFixedCellHeight(138); // 5px padding

		// demoList.setPreferredSize(new Dimension(200, 220)); // BIG
	}

	/** ***************** INNER CLASSES ****************** */

	private class LapyxMouseCommands extends MouseAdapter {

		private final TCPClient client;

		public LapyxMouseCommands() {
			client = new TCPClient("localhost");
		}

		@Override
		public void mouseClicked(MouseEvent e) {
			super.mouseClicked(e);

			if (e.getClickCount() == 2) {
				int index = demoList.locationToIndex(e.getPoint());
				System.out.println("Double clicked on Item " + index);

				DemoEntry something = (DemoEntry) demoList.getSelectedValue();

				System.out.println(something.getName());

				client.sendData(something.getName());

			}
		}
	}
	
	
	/*
	 * 
	 */
	class ImgTextCellRenderer extends JLabel implements ListCellRenderer {
		public ImgTextCellRenderer() {
			setOpaque(true);
		}

		public Component getListCellRendererComponent(JList list, Object value,
				int index, boolean isSelected, boolean cellHasFocus) {
			DemoEntry entry = (DemoEntry) value;
			setText(entry.getName());
			setIcon(entry.getScreenshot());
			// setBackground(isSelected ? Color.red : (index & 1) == 0 ?
			// Color.cyan : Color.green);

			// setForeground(isSelected ? Color.white : Color.black);
			if (isSelected)
				setBackground(Color.lightGray);
			else
				setBackground(Color.white);

			return this;
		}
	}

}
