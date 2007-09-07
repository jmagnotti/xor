package lapyxclient;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Properties;

public class NetworkSettings
{
	private String     cfgFile;  // where the network settings are stored
	private Properties cfgProps;
	
	private static final String MASTER_HOSTNAME = "MasterHostname";
	private static final String MASTER_PORT = "MasterPort";
	
	NetworkSettings(String cfgFile)
	{
		this.cfgFile = cfgFile;
		cfgProps = new Properties();
	}
	
	public void setMasterHost(String hostname)
	{
		cfgProps.setProperty(MASTER_HOSTNAME, hostname);
	}
	
	public void setMasterPort(int portNum)
	{
		cfgProps.setProperty(MASTER_PORT, Integer.toString(portNum));
	}
	
	public String getMasterHost()
	{
		return cfgProps.getProperty(MASTER_HOSTNAME, "Host not found!");
	}
	
	public int getMasterPort()
	{
		return Integer.parseInt(cfgProps.getProperty(MASTER_PORT));
	}
	
	
	/**
	 * loads the properties from the CFG file
	 *
	 * @return a populated Properties object
	 */
	public void loadCFG() throws IOException
	{
		FileInputStream in = null;
		
		in = new FileInputStream(cfgFile);
		cfgProps.load(in);
		in.close();
	}
	
	/**
	 * saves the properties to a cfg file
	 */
	public void saveCFG() throws IOException
	{
		// DEBUG
		System.out.println("Writing cfg file:");
		printCFG();
		
		FileOutputStream out = new FileOutputStream(cfgFile);
		cfgProps.store(out, "Updated with Lapyx Client");
		out.flush();
		out.close();
	}
	
	/**
	 * This private method enumerates the Properties and
	 * prints them.  It's used for degbugging.
	 *
	 */
	private void printCFG()
	{
		Enumeration e = cfgProps.propertyNames();
		while (e.hasMoreElements()) {
			String propName = e.nextElement().toString();
			System.out.println(propName+ " : " + cfgProps.getProperty(propName));
		}
	}
}