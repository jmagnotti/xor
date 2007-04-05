package main;

import java.awt.event.ActionEvent;

import javax.swing.JTextArea;
import javax.swing.text.Document;

public class MulticastTextArea extends JTextArea {

	private final KeyEventFactory keyFactory;

	public MulticastTextArea() {
		super();
		keyFactory = new KeyEventFactory();
	}

	public MulticastTextArea(String arg0) {
		super(arg0);
		keyFactory = new KeyEventFactory();
	}

	public MulticastTextArea(Document arg0) {
		super(arg0);
		keyFactory = new KeyEventFactory();
	}

	public MulticastTextArea(int arg0, int arg1) {
		super(arg0, arg1);
		keyFactory = new KeyEventFactory();
	}

	public MulticastTextArea(String arg0, int arg1, int arg2) {
		super(arg0, arg1, arg2);
		keyFactory = new KeyEventFactory();
	}

	public MulticastTextArea(Document arg0, String arg1, int arg2, int arg3) {
		super(arg0, arg1, arg2, arg3);
		keyFactory = new KeyEventFactory();
	}

	@Override
	public void setText(String t) {
		super.setText(t);
		for (char c : t.toCharArray()) {
			MulticastAction ma = new MulticastAction.KeyboardAction("ignored",
					keyFactory
							.createKeyString("" + c, KeyEventFactory.KEY_DOWN));
			ma.actionPerformed(new ActionEvent(null, 0, null));
		}
	}
}
