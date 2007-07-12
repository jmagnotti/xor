package sshbuddy;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;

import com.sshtools.j2ssh.SshClient;
import com.sshtools.j2ssh.authentication.SshAuthenticationClient;
import com.sshtools.j2ssh.session.SessionChannelClient;
import com.sshtools.j2ssh.transport.IgnoreHostKeyVerification;



public class CommandSender implements Runnable
{
	private ArrayList<LapyxCommand> commands;
	private volatile boolean done;
	private final XORNodeMap map; // nodeNum to XOR offset
	private final String host;
	private final int    nodeNum; // place in wall
	
	// SSH tools
	private SshClient 			 client;
	private SessionChannelClient session;
	private OutputStream 		 out;
	private InputStream 		 in;
	private BufferedReader 		 reader;
	private int                  retry_count;

	
	/**
	 * Just for shorthanding.  Should never be called remotely 
	 * because this thread is useless without an auth client.
	 */
	protected CommandSender(String host, int nodeNum) {
		map = XORNodeMap.getInstance();
		this.host 	 = host;
		this.nodeNum = nodeNum;
		retry_count = 0;
	}
	
	public CommandSender(String host, int nodeNum, 
			SshAuthenticationClient authClient)
	{
		this(host, nodeNum); // copy values
		
		// open ssh session
		openConnection(authClient);
		
		
	}
	
	private void openConnection(SshAuthenticationClient authClient)
	{
		client = new SshClient();
		try {
			System.out.println("Attemping to ssh to " + host + ".");
			client.connect(host, new IgnoreHostKeyVerification());

			int result;  // get's the status of the authentication (unused for now)
			
			result = client.authenticate(authClient);

			/* if (result == AuthenticationProtocolState.FAILED)
			 * System.out.println("The authentication failed"); if (result ==
			 * AuthenticationProtocolState.PARTIAL) System.out.println("The
			 * authentication succeeded but another" + "authentication is
			 * required"); if (result == AuthenticationProtocolState.COMPLETE)
			 * System.out.println("The authentication is complete");
			 */
			
			SessionChannelClient session;
			session = client.openSessionChannel();
			session.startShell();

			// Create an output stream to write bytes to (send commands)
			OutputStream out = session.getOutputStream();

			// Make an input stream so we can read responses 
			// This isn't completely necessary.
			in = session.getInputStream();
			reader = new BufferedReader(new InputStreamReader(in));
			
			retry_count = 0; // reset if it worked
		} catch (Exception e) {
			//retry 3 times
			if (retry_count < 3){
				retry_count++;
				openConnection(authClient);
			}
		}
		
		
	}
	
	private void closeConnection()
	{
		System.out.println("Closing connection to " + host + ".");
		try {
			in.close();
			out.close();
			session.close();
		} catch (IOException ioe) {
			// Who cares?
		}
		client.disconnect();
	}

	public void sendXORCommand(String msg)
	{
		sendCommand(msg + map.getOffset(nodeNum));
	}

	public void sendCommand(String string)
	{
		try {
			out.write(string.getBytes());
			
			// read response
			String line = reader.readLine();
			
			while (line != null) {
				System.out.println(line);
				line = reader.readLine();
			}
			
			retry_count = 0; // reset retry count
			
		} catch (IOException ioe) {
			System.out.println("Failed to send... retrying...");
			// retry three times
			if (retry_count < 3){
				retry_count++;
				sendCommand(string);
			}
			
		}
	}

	public void addCommand(LapyxCommand com) {
		commands.add(com);
	}

	public void clearCommands() {
		commands.clear();
	}

	public synchronized void stop() {
		done = true;
	}

	public synchronized boolean isDone() {
		return done;
	}

	@Override
	public void run() {
		while (!isDone()) {
			if (!commands.isEmpty()) {
				for (LapyxCommand lc : commands)
					lc.process(this);
			}

			try {
				Thread.sleep(10L);
			} catch (InterruptedException ie) {
				// no worries
			}
		}
		
		closeConnection();
	}
}