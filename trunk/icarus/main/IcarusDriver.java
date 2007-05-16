package main;


import javax.swing.JFrame;
import javax.swing.UIManager;

public class IcarusDriver {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		JFrame frame = new IcarusFrame();
		frame.setBounds(20, 20, 600, 480);
		/*
			try {
				UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
			} catch (Exception e) {
			}
		*/
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

	}

}
