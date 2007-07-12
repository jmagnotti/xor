package sshbuddy;



public class LaunchXORDemo implements LapyxCommand
{
	private String command; // the actual command-line command

	public LaunchXORDemo(String command)
	{
		this.command = command;
	}

	@Override
	public void process(CommandSender r)
	{
		r.sendXORCommand(command);
	}

}