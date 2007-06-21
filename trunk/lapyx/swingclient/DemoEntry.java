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
		java.net.URL url = getClass().getResource(name + ".gif");
		ImageIcon sweetIcon = new ImageIcon(url);
		
		screenshot = sweetIcon;
    }

	public String getName() {
		return name;
	}

	public Icon getScreenshot() {
		return screenshot;
	}
	
	
	
}