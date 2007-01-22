package makehelp;

import java.io.*;

/**
 * 
 */
public class Make {

	public void run() throws Exception {
		MakefileGenerator generator = MakefileGenerator.GetInstance();
		generator.generateMakefile();

		String command = "make -j2 -f " + generator.getMakefileName() + " depend";
		System.out.println(command);

		Process proc = Runtime.getRuntime().exec(command);

		Slurper err = new Slurper(proc.getErrorStream());
		Slurper in = new Slurper(proc.getInputStream());

		err.start();
		in.start();
		
		proc.waitFor();

		err.stop();
		in.stop();

		command = "make -j2 -f " + generator.getMakefileName();
		System.out.println(command);
		proc = Runtime.getRuntime().exec(command);

		err = new Slurper(proc.getErrorStream());
		in = new Slurper(proc.getInputStream());

		err.start();
		in.start();

		
		try {
			proc.waitFor();
		} catch (InterruptedException ie) {
			// no biggie
		}

		err.stop();
		in.stop();

		if (proc.exitValue() == 0)
			System.out
					.println("Now run make install as the administrator user");
		else
			System.out
					.println("Process terminated abnormally. Fix errors, and rerun java makehelp/Make");

	}

	private final class Slurper implements Runnable {
		private final BufferedReader reader;
		private volatile boolean done, started;

		Slurper(InputStream is) {
			reader = new BufferedReader(new InputStreamReader(is));
			done = started = false;
		}

		public void start() {
			if (!started)
				try {
					new Thread(this).start();
					started = true;
				} catch (Exception e) {
					// no worries
				}
		}

		public void stop() {
			done = true;
		}

		public void run() {

			while (!done) {
				try {
					while (reader.ready()) {
						System.out.println(reader.readLine());
						System.out.flush();
					}
				} catch (IOException ioe) {
					ioe.printStackTrace();
				}
				try {
					Thread.sleep(50L);
				} catch (InterruptedException ie) {
					// no worries
				}
			}

            try {
            // catch any leftover buffer
            while (reader.ready()) {
                System.out.println(reader.readLine());
                System.out.flush();
            }
            } catch (IOException ioe) {
                //nothing
            }

		}
	}

	public static void main(String[] args) throws Exception {
		new Make().run();
	}

}
