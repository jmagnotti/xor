package server;

import java.util.Hashtable;

import sshbuddy.CommandSender;
import sshbuddy.LapyxCommand;

import com.sshtools.j2ssh.authentication.PasswordAuthenticationClient;
import com.sshtools.j2ssh.authentication.SshAuthenticationClient;

public class NodeConnectionManager
{
	private Hashtable<Integer, CommandSender> threads;
	private int loRange;
	private int hiRange;
	
	private SshAuthenticationClient authClient;
		
	public NodeConnectionManager(String baseHostname, int loRange, 
			int hiRange, String username, String password)
	{
		setRange(loRange, hiRange);
		threads = new Hashtable<Integer, CommandSender>();
		
		// pwc lets us authenticate later with a password
		PasswordAuthenticationClient pwc = new PasswordAuthenticationClient();
		pwc.setUsername(username);
		pwc.setPassword(password);
		
		// now "cast" it to our more abstract type so we can hand it off later
		authClient = pwc;
		
		startThreads(baseHostname);
	}
	
	public void setRange(int loRange, int hiRange)
	{
		if(loRange <= hiRange && loRange >= 0) {
			this.loRange = loRange;
			this.hiRange = hiRange;
		}
	}
	
	public CommandSender getCommandSender(int nodeNum)
	{
		if(nodeNum <= hiRange && nodeNum >= loRange)
			return threads.get(nodeNum);
		else
			return null;
	}
	
	public void sendToNodes(LapyxCommand lc, int loRange, int hiRange)
	{
		if(loRange >= this.loRange && hiRange <= this.hiRange)
		{
			for(int i = loRange; i <= hiRange; i++)
				threads.get(i).addCommand(lc);
				//lc.process(getCommandSender(i));
		}
		else
		{
			System.out.println("Cannot send to nodes, invalid range!");
		}
	}
	
	private void startThreads(String baseHostname)
	{
		for(int i = loRange; i <= hiRange; i++)
		{
			CommandSender cs = new CommandSender(baseHostname + " " + i,
					i, authClient);
			threads.put(i, cs);
			
			System.out.println("Starting thread for node " + i + ".");
			Thread t = new Thread(cs);
			t.start();
		}
	}	
}
