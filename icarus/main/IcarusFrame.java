package main;


import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.LayoutManager;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class IcarusFrame extends JFrame {
	private final KeyEventFactory keyFactory;

	private final MouseEventFactory mouseFactory;

	public IcarusFrame() {
		keyFactory = new KeyEventFactory();
		mouseFactory = new MouseEventFactory();
		init();
	}

	/**
	 * Creates a new button for the user interface
	 * 
	 * @param ma
	 *            The MulticastAction that is being performed when the button is
	 *            clicked
	 * @param gridbag
	 *            The GridBagLayout for the button
	 * @param c
	 *            The GridBagConstraints for the button
	 */
	private void makebutton(MulticastAction ma, GridBagLayout gridbag,
			GridBagConstraints c) {
		JButton button = new JButton(ma);
		gridbag.setConstraints(button, c);
		add(button);
	}

	/**
	 * Creates a new button with an icon for the user interface
	 * 
	 * @param ma
	 * @param gridbag
	 * @param c
	 */
	private void makebutton(MulticastAction ma, GridBagLayout gridbag,
			GridBagConstraints c, String iconName) {
		JButton button = new JButton(ma);
		gridbag.setConstraints(button, c);
		add(button);
		ImageIcon icon = new ImageIcon(iconName);
		button.setIcon(icon);
	}

	private void init() {
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();

		setFont(new Font("SansSerif", Font.PLAIN, 14));
		setLayout(gridbag);

		c.fill = GridBagConstraints.BOTH;

		c.weightx = 1.0;

		makebutton(new MulticastAction.KeyboardAction("Keyboard w", keyFactory
				.createKeyString("w", KeyEventFactory.KEY_DOWN)), gridbag, c, "MovU.png");
		makebutton(new MulticastAction.KeyboardAction("Keyboard s", keyFactory
				.createKeyString("s", KeyEventFactory.KEY_DOWN)), gridbag, c, "MovD.png");
		makebutton(new MulticastAction.KeyboardAction("F5", keyFactory
				.createKeyString("f5", KeyEventFactory.KEY_DOWN)), gridbag, c);

		c.weightx = 0;
		c.weighty = 0;
		c.gridx = GridBagConstraints.EAST;

		makebutton(new MulticastAction.KeyboardAction("ESCAPE", keyFactory
				.createKeyString("escape", KeyEventFactory.KEY_DOWN)), gridbag,
				c);

		LayoutManager lm = new LayoutManager() {

			public void addLayoutComponent(String name, Component comp) {
				// TODO Auto-generated method stub
				
			}

			public void layoutContainer(Container parent) {
				// TODO Auto-generated method stub
				
			}

			public Dimension minimumLayoutSize(Container parent) {
				// TODO Auto-generated method stub
				return null;
			}

			public Dimension preferredLayoutSize(Container parent) {
				// TODO Auto-generated method stub
				return null;
			}

			public void removeLayoutComponent(Component comp) {
				// TODO Auto-generated method stub
				
			}
			
		};
		
		makebutton(new MulticastAction.KeyboardAction("Keyboard 3", keyFactory
				.createKeyString("3", KeyEventFactory.KEY_DOWN)), gridbag, c);

		makebutton(new MulticastAction.KeyboardAction("Keyboard d", keyFactory
				.createKeyString("d", KeyEventFactory.KEY_DOWN)), gridbag, c);

		makebutton(new MulticastAction.KeyboardAction("Keyboard up", keyFactory
				.createKeyString("up", KeyEventFactory.KEY_DOWN)), gridbag, c,
				"arrowUp.gif");

		makebutton(new MulticastAction.KeyboardAction("Keyboard down",
				keyFactory.createKeyString("down", KeyEventFactory.KEY_DOWN)),
				gridbag, c, "arrowDown.gif");

		makebutton(new MulticastAction.KeyboardAction("Keyboard right",
				keyFactory.createKeyString("right", KeyEventFactory.KEY_DOWN)),
				gridbag, c, "arrowRight.gif");

		makebutton(new MulticastAction.KeyboardAction("Keyboard left",
				keyFactory.createKeyString("left", KeyEventFactory.KEY_DOWN)),
				gridbag, c, "arrowLeft.gif");

		makebutton(new MulticastAction.KeyboardAction("Keyboard space",
				keyFactory.createKeyString("space", KeyEventFactory.KEY_DOWN)),
				gridbag, c);

		makebutton(
				new MulticastAction.KeyboardAction("Keyboard period",
						keyFactory.createKeyString("period",
								KeyEventFactory.KEY_DOWN)), gridbag, c);

		c.weighty = .1;
		JLabel label = new JLabel();
		gridbag.setConstraints(label, c);
		add(label);
	}
}
