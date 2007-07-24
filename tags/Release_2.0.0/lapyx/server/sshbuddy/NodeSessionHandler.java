package sshbuddy;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

import com.sshtools.j2ssh.SshClient;
import com.sshtools.j2ssh.authentication.SshAuthenticationClient;
import com.sshtools.j2ssh.session.SessionChannelClient;
import com.sshtools.j2ssh.transport.IgnoreHostKeyVerification;

/**
 * This class handles the nitty-gritty sort 
 * of things when connecting to a remote node
 * via SSH. It's given a Node object which 
 * consists of a hostname and a command.  It 
 * then SSHes into that hostname and executes 
 * that given command.  Simple.
 * 
 * @author Kristopher Kalish adapted from code
 * 			by John Magnotti
 *
 */


public class NodeSessionHandler implements Runnable
{
	private SshAuthenticationClient  authClient;
	private Node targetNode;
	
	private int retry_count = 0; //TODO: Do something with this
	
	
	NodeSessionHandler(Node node, SshAuthenticationClient authClient)
	{
		this.targetNode = node;
		this.authClient = authClient;
	}
	
	//@Override
	public void run() {
		SshClient client = new SshClient();
		try {
			System.out.println("Attemping to ssh to " + targetNode.getHostname() + ".\n"
					+ "Sending command \"" + targetNode.getCommand() + "\".");
			client.connect(targetNode.getHostname(), new IgnoreHostKeyVerification());

			int result;  // get's the status of the authentication (unused for now)
			
			result = client.authenticate(authClient);

			/*
			 * if (result == AuthenticationProtocolState.FAILED)
			 * System.out.println("The authentication failed"); if (result ==
			 * AuthenticationProtocolState.PARTIAL) System.out.println("The
			 * authentication succeeded but another" + "authentication is
			 * required"); if (result == AuthenticationProtocolState.COMPLETE)
			 * System.out.println("The authentication is complete");
			 */
			SessionChannelClient session;
			session = client.openSessionChannel();
			session.startShell();

			/** Writing to the session OutputStream 
			 * (Sending the command) */
			OutputStream out = session.getOutputStream();
			out.write(targetNode.getCommand().getBytes());
			out.close();
			
			/**
			 * Reading from the session InputStream
			 * (Printing the results of the command)
			 */
			InputStream in = session.getInputStream();
			BufferedReader reader = new BufferedReader(
					new InputStreamReader(in));
			String line = reader.readLine();
			
			while (line != null) {
				System.out.println(line);
				line = reader.readLine();
			}
			in.close();
			session.close();
			client.disconnect();
		} catch (Exception e) {
			//retry
			if (retry_count < 3){
				retry_count++;
				run();
			}
		}
	}

}
