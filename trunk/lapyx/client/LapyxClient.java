/**
 * The LapyxClient can be run on any machine and will connect to the
 * LapyzDaemon (which executes the scripts to start wall apps)
 *
 * @author Kristopher Kalish
 * @version 1 Command Line Edition
 */

import java.util.*;
import java.io.*;
public class LapyxClient
{
	private static final String XML_FILE = "demos.xml";
    private static final String MASTER_NODE = "localhost"; 
	
	/**
	 * main() does everything.  It tells the user his/her choices
	 * then prompts for input and sends it off to the master node.
	 */
	public static void main(String args[])
	{
		Properties wallDemos;
		TCPClient  tcpGuy;
		String     demo;      // demo the user wants to run
		Scanner    keyboard;

		keyboard = new Scanner(System.in);
		// load all of the demos in to the handy hashtable
		wallDemos = loadXML();
		
		System.out.println("Availible demos to run:");
		System.out.println("---------------------------");
		printKeys(wallDemos);	
		System.out.println("---------------------------");

		while(true)
		{
			demo = getInput(keyboard, "Demo");
			try {
				tcpGuy = new TCPClient(MASTER_NODE, demo);
			} catch (IOException ioe) {
				System.out.println("Error opening connection!");
				System.exit(1);
			}
		}

	}

	/**
	 * enumerates a Properties object and prints all of the keys
	 *
	 * @param someProperties A properties object to print
	 */
	public static void printKeys(Properties someProperties)
	{
		Enumeration e = someProperties.propertyNames();
		while (e.hasMoreElements()) {
			System.out.println(e.nextElement());
		}
	}
	/**
	 * gets some input from the user wih the specified prompt
	 *
	 * @return A String grabbed from the keyboard
	 */
	public static String getInput(Scanner keyboard, String prompt)
	{
		String input = "";
		
		// prompt user
		System.out.print(prompt + ": ");
		input = keyboard.next();

		return input;
	}

	/**
	 * loads the properties from the XML file
	 *
	 * @return a populated Properties object
	 */
	public static Properties loadXML()
	{
		Properties      properties = null;
		FileInputStream in = null;
		properties = new Properties();
		try {
			in = new FileInputStream(XML_FILE);
			properties.loadFromXML(in);
		} catch (IOException ioe) {
			System.out.println("Error opening \"" + XML_FILE + "\"!");
			System.exit(1);
		}

		return properties;	
	}
}
