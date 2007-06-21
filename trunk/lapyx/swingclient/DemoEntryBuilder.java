import java.io.FileInputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Properties;
import java.util.Vector;

/**
 * 
 * @author Kris Kalish
 *
 */



public class DemoEntryBuilder
{
	private String filename;
	/**
	 * Explicit constructor... Must always specify a filename
	 * @param filename
	 */
	DemoEntryBuilder(String filename)
	{
		this.filename = filename;
	}
	
	public Vector<DemoEntry> parseFromXML()
	{
		// Vector to return
		Vector<DemoEntry> demoEntries = new Vector<DemoEntry>();
		// A properties object to build the vector from
		Properties props;
		
		props = loadXMLtoProperties();
		
		Enumeration e = props.propertyNames();
		while (e.hasMoreElements()) {
			String current = e.nextElement().toString();
			demoEntries.add(new DemoEntry(current));
			System.out.println(current + " added to vector.");
		}
		
		return demoEntries;
	}
	
	/**
	 * loads the properties from the XML file
	 *
	 * @return a populated Properties object
	 */
	private Properties loadXMLtoProperties()
	{
		Properties      properties = null;
		FileInputStream in = null;
		properties = new Properties();
		try {
			in = new FileInputStream(filename);
			properties.loadFromXML(in);
		} catch (IOException ioe) {
			System.out.println("Error opening \"" + filename + "\"!");
			System.exit(1);
		}

		return properties;	
	}

}
