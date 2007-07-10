package server;
/**
 * The LapyxDaemon class is a simple multithreaded server
 * that waits for incomming connections and creates a new
 * thread to handle them.  The nested class ConnectionHandler
 * Will launch an application based on the string it receives
 * 
 * @author Kristopher Kalish
 * @version 1
 *
 */

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;
import sshbuddy.*;

public class LapyxDaemon
{
	public static final short PORT_NUMBER = 1908;
	public static final String XML_FILE = "demos.xml";
	private boolean keepGoing = true;
	private ServerSocket socket; 
	private Properties programs; // maps program names to script paths
	
	/**
	 * Opens the XML file and reads them from it, then listens
	 * for incoming connections on PORT_NUMBER.
	 */
	LapyxDaemon() 
	{
		FileInputStream in = null;

		// read in table 
		System.out.println("Loading demo/script map from XML file...");
		programs = new Properties();

		// attempt to open XML_FILE
		try {
			in = new FileInputStream(XML_FILE);
			programs.loadFromXML(in);
		} catch (IOException ioe) {
			System.out.println(XML_FILE + " not present! Exiting...");
			System.exit(1);
		}

		System.out.println("Opening listening socket...");
		try
		{
			socket = new ServerSocket(PORT_NUMBER); 
		} catch (IOException e) {
				e.printStackTrace(); 
		} 
	} 

    public void start() throws IOException 
	{ 
		while (keepGoing)
		{
			Socket s = socket.accept(); 
			System.out.println("Connection accepted...");
			Thread t = new Thread(new ConnectionHandler(s)); t.start(); 
		} 
    } 

    public void stop() 
	{
        keepGoing = false; 
    } 

    final class ConnectionHandler implements Runnable 
	{ 
		private final Socket socket; 
		
		public ConnectionHandler(Socket socket)
		{
			this.socket = socket; 
		} 

		public void run() 
		{
			// this will be false when 
			boolean sessionRunning = true;
			
			System.out.println("Entering new thread.");
			try {
				BufferedReader reader = new BufferedReader(
				
				// input stream reader will let us grab
				// the data sent over the socket
                new InputStreamReader(socket.getInputStream())); 
				
				while(sessionRunning)
				{
					System.out.println("Attemping to read a line...");
					// now actually read, and echo
					String str = reader.readLine();
					System.out.println("Received \"" + str+ "\".");
					
					if(str != null) {
						// Client wants to disconnect
						if(str.equals("!Exit!")) {
							sessionRunning = false;
						} else {
							// execute the program in str on all nodes via ssh
							sendToAllNodes(str);
						}
					} else {
						System.out.println("Read null from the stream. Socket must" +
								"have been lost.");
						sessionRunning = false;
					}
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block 
				e.printStackTrace(); 
			} 

			System.out.println("Leaving thread.");
		} 
		
		private void sendToAllNodes(String program)
		{
			boolean needOffsets; // is this an XOR launch?
			SSHBuddy ssh; 
			// look up the command to run for 
			// the given program name
			String cmdToSend = programs.getProperty(program);
			
			// if we find the work XOR in the program name we know
			// we have to launch an XOR app.
			needOffsets = program.contains("XOR");
			
			
			// ensure that we actually looked something up
			if (cmdToSend != null) {
				System.out.println("Sending \"" + cmdToSend + "\" now.");
				//try {
					//ssh = new SSHBuddy("wall-node", "display", "/home/display/.ssh/id_rsa");
					ssh = new SSHBuddy("wall-node", "display", "display", true);
					
					if(needOffsets)
						ssh.sendXORCommandToNodes(cmdToSend, 16, 58);
					else
						ssh.sendCommandToNodes(cmdToSend, 16, 58);
				//} catch (IOException ioe) {
				//	System.out.println("Couldn't open the public key file!");
				//}
			}
		}
    } 
}
