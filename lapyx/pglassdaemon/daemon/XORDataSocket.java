package daemon;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

/**
 * The XOR Data Socket is a gateway to the 
 * XOR Multicast data pipeline.  
 * 
 * @author Kristopher Kalish
 *
 */

public class XORDataSocket
{
	private MulticastSocket socket;
	private InetAddress group;
	private String message;
	private DatagramPacket packet;
	
	public final int PORT = 1239;
	public final String ADDRESS = "239.239.239.239";

	public XORDataSocket()
	{
		// join the multicast group
		try {
			socket = new MulticastSocket(PORT);
			group = InetAddress.getByName(ADDRESS);
			socket.joinGroup(group);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/** 
	 * Convenience function for sending bytes
	 * @param data
	 */
	public void sendBytes(byte[] data)
	{
		packet = new DatagramPacket(data, data.length,
				group, PORT);
		
		try {
			socket.send(packet);
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}
	
	/** 
	 * Convenience function for sening Strings
	 * @param data
	 */
	public void sendString(String data)
	{
		packet = new DatagramPacket(data.getBytes(), data.length(),
				group, PORT);
		
		try {
			socket.send(packet);
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}
	
	

}
