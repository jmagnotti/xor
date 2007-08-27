package daemon;

import java.io.File;
import java.util.Vector;


public class Driver
{
	public static void main(String args[])
	{	
		// load some bogus pictures
		Vector<FileChunker> somepics = new Vector<FileChunker>();
		File pic1 = new File("1.jpg");
		File pic2 = new File("2.jpg");
		File pic3 = new File("3.jpg");
		
		somepics.add(new FileChunker(pic3));
		somepics.add(new FileChunker(pic2));
		somepics.add(new FileChunker(pic1));

		somepics.add(new FileChunker(pic3));
		somepics.add(new FileChunker(pic2));
		somepics.add(new FileChunker(pic1));
		
		somepics.add(new FileChunker(pic3));
		somepics.add(new FileChunker(pic2));
		somepics.add(new FileChunker(pic1));
		
		somepics.add(new FileChunker(pic3));
		somepics.add(new FileChunker(pic2));
		somepics.add(new FileChunker(pic1));
		
		somepics.add(new FileChunker(pic3));
		somepics.add(new FileChunker(pic2));
		somepics.add(new FileChunker(pic1));
		
		PhotoSender ps = new PhotoSender();
		ps.sendPictures(somepics);
		
	}
}
