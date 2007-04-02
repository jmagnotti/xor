package main;


import java.awt.event.ActionEvent;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

import javax.swing.AbstractAction;

public abstract class MulticastAction extends AbstractAction {
	private MulticastSocket socket;

	private InetAddress group;

	private String message;

	private final DatagramPacket packet;

	public static final String ADDRESS = "239.239.239.239";

	public static class KeyboardAction extends MulticastAction {
		public KeyboardAction(String name, String message) {
			super(name, message, 1235);
		}
	}

	public static class MouseAction extends MulticastAction {
		public MouseAction(String name, String message) {
			super(name, message, 1234);
		}
	}

	/**
	 * Explicit constructor. Instantiates a new multicast socket. Joins the
	 * multicast group.
	 * 
	 * @param name
	 *            The text of the button
	 * @param message
	 *            The string to be broadcasted to everyone in the group
	 */
	public MulticastAction(String name, String message, int port) {
		//super(name);

		this.message = message;
		try {
			socket = new MulticastSocket(port);
			group = InetAddress.getByName(ADDRESS);
			socket.joinGroup(group);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		packet = new DatagramPacket(message.getBytes(), message.length(),
				group, port);
	}

	/**
	 * Broadcasts message to the group.
	 */
	public void actionPerformed(ActionEvent e) {

		try {
			socket.send(packet);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}
}
