/**
 * Simple java program to build an XML properties
 * filexs for the LapyxDaemon.
 */
import java.util.*;
import java.io.*;
public class XMLBuilder 
{	
	// The XML file for LapyxDaemon
	static final String XML_FILE = "demos.xml";
	
	public static void main(String args[])
	{
		Properties propsToWrite = new Properties();
		FileInputStream		in = null;
		FileOutputStream	out = null;
		Scanner             keyboard = new Scanner(System.in);
	

		// Load the existing demos.xml into memory
		// then we'll append to it
		System.out.println("Reading " + XML_FILE + "...");
		try {
			in = new FileInputStream(XML_FILE);
		} catch(IOException ioe) {
			System.out.println("Could not open " + XML_FILE + "!");
			System.exit(1);
		}
		
		// load the values
		try {
		propsToWrite.loadFromXML(in);
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}

		// print what we have
		System.out.println("Keys already in " + XML_FILE + ":");
		Enumeration e = propsToWrite.propertyNames();
		while (e.hasMoreElements()) {
			System.out.println(e.nextElement());
		}
		
		boolean looping = true;

		System.out.println("\nType \"done\" to finish");
		System.out.println("-----------------------");
		while(looping)
		{
			String pair[];
			pair = getInput(keyboard);
			if(pair[0].equals("done") || pair[1].equals("done"))
				looping = false;
			else
				propsToWrite.setProperty(pair[0], pair[1]);
		}
		try {
			out = new FileOutputStream(XML_FILE);
			propsToWrite.storeToXML(out, "Updated with XMLBuilder");
		} catch (IOException ioe) {
			System.out.println("Error writing to " + XML_FILE + "!");
		}
	}

	public static String[] getInput(Scanner keyboard)
	{
		// index 0 is key, index 1 is value
		String keyvalpair[] = new String[2];
		String input = "";         //temp place to store input
		
		System.out.print("New key: ");
		while(input.equals(""))
		{
			input = keyboard.nextLine(); 
		}
		keyvalpair[0] = input;
		input = "";
		System.out.print("Value: ");
		while(input.equals(""))
		{
			input = keyboard.nextLine();
		}
		keyvalpair[1] = input;
		return keyvalpair;
	}
}
