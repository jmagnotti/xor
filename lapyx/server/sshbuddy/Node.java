package sshbuddy;

/**
 * Node might be a bad name for this object, as it 
 * is primarily a struct type of thing to couple
 * a hostname with a command to execute on that node.
 * 
 * @author kris
 *
 */

public class Node
{
	private String hostname;
	private String command; // command to send to the node
	
	Node(String hostname, String command)
	{
		this.command  = command;
		this.hostname = hostname;
	}
	
	public String getHostname()
	{
		return hostname;
	}
	
	public String getCommand()
	{
		return command;
	}
	
	/*
	 * TODO: Make each node calculate its own offset?
	 */
}
