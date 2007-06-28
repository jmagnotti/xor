package main;

import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class IcarusDriver {

	/**
	 * @param args
	 * @throws UnsupportedLookAndFeelException
	 * @throws IllegalAccessException
	 * @throws InstantiationException
	 * @throws ClassNotFoundException
	 */
	public static void main(String[] args) throws ClassNotFoundException,
			InstantiationException, IllegalAccessException,
			UnsupportedLookAndFeelException {
		JFrame frame = new IcarusFrame();
		frame.setBounds(20, 20, 600, 480);

		UIManager.setLookAndFeel(UIManager
				.getCrossPlatformLookAndFeelClassName());
		/*
		 * try {
		 * UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName()); }
		 * catch (Exception e) { }
		 */
		frame.setVisible(true);
		frame.setResizable(false);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	}

}
