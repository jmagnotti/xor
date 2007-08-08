package daemon;

import java.util.Vector;

public class PhotoSender extends XORDataSocket
{
	public PhotoSender()
	{
		super();
	}
	
	public void sendPictures(Vector<FileChunker> pics)
	{
		Integer numpics = pics.size();
		// send the header... number of pics
		sendString(numpics.toString());
		for(int i = 0; i < numpics; i++)
		{
			System.out.println("=========Sending pic " + i + "==============");
			sendPicture(pics.get(i));
			try {
				Thread.sleep(10);
			} catch (InterruptedException ie) {
				// everyting's gonna be alright
			}
		}
		
	}
	
	/**
	 * This function will send the header
	 * and bytes for an image.  Should not
	 * be called by anything other then
	 * sendPictures().
	 *
	 */
	private void sendPicture(FileChunker pic)
	{
		int sent = 0;
	
		// send header
		sendString(pic.getName());
		sendString(pic.getSize() + "");
		
		while(!pic.done())
		{
			byte[] pakdata = pic.getNextChunk();
			sent += pakdata.length;
			System.out.println("Sent " + sent + " bytes so far.");
			
			sendBytes(pakdata);
			
			try {
				Thread.sleep(10);
			} catch (InterruptedException ie) {
				// everyting's gonna be alright
			}
		}
	}

}
