package lapyxclient;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.IOException;

import javax.swing.AbstractButton;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

//import lapyxclient.LapyxFrame.LapyxMouseCommands;

public class NetworkSettingsFrame extends JFrame implements ActionListener {
	private JTextField hostname;

	private JButton update;

	private final NetworkSettings networkSettings;

	private String defaultHost;

	// the string to catch in the action listener
	private final String updateCommand = "update";

	/**
	 * We use a Model View Controller type thing here where we send a reference
	 * to NetworkSettings (Model) to the frame (view) for it to modify.
	 */
	NetworkSettingsFrame(NetworkSettings nws) {
		super("Network Settings"); // title window
		setBounds(10, 10, 300, 120); // big window
		// this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);

		networkSettings = nws; // keep a reference

		// always do this last!
		addComponentsToPane(this.getContentPane());
	}

	public void addComponentsToPane(Container pane) {
		if (!(pane.getLayout() instanceof BorderLayout)) {
			pane.add(new JLabel("Container doesn't use BorderLayout!"));
			return;
		}

		JPanel p = new JPanel();
		p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
		p.setBorder(BorderFactory
				.createTitledBorder("Master Server Hostname/IP"));

		hostname = new JTextField(20);
		hostname.setText(networkSettings.getMasterHost());
		hostname.addActionListener(this);

		update = new JButton("Update");
		update.setVerticalTextPosition(AbstractButton.CENTER);
		update.setMnemonic(KeyEvent.VK_U);
		update.setActionCommand(updateCommand);
		update.addActionListener(this);

		p.add(hostname, BorderLayout.CENTER);
		p.add(update, BorderLayout.LINE_END);

		pane.add(p);
	}

	/**
	 * When an action is fired, this will intercept it and do what's
	 * appropriate.
	 * 
	 * @param e
	 */
	public void actionPerformed(ActionEvent e) {
		String newhostname, command;
		newhostname = hostname.getText();

		command = e.getActionCommand();
		System.out.println("Command called from Network AListener: " + command);

		// we need to update the network settings
		if (updateCommand.equals(e.getActionCommand())
				|| newhostname.equals(e.getActionCommand())) {
			try {
				networkSettings.setMasterHost(newhostname);
				// TODO: let user change port
				networkSettings.setMasterPort(1908);
				networkSettings.saveCFG();
				this.setVisible(false);
				this.dispose();
			} catch (IOException ioe) {
				JOptionPane.showMessageDialog(this,
						"Couldn't write configuration file.", "Error",
						JOptionPane.WARNING_MESSAGE);
			}
		}

	}

}
