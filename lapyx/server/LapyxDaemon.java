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

public class LapyxDaemon
{
	public static final short PORT_NUMBER = 1908;
	public static final String XML_FILE = "demos.xml";
	private boolean keepGoing = true;
	private ServerSocket socket; 
	private Properties programs; // maps program names to script paths
	
	/**
	 * Opens the XML file and reads them from it, then listens
	 * for incomming connections on PORT_NUMBER.
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
			System.out.println("Entering new thread.");
			try {
				BufferedReader reader = new BufferedReader(
				
				// input stream reader will let us grab
				// the data sent over the socket
                new InputStreamReader(socket.getInputStream())); 
				
				// now actually read, and echo
				String str = reader.readLine();
				System.out.println("Received \"" + str+ "\".");

				// look up the command to run for 
				// the given program name
				String program = programs.getProperty(str);
			
				// if searching the hashmap returned a result
				// execute that result
				if (program != null) {
					System.out.println("Will execute " + program + " now.");
					Runtime.getRuntime().exec(program); 
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block 
				e.printStackTrace(); 
			} 

			System.out.println("Leaving thread.");
		} 
    } 
}
