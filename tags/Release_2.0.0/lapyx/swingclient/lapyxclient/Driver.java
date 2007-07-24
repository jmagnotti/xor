package lapyxclient;
/**
 * This driver does little more than create a LapyxFrame
 * and start it.
 *
 */

import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;


public class Driver {
    
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event dispatch thread.
     */
    private static void createAndShowGUI()
    {
        DemoEntryBuilder builder = new DemoEntryBuilder("demos.xml");
    	NetworkSettings nws = new NetworkSettings("network.cfg");
        
        //Create and set up the window.
    	LapyxFrame lapyxFrame = new LapyxFrame(builder.parseFromXML());
    	

        //Use the content pane's default BorderLayout. No need for
        //setLayout(new BorderLayout());
        //Display the window.
        //lapyxFrame.pack(); // make it a small as possible
        lapyxFrame.setVisible(true);
    }
    
    public static void main(String[] args) {
        /* Use an appropriate Look and Feel */
        try {
            //UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (UnsupportedLookAndFeelException ex) {
            ex.printStackTrace();
        } catch (IllegalAccessException ex) {
            ex.printStackTrace();
        } catch (InstantiationException ex) {
            ex.printStackTrace();
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
        
        //Schedule a job for the event dispatch thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }
}
