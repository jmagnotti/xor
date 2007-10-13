package main;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextArea;
import javax.swing.SpringLayout;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class IcarusFrame extends JFrame {
	private final KeyEventFactory keyFactory;

	private Ticker ticker;

	private JPanel content;

	private SpringLayout layout;

	private int val;

	private final MouseEventFactory mouseFactory;

	public IcarusFrame() {
		keyFactory = new KeyEventFactory();
		mouseFactory = new MouseEventFactory();
		ticker = new Ticker(30);

		// create a thread initialized with out ticker runnable
		Thread t = new Thread(ticker);

		// this will eventually call the run method in Ticker
		t.start();

		init();
	}

	@Deprecated
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
	@Deprecated
	private void makebutton(MulticastAction ma, GridBagLayout gridbag,
			GridBagConstraints c, String iconName) {
		JButton button = new JButton(ma);
		gridbag.setConstraints(button, c);
		add(button);
		ImageIcon icon = new ImageIcon(iconName);
		button.setIcon(icon);
	}

	private JButton makeButton(MulticastAction ma, String iconName) {
		JButton button = new JButton(ma);
		content.add(button);
		ImageIcon icon = new ImageIcon(iconName);
		button.setIcon(icon);
		return button;
	}

	private void gridBagInit() {
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();

		setFont(new Font("SansSerif", Font.PLAIN, 14));
		setLayout(gridbag);

		c.fill = GridBagConstraints.BOTH;

		c.weightx = 1.0;

		makebutton(new MulticastAction.KeyboardAction("Keyboard w", keyFactory
				.createKeyString("w", KeyEventFactory.KEY_DOWN)), gridbag, c,
				"MovU.png");
		makebutton(new MulticastAction.KeyboardAction("Keyboard s", keyFactory
				.createKeyString("s", KeyEventFactory.KEY_DOWN)), gridbag, c,
				"MovD.png");
		makebutton(new MulticastAction.KeyboardAction("F5", keyFactory
				.createKeyString("f5", KeyEventFactory.KEY_DOWN)), gridbag, c);

		c.weightx = 0;
		c.weighty = 0;
		c.gridx = GridBagConstraints.EAST;

		makebutton(new MulticastAction.KeyboardAction("ESCAPE", keyFactory
				.createKeyString("escape", KeyEventFactory.KEY_DOWN)), gridbag,
				c);

		makebutton(new MulticastAction.KeyboardAction("Keyboard 3", keyFactory
				.createKeyString("3", KeyEventFactory.KEY_DOWN)), gridbag, c);

		makebutton(new MulticastAction.KeyboardAction("Keyboard d", keyFactory
				.createKeyString("d", KeyEventFactory.KEY_DOWN)), gridbag, c);

		makebutton(new MulticastAction.KeyboardAction("Keyboard up", keyFactory
				.createKeyString("up", KeyEventFactory.KEY_DOWN)), gridbag, c,
				"MovU.png");

		makebutton(new MulticastAction.KeyboardAction("Keyboard down",
				keyFactory.createKeyString("down", KeyEventFactory.KEY_DOWN)),
				gridbag, c, "MovD.png");

		makebutton(new MulticastAction.KeyboardAction("Keyboard right",
				keyFactory.createKeyString("right", KeyEventFactory.KEY_DOWN)),
				gridbag, c);

		makebutton(new MulticastAction.KeyboardAction("Keyboard left",
				keyFactory.createKeyString("left", KeyEventFactory.KEY_DOWN)),
				gridbag, c);

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

	private void makeTextArea() {
		JTextArea jta = new JTextArea(5, 20);
		MulticastTextArea mta = new MulticastTextArea(jta);
		content.add(jta);
		layout.putConstraint(SpringLayout.EAST, jta, 25, SpringLayout.EAST,
				content);
		layout.putConstraint(SpringLayout.NORTH, jta, 20, SpringLayout.NORTH,
				content);
		jta.setVisible(true);
	}

	/**
	 * Creates a frame slider to control frame rate
	 */
	private void makeFrameSlider() {
		JSlider slider = new JSlider(10, 100);
		slider.setMajorTickSpacing(10);
		slider.setPaintTicks(true);
		slider.setSnapToTicks(true);
		slider.setVisible(true);

		slider.addChangeListener(new ChangeListener() {
			/*
			 * (non-Javadoc)
			 * 
			 * @see javax.swing.event.ChangeListener#stateChanged(javax.swing.event.ChangeEvent)
			 */
			public void stateChanged(ChangeEvent arg0) {
				JSlider source = (JSlider) arg0.getSource();
				if (!source.getValueIsAdjusting()) {
					int interval = 110 - source.getValue();
					ticker.setInterval(interval);
					// pauses ticker if interval is set to 100
					if (ticker.getInterval() == 100)
						ticker.setKeepGoing(false);
					else
						ticker.setKeepGoing(true);
				}
			}
		});

		getContentPane().add(slider, BorderLayout.SOUTH);
		layout.putConstraint(SpringLayout.SOUTH, slider, 50,
				SpringLayout.SOUTH, content);

	}

	/**
	 * Creates a zoom slider to zoom in and out
	 */
	private void makeZoomSlider() {
		JSlider slider = new JSlider(JSlider.VERTICAL, 10, 100, 55);
		slider.setMajorTickSpacing(20);
		slider.setPaintTicks(true);
		slider.setVisible(true);

		val = slider.getValue();
		slider.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent arg0) {
				JSlider source = (JSlider) arg0.getSource();
				if (source.getValueIsAdjusting()) {
					if (source.getValue() > val) {
						MulticastAction ma = new MulticastAction.KeyboardAction(
								"ignored", keyFactory.createKeyString("w",
										KeyEventFactory.KEY_DOWN));
						ma.actionPerformed(new ActionEvent(this, 0, "FIRE"));
					} else if (source.getValue() < val) {
						MulticastAction ma = new MulticastAction.KeyboardAction(
								"ignored", keyFactory.createKeyString("s",
										KeyEventFactory.KEY_DOWN));
						ma.actionPerformed(new ActionEvent(this, 0, "FIRE"));
					}
				}
				val = source.getValue();
			}
		});

		getContentPane().add(slider, BorderLayout.WEST);

	}

	private void init() {

		layout = new SpringLayout();

		content = new JPanel();
		content.setLayout(layout);
		getContentPane().add(content, BorderLayout.CENTER);

		makeTextArea();

		makeFrameSlider();

		makeZoomSlider();

		JButton buttonU = makeButton(new MulticastAction.KeyboardAction(
				"Keyboard w", keyFactory.createKeyString("w",
						KeyEventFactory.KEY_DOWN)), "MovU.png");
		layout.putConstraint(SpringLayout.WEST, buttonU, 250,
				SpringLayout.WEST, content);
		layout.putConstraint(SpringLayout.NORTH, buttonU, 150,
				SpringLayout.NORTH, content);

		JButton buttonD = makeButton(new MulticastAction.KeyboardAction(
				"Keyboard d", keyFactory.createKeyString("s",
						KeyEventFactory.KEY_DOWN)), "MovD.png");
		layout.putConstraint(SpringLayout.NORTH, buttonD, 0,
				SpringLayout.SOUTH, buttonU);
		layout.putConstraint(SpringLayout.WEST, buttonD, 250,
				SpringLayout.WEST, content);

		JButton buttonL = makeButton(new MulticastAction.KeyboardAction(
				"Keyboard l", keyFactory.createKeyString("a",
						KeyEventFactory.KEY_DOWN)), "MovL.png");
		layout.putConstraint(SpringLayout.EAST, buttonL, 0, SpringLayout.WEST,
				buttonD);
		layout.putConstraint(SpringLayout.NORTH, buttonL, 0,
				SpringLayout.SOUTH, buttonU);

		JButton buttonR = makeButton(new MulticastAction.KeyboardAction(
				"Keyboard r", keyFactory.createKeyString("d",
						KeyEventFactory.KEY_DOWN)), "MovR.png");
		layout.putConstraint(SpringLayout.NORTH, buttonR, 0,
				SpringLayout.SOUTH, buttonU);
		layout.putConstraint(SpringLayout.WEST, buttonR, 0, SpringLayout.EAST,
				buttonD);

		JButton buttonRotL = makeButton(new MulticastAction.KeyboardAction(
				"Keyboard e", keyFactory.createKeyString("e",
						KeyEventFactory.KEY_DOWN)), "RotL.png");
		layout.putConstraint(SpringLayout.SOUTH, buttonRotL, 0,
				SpringLayout.NORTH, buttonR);
		layout.putConstraint(SpringLayout.WEST, buttonRotL, 0,
				SpringLayout.EAST, buttonU);

		JButton buttonRotR = makeButton(new MulticastAction.KeyboardAction(
				"Keyboard q", keyFactory.createKeyString("q",
						KeyEventFactory.KEY_DOWN)), "RotR.png");
		layout.putConstraint(SpringLayout.SOUTH, buttonRotR, 0,
				SpringLayout.NORTH, buttonL);
		layout.putConstraint(SpringLayout.EAST, buttonRotR, 0,
				SpringLayout.WEST, buttonU);

		JButton buttonESC = makeButton(new MulticastAction.KeyboardAction(
				"Keyboard escape", keyFactory.createKeyString("escape",
						KeyEventFactory.KEY_UP)), "X.png");

		/*
		 * JButton buttonSpace = makeButton(new MulticastAction.KeyboardAction(
		 * "Keyboard space", keyFactory.createKeyString("space",
		 * KeyEventFactory.KEY_DOWN)), "X.png");
		 * layout.putConstraint(SpringLayout.NORTH, buttonSpace, 0,
		 * SpringLayout.SOUTH, buttonD); layout.putConstraint(SpringLayout.WEST,
		 * buttonSpace, 0, SpringLayout.EAST, buttonL);
		 */
	}

}
