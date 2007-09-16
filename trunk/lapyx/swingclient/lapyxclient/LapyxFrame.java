package lapyxclient;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.IOException;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.KeyStroke;
import javax.swing.ListCellRenderer;
import javax.swing.border.Border;

/**
 * A LapyxFrame is the MacDaddy of this application. It's a JFrame that contains
 * 
 * @author Kris Kalish
 * 
 */

public class LapyxFrame extends JFrame implements ActionListener, WindowListener {
	
	private JList demoList;
	private JScrollPane scrollableDemoList;
	private NetworkSettings nws;
	private NetworkSettingsFrame nsf;
	
	private TCPClient client; // talks to the server

	/**
	 * The default constructor
	 * 
	 * @param demoEntries
	 */
	LapyxFrame(Vector<DemoEntry> demoEntries) {
		// decorate and modify this window
		super("Lapyx Launcher"); // add title
		setBounds(10, 10, 400, 600); // change size
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // close when
																// done
		this.setResizable(false); // no resizing!!!

		// Load network settings
		nws = new NetworkSettings("network.cfg");
		try {
			nws.loadCFG();
		} catch (IOException ioe) {
			JOptionPane
					.showMessageDialog(
							this,
							"Couldn't find the network config file! Please check network settings.",
							"Could not open configuration file",
							JOptionPane.WARNING_MESSAGE);

		}
		System.out.println("Master host:" + nws.getMasterHost());

		// fill the list up with demos
		populateList(demoEntries);

		addComponentsToPane(this.getContentPane());

		LapyxMouseCommands lmc = new LapyxMouseCommands();
		
		// connect to daemon
		openTCP();
		demoList.addMouseListener(lmc);
	}

