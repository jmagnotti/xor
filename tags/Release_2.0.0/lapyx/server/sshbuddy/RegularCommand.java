package sshbuddy;



public class RegularCommand implements LapyxCommand
{
	private String command;
	
	public RegularCommand(String command)
	{
		this.command = command;
	}
	
	//@Override
	public void process(CommandSender r)
	{
		r.sendCommand(command);
	}
}
