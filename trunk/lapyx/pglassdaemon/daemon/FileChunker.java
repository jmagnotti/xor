package daemon;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;


public class FileChunker {
	private byte[] data;
	private String filename;
	private int size;
	
	// the offset keeps track of where we 
	// left off in reading chunks of the data array.
	private int offset;
	
	public final int CHUNKSIZE = 100;
	
	FileChunker(File file)
	{
		offset = 0;
		// check to make sure the file exists
		// then create the byte array
		if(file.exists()) {
			filename = file.getName();
			FileInputStream fis;
			//debug
			size = (int) file.length();
			System.out.println("Creating new byte array with length of " + file.length()
					+ ".");
			data = new byte[(int) file.length()];
			try {
				fis = new FileInputStream(file);
				// debug
				System.out.println("Populating array...");
				int bytesread = fis.read(data);
				System.out.println("Read " + bytesread + " bytes.");
			} catch (FileNotFoundException fnfe) {
				// should never hit this
			} catch (IOException ioe) {
				System.out.println("Error reading file!");
			}
		} else {
			System.out.println("File does not exist!!!");
		}
	}
	
	byte[] getNextChunk() {
		byte[] chunk;
		int bytestoread;
		
		// check to see if there are 50 bytes remaining
		if(offset + CHUNKSIZE > data.length) {
			// make an array to hold the remainder of data
			chunk = new byte[data.length - offset]; 
			bytestoread = data.length - offset;
		} else {
			chunk = new byte[CHUNKSIZE];
			bytestoread = CHUNKSIZE;
		}
		
		// copy the bits in data to chunk
		// TODO: make this more efficient
		for(int i = 0; i < bytestoread; i++)
			chunk[i] = data[i + offset];
		
		offset += bytestoread;
		
		return chunk;
	}
	
	boolean done() {
		if(offset == data.length)
			return true;
		else
			return false;
	}
	
	void resetChunking() {
		offset = 0;
	}
	
	String getName() {
		return filename;
	}
	
	int getSize() {
		return size;
	}
}
