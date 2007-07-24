package main;

import java.awt.event.ActionEvent;
import javax.swing.JTextArea;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

public class MulticastTextArea implements DocumentListener {

	private final KeyEventFactory keyFactory;

	private int index;

	private JTextArea jta;

	public MulticastTextArea(JTextArea text) {
		keyFactory = new KeyEventFactory();
		jta = text;
		jta.getDocument().addDocumentListener(this);
		index = 0;
	}

	/**
	 * Creates a new MulticastAction for each char in t
	 * 
	 * @param t
	 */
	public void fireNotification(String t) {
		for (char c : t.toCharArray()) {
			MulticastAction ma = new MulticastAction.KeyboardAction("ignored",
					keyFactory
							.createKeyString("" + c, KeyEventFactory.KEY_DOWN));
			ma.actionPerformed(new ActionEvent(this, 0, "FIRE"));
		}
	}

	public void changedUpdate(DocumentEvent arg0) {
	}

	/**
	 * Whenever text is entered the new text is sent to fireNotification()
	 * 
	 * @param arg0
	 *            The document that is being changed
	 */
	public void insertUpdate(DocumentEvent arg0) {
		int start = arg0.getOffset();
		int finish = arg0.getLength();

		fireNotification(jta.getText().substring(start, start + finish));
	}

	public void setText(String t) {
		for (char c : t.toCharArray()) {
			MulticastAction ma = new MulticastAction.KeyboardAction("ignored",
					keyFactory
							.createKeyString("" + c, KeyEventFactory.KEY_DOWN));
			ma.actionPerformed(new ActionEvent(null, 0, null));
		}
	}

	public void removeUpdate(DocumentEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
