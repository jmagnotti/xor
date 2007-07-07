package server;
import java.io.*;


public class LapyxDriver
{
	public static void main(String args[])
	{
		LapyxDaemon daemon = new LapyxDaemon();
		try {
			daemon.start();
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}
}
