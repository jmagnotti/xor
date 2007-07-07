package sshbuddy;

import java.util.Vector;

/**
 * This will produce a vectors of Nodes in
 * various configurations.  Currently it 
 * will only produce XOR start commands 
 * for a given range on the wall.
 * 
 * @author Kristopher Kalish
 *
 */

public class NodeGenerator
{
	private String baseHostname;
	private String baseXorCMD;
	private int loRange, hiRange;
	/**
	 * 
	 * @param baseHostname
	 * @param lowRange
	 * @param highRange
	 * @param baseXorCMD
	 */
	NodeGenerator(String baseHostname, int lowRange, int highRange, String baseXorCMD)
	{
		this.loRange = lowRange;
		this.hiRange = highRange;
		this.baseHostname = baseHostname;
		this.baseXorCMD = baseXorCMD;
	}
	
	/**
	 * This one defaults to running photoalbum
	 * @param baseHostname
	 * @param lowRange
	 * @param highRange
	 */
	NodeGenerator(String baseHostname, int lowRange, int highRange)
	{
		this(baseHostname, lowRange, highRange, 
				"export DISPLAY=:0 && " +
				"cd /home/display/master2/xor/src/demo/photoalbum && " +
				"./PhotoAlbum ");
	}
	
	
	
	/**
	 * This function is specific to JMU's video wall in the
	 * "wing formations, modify, as necessary.
	 * 
	 * @return A vector of Nodes (hostname/command)
	 */
	public Vector<Node> generateWallNodes()
	{
		Vector<Node> nodes; 
		nodes = new Vector<Node>();
		
		// First we'll generate the 5x5 nodes since we want
		// to see those first.
		
		// the 5x5 consists of nodes 25-49
		for(int i = 25; i < 49; i++) 
		{
			if(i >= loRange && i <= hiRange)
			{
				// calculate XOR offset for these nodes
				int colOffset = (i - 25) % 5 - 2;
				int rowOffset = -1 * ((i -25) % 5 - 2);
				
				
				String cmd = baseXorCMD + rowOffset + " " + colOffset;
				
				Node newNode = new Node(baseHostname + i, cmd);
				nodes.add(newNode);
			}
		}
		
		// now do the left wing (nodes 16-23)
		for(int i = 16; i < 23; i++)
		{
			if(i >= loRange && i <= hiRange)
			{
				// calculate XOR offset for these nodes
				int colOffset = -1 * ((16 - i) % 3 + 2) - 3;
				int rowOffset = (i - 16) % 3 - 1;
				
				
				String cmd = baseXorCMD + rowOffset + " " + colOffset;
				
				Node newNode = new Node(baseHostname + i, cmd);
				nodes.add(newNode);
			}
		}
		
		// now do the right wing (nodes 50-58)
		for(int i = 50; i < 58; i++)
		{
			if(i >= loRange && i <= hiRange)
			{
				// calculate XOR offset for these nodes
				int colOffset = (i - 50) % 3 + 3;
				int rowOffset = -1 * ((i - 50) % 3 - 1);
				
				String cmd = baseXorCMD + rowOffset + " " + colOffset;
				
				Node newNode = new Node(baseHostname + i, cmd);
				nodes.add(newNode);
			}
		}

		return nodes;
	}
}
