package lapyxclient;
import javax.swing.Icon;
import javax.swing.ImageIcon;

public class DemoEntry
{
    private  String name;
    private Icon screenshot;
    
    DemoEntry(String name)
    {
        this.name = name;
        
		// Load icon
        screenshot = loadIcon();
    }

	public String getName()
	{
		return name;
	}

	public Icon getScreenshot()
	{
		return screenshot;
	}
	
	/**
	 * 
	 * @return False if no image was loaded.
	 */
	private ImageIcon loadIcon()
	{
		boolean success = true;
		ImageIcon sweetIcon;
		
        //System.out.println("Attempting to open \"" + ("img/"+ name + ".png") + "\".");
		java.net.URL url = getClass().getResource("img/"+ name + ".png");
		
		try {
			sweetIcon = new ImageIcon(url);
			
		} catch (NullPointerException npe) {
			// TODO: How is this done properly?
			// if loading failed, go to default image
			System.out.println("Defauling to no image...");
			url = getClass().getResource("img/noimage.png");
			sweetIcon = new ImageIcon(url);
		}
		
		return sweetIcon;
	}
}