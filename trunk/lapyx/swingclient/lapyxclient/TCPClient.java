package lapyxclient;
/**
 * A simple TCP client adapted from David Bernstein.
 *
 * @author Kristopher Kalish
 * @version 1
 *
 */

import java.io.*;
import java.net.*;

public class TCPClient
{
    //private BufferedReader          in;
    private int                     port = 1908;
    private PrintWriter             out;
    private Socket                  s;
    private String                  host;
    private boolean                 open;


    /**
     * Explicit Value Constructor
	 *
	 * @param host Host to connect to
	 * @param data The string to send
     */
    public TCPClient(String host)
    {
    	this.host = host;
    	openConnection();
       
	   // TODO: Have the server send a response if it was successful or
	   // not
       // Get an input stream and construct a reader
       /*
		in  = new BufferedReader(
	    new InputStreamReader(s.getInputStream()));
		*/
              
       
	   // read the response....
	   /*
       while ( (line=in.readLine()) != null) 
       {
          System.out.println(line);
       }*/
	   
    }

	public void sendData(String data)
	{
		// there no point sending data if the connection never opened
		if(s.isConnected())
		{
			// Send the data
		 	out.println(data);
		 	out.flush();
		 	// Dump some console output
		 	// DEBUG
		 	System.out.println("Sent: " + data);
		 	
		 	cleanUp();
		}
	}
	
	/**
	 * Open up a new connection
	 */
	public void openConnection()
	{
		try {
			// open connection to predetermined host and port
			s = new Socket(host, port); 
			// give us a way to throw data at the connection
			out = new PrintWriter(s.getOutputStream());
		} catch (IOException ioe) {
			System.out.println("Error opening socket!");
		}
	}
	
	/**
	 * Safely closes our socket
	 */
	private void cleanUp()
	{
		try {
			// ensure it hasn't been closed already
			if(!s.isClosed())
			{
				s.close();
			}
		} catch (IOException ioe) {
			System.out.println("Error closing socket!");
		}
	}
}
