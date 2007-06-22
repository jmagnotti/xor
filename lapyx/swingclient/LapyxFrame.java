import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListCellRenderer;
import javax.swing.border.Border;

public class LapyxFrame extends JFrame 
{
	private JList demoList;
	private JScrollPane scrollableDemoList;

	LapyxFrame(Vector<DemoEntry> demoEntries) {
		super("Lapyx Launcher"); // title window
		setBounds(10, 10, 400, 600); // big window
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
		
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

		
		Border blackline = BorderFactory.createLineBorder(Color.WHITE, 5);
		
		demoList.setBorder(blackline);
		scrollableDemoList = new JScrollPane(demoList);
		
		pane.add(scrollableDemoList, BorderLayout.CENTER);

		// add logo
		pane.add(new JLabel(loadImage("img/logo.png")), BorderLayout.PAGE_START);
		// add side
		pane.add(new JLabel(loadImage("img/side.png")), BorderLayout.WEST);

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
	
	private ImageIcon loadImage(String filename)
	{
		java.net.URL url = getClass().getResource(filename);
		ImageIcon icon = new ImageIcon(url);
		
		return icon;
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
		private Color veryLightGray = new Color (237, 237, 237); // highlight color
		
		public ImgTextCellRenderer() {
			setOpaque(true);
		}

		public Component getListCellRendererComponent(JList list, Object value,
				int index, boolean isSelected, boolean cellHasFocus) {
			DemoEntry entry = (DemoEntry) value;
			setText(entry.getName());
			setIcon(entry.getScreenshot());

			if (isSelected)
				setBackground(veryLightGray);
			else
				setBackground(Color.white);

			return this;
		}
	}

}
