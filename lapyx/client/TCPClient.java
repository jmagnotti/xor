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
    private BufferedReader          in;
    private int                     port = 1908;
    private PrintWriter             out;
    private Socket                  s;


    /**
     * Explicit Value Constructor
	 *
	 * @param host Host to connect to
	 * @param data The string to send
     */
    public TCPClient(String host, String data) throws IOException, 
		                                             SocketException
    {
       String    line;
       
       // Create a connection to a particular host and port
       s   = new Socket(host, port);
       
       // Get an output stream and construct a writer
       out = new PrintWriter(s.getOutputStream());
       
	   // TODO: Have the server send a response if it was successful or
	   // not
       // Get an input stream and construct a reader
       /*
		in  = new BufferedReader(
	    new InputStreamReader(s.getInputStream()));
		*/
              
       // Read and write to the two streams as required
       // by the application

	   // in this case we will just be sending hte data and finishing
       out.println(data);
       out.flush();
       
	   // read the response....
	   /*
       while ( (line=in.readLine()) != null) 
       {
          System.out.println(line);
       }*/
    }
    
}