	/**
	 * Populates the pane with all kinds of fun Swing object to make it useful.
	 * Thing menu bars...Lists...Logo etc.
	 * 
	 * @param pane
	 *            A pane (usually the content pane) to add everything to
	 */
	public void addComponentsToPane(Container pane) {
		if (!(pane.getLayout() instanceof BorderLayout)) {
			pane.add(new JLabel("Container doesn't use BorderLayout!"));
			return;
		}

		// Create a menu and add some stuff
		JMenuBar menuBar;
		JMenu menu, submenu;
		JMenuItem menuItem;

		// Create the menu bar.
		menuBar = new JMenuBar();

		// Build the first menu.
		menu = new JMenu("Lapyx");
		menu.setMnemonic(KeyEvent.VK_L);
		menuBar.add(menu);

		// a group of JMenuItems
		menuItem = new JMenuItem("Exit", KeyEvent.VK_T);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_1,
				ActionEvent.ALT_MASK));
		menuItem.addActionListener(this);
		menu.add(menuItem);

		// a submenu
		menu.addSeparator();
		submenu = new JMenu("Network");
		submenu.setMnemonic(KeyEvent.VK_N);

		menuItem = new JMenuItem("Master Server");
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_2,
				ActionEvent.ALT_MASK));
		menuItem.addActionListener(this);
		submenu.add(menuItem);
		
		menuItem = new JMenuItem("Reconnect");
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_3,
				ActionEvent.ALT_MASK));
		menuItem.addActionListener(this);
		submenu.add(menuItem);
		
		menuItem = new JMenuItem("Connect");
		menuItem.addActionListener(this);
		submenu.add(menuItem);
		
		menuItem = new JMenuItem("Disconnect");
		menuItem.addActionListener(this);
		submenu.add(menuItem);
		
		menu.add(submenu);

		this.setJMenuBar(menuBar);

		/*
		 * // All of the positions available to me pane.add(button,
		 * BorderLayout.PAGE_START); pane.add(button, BorderLayout.CENTER);
		 * pane.add(button, BorderLayout.LINE_START); pane.add(button,
		 * BorderLayout.PAGE_END); pane.add(button, BorderLayout.LINE_END);
		 */

		Border blackline = BorderFactory.createLineBorder(Color.WHITE, 5);

		demoList.setBorder(blackline);
		scrollableDemoList = new JScrollPane(demoList);

		pane.add(scrollableDemoList, BorderLayout.CENTER);

		// add logo
		pane.add(new JLabel(loadImage("img/logo.png")),
						BorderLayout.PAGE_START);
		// add side
		pane.add(new JLabel(loadImage("img/side.png")), BorderLayout.WEST);

	}

	/**
	 * actionPerformed is used (in this class) to catch mouse clicks on the menu
	 * items.
	 */
	public void actionPerformed(ActionEvent e) {
		String command;
		command = e.getActionCommand();
		System.out.println("Command: " + command);
		if (command.equals("Exit")) {
			this.setVisible(false);
			this.dispose();
		} else if (command.equals("Master Server")) {
			System.out.println("Attempting to open a popup.");
			// make a new frame
			nsf = new NetworkSettingsFrame(nws);
			nsf.setVisible(true);
		} else if (command.equals("Reconnect") || command.equals("Connect")) {
			System.out.println("Reconnecting...");
			if (client != null)
				client.cleanUp();
			openTCP();
		} else if (command.equals("Disconnect")) { 
			if (client != null)
				client.cleanUp();
			client = null;
		}
	}
	
	/**
	 * This is from the WindowListener interface.  It gets
	 * called when dispose is called on this frame.  Here 
	 * we can close our network connection(s).
	 */
	public void windowClosed(WindowEvent e)
	{
		System.out.println("Closing socket connection...");
		client.cleanUp();
	}
	
	/**
	 * Forced on us from the WindowListener interface. Unused.
	 */
	public void windowOpened(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowActivated(WindowEvent e) {}
	public void windowDeactivated(WindowEvent e) {}
	public void windowClosing(WindowEvent e) {
		System.out.println("Closing socket connection...");
		client.cleanUp();
	}
	

	/**
	 * Makes the Swing List object from a vector of demo entries.
	 * 
	 * @param demoEntries
	 *            The demo entries to populate the list
	 */
	private void populateList(Vector<DemoEntry> demoEntries) {
		// Make a new list full of our demos
		demoList = new JList(demoEntries);

		// now take care of some odds and ends
		// first we'll need to use our own rendered to use imgs
		demoList.setCellRenderer(new ImgTextCellRenderer());
		// make each cell 10px taller than our images for padding
		demoList.setFixedCellHeight(138);
	}

	private ImageIcon loadImage(String filename) {
		java.net.URL url = getClass().getResource(filename);
		ImageIcon icon = new ImageIcon(url);

		return icon;
	}
	
	/**
	 * Does the error handling involved with opening a TCP Connection
	 */
	private void openTCP()
	{
		try {
			client = new TCPClient(nws.getMasterHost());
		} catch (IOException ioe) {
			JOptionPane.showMessageDialog(this,
					"Couldn't open a connection to the Lapyx Daemon.\n" +
					"Ensure that it running and check the network \n" +
					"settings.  Attemping to launch demos now will \n" +
					"not work.", "Network Error",
					JOptionPane.WARNING_MESSAGE);
		}

	}

	/** ***************** INNER CLASSES ****************** */

	/**
	 * This mouse listener is and inner class of the LapyxFrame rather than it's
	 * own class in order to have access to the demoList.
	 * 
	 * It takes the text label from the list item double-clicked and creates a
	 * TCP client to send that message.
	 */
	private class LapyxMouseCommands extends MouseAdapter {
		/**
		 * The default constructor... Readies a new TCPClient
		 */
		public LapyxMouseCommands() {
			
		}

		@Override
		public void mouseClicked(MouseEvent e) {
			super.mouseClicked(e);

			if (e.getClickCount() == 2) {
				int index = demoList.locationToIndex(e.getPoint());
				System.out.println("Double clicked on Item " + index);

				DemoEntry something = (DemoEntry) demoList.getSelectedValue();

				System.out.println(something.getName());

				// ensure we even have a channel to send data into
				if (client != null)
					client.sendData(something.getName());
			}
		}
	}

	/**
	 * Since a JList is nothing more than a bunch of JLabels with a renderer,
	 * this class replaces the default so we can add pictures with our text and
	 * even customize the highlight color(s).
	 */
	class ImgTextCellRenderer extends JLabel implements ListCellRenderer {
		// alternating highlight colors
		private final Color VERYLIGHTGREY = new Color(237, 237, 237);
		private final Color VERYLIGHTGREEN = new Color(241, 247, 223);

		/**
		 * This default constructor does nothing more than to set the label to
		 * opaque
		 */
		public ImgTextCellRenderer() {
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
			DemoEntry entry = (DemoEntry) value;
			setText(entry.getName());
			setIcon(entry.getScreenshot());

			// alternate highlight colors, white if not selected
			if (isSelected)
				setBackground(index % 2 == 0 ? VERYLIGHTGREY : VERYLIGHTGREEN);
			else
				setBackground(Color.white);

			return this;
		}
	}
}
