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
     */
    public TCPClient(String host) throws IOException
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
		}
	}
	
	/**
	 * Open up a new connection
	 */
	public void openConnection() throws IOException
	{
		// open connection to predetermined host and port
		s = new Socket(host, port); 
		// give us a way to throw data at the connection
		out = new PrintWriter(s.getOutputStream());
	}
	
	/**
	 * Safely closes our socket
	 */
	public void cleanUp()
	{
		try {
			// ensure it hasn't been closed already
			if(!s.isClosed())
			{
				sendData("!Exit!"); // tell daemon we're leaving
				s.close();
			}
		} catch (IOException ioe) {
			System.out.println("Error closing socket!");
		}
	}
}
