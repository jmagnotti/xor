package main;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

public class KeyEventFactory {

	private final Properties bindings;

	public static final int KEY_DOWN = 0;

	public static final int KEY_UP = 1;

	public KeyEventFactory() {
		bindings = new Properties();
		try {
			bindings.load(new FileInputStream(new File("keys")));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public String createKeyString(String key, int state) {

		String mods = "4096";

		if (key.length() == 1 && key.charAt(0) > 'A' && key.charAt(0) < 'Z')
			mods = "1";

		return "" + state + " " + bindings.getProperty(key) + " " + mods + "\n";
	}
}
