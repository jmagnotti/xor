package sshbuddy;

import java.io.File;
import java.io.IOException;
import java.util.Vector;

import com.sshtools.j2ssh.authentication.SshAuthenticationClient;
import com.sshtools.j2ssh.authentication.PasswordAuthenticationClient;
import com.sshtools.j2ssh.authentication.PublicKeyAuthenticationClient;
import com.sshtools.j2ssh.transport.publickey.SshPrivateKeyFile;

/**
 * SSHBuddy is a very easy to use front end for SSH. 
 * It's designed to send commands to lots of well-named
 * nodes. It takes care of figuring out authentication
 * and lets the NodeSessionHandlers loose with it.
 * 
 * @author Kris Kalish (adapted from code by John Magnotti)
 *
 */

public class SSHBuddy
{
	private SshAuthenticationClient authClient;
	private String					baseHostname;
	/**
	 * Using this constructor will connect to nodes using 
	 * a username and password.
	 * 
	 * @param username
	 * @param password
	 */
	public SSHBuddy(String baseHostname, String username, String password, boolean pass)
	{
		this.baseHostname = baseHostname;
		// pwc lets us authenticate later with a password
		PasswordAuthenticationClient pwc = new PasswordAuthenticationClient();
		pwc.setUsername(username);
		pwc.setPassword(password);
		
		// now "cast" it to our more abstract type so we can hand it off later
		authClient = pwc;
	}
	
	/**
	 * This constructor will connect to nodes using a public key. 
	 * 
	 * @param pathToKey path to the key file (can be absolute or relative)
	 */
	public SSHBuddy(String hostname, String username, String pathToKey) throws IOException
	{
		this.baseHostname = hostname;
		// load the private key file, should have no keyword
		SshPrivateKeyFile file =
			SshPrivateKeyFile.parse(new File(pathToKey));
	    PublicKeyAuthenticationClient pk = new PublicKeyAuthenticationClient();
	    pk.setUsername(username);
	    pk.setKey(file.toPrivateKey(null));
	    
	    authClient = pk;
	}
	
	/**
	 * This is a highly specialized method.  It's designed to start XOR apps on 
	 * remote machines via SSH.  It calculates node offsets and passes them as
	 * parameters in additon to the baseXORCmd that is passed in.
	 * 
	 * @param baseXORCmd The command used to start the XOR app without offsets
	 * @param loRange The beginning of the range of nodes to start this on
	 * @param hiRange The high end of the range to start the demo on
	 */
	public void sendCommandToNodes(String baseXORCmd, int loRange, int hiRange)
	{
		Vector<Node> nodes; // some place to store all of our nodes
		
		// generate hostname to XOR offset relationship
		NodeGenerator nodeGen = new NodeGenerator(baseHostname, 
				loRange, hiRange, baseXORCmd);
		
		nodes = nodeGen.generateWallNodes();
		
		// start a new thread to ssh into each node and execute that command
		for(int i = 0; i < nodes.size(); i++)
		{
			Thread t = new Thread(
					new NodeSessionHandler(nodes.elementAt(i), authClient));
			t.start();
		}
	}

}
