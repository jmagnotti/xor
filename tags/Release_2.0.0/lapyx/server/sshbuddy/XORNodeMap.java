package sshbuddy;

import java.util.Hashtable;

/**
 * The XORNodeMap pairs hostnames to XOR wall offsets.
 * It is a singleton because the offsets should not change.
 * 
 * @author kris
 *
 */

public class XORNodeMap
{
	// The reference to this singleton
	private static XORNodeMap ref;
	
	private static Hashtable<Integer, String> nodeToOffset;
	
	private XORNodeMap()
	{
		nodeToOffset = new Hashtable<Integer, String>();
		generateWingMap(); // may want a different map later
	}
	
	/**
	 * Gets XOR offsets in string format for the 
	 * node number specified.
	 * 
	 * @param nodeNumber
	 * @return The offset in String format. "<col> <row>"
	 */
	public static String getOffset(int nodeNumber)
	{
		return nodeToOffset.get(nodeNumber);
	}
	
	/**
	 * Generates the node number to wall offset map
	 * for the JMU video wall in the wing formation.
	 * that is:
	 * 
	 * 3x3 Lwing - 5x5 center - 3x3 Rwing
	 */
	private void generateWingMap()
	{
		// the 5x5 consists of nodes 25-49
		for(int i = 25; i <= 49; i++) 
		{
			// calculate XOR offset for these nodes
			int colOffset = (i - 25) / 5 - 2;
			int rowOffset = -1 * ((i -25) % 5 - 2);
			nodeToOffset.put(i, colOffset + " " + rowOffset);
		}
		
		// now do the left wing (nodes 16-24)
		for(int i = 16; i <= 24; i++)
		{
			// calculate XOR offset for these nodes
			int colOffset = -1 * ((16 - i) / 3 + 2) - 3;
			int rowOffset = -1 * ((i - 16) % 3 - 1);
			nodeToOffset.put(i, colOffset + " " + rowOffset);
		}
		
		// now do the right wing (nodes 50-58)
		for(int i = 50; i <= 58; i++)
		{
			// calculate XOR offset for these nodes
			int colOffset = (i - 50) / 3 + 3;
			int rowOffset = -1 * ((i - 50) % 3 - 1);
			nodeToOffset.put(i, colOffset + " " + rowOffset);
		}
	}
	
	public static XORNodeMap getInstance()
	{
		// only instantiate if there is no instance yet
		if (ref == null)
			ref = new XORNodeMap();
		return ref;
	}

	/**
	 * Prevent cloning of this object.
	 */
	@Override
	public Object clone() throws CloneNotSupportedException
	{
		throw new CloneNotSupportedException(); 
	}
}