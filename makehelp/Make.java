package makehelp;

import java.io.*;

/**
 *
 */
public class Make {

	public static void main(String[] args) throws Exception
    {
		MakefileGenerator generator = MakefileGenerator.GetInstance();
		generator.generateMakefile();

		String command = "make -f " + generator.getMakefileName() + " depend";
		System.out.println(command);

        Process proc = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
        proc.waitFor(); // wait for termination

        while (reader.ready())
            System.out.println(reader.readLine());

        reader.close();

		command = "make -f " + generator.getMakefileName(); 
        proc = Runtime.getRuntime().exec(command);
		System.out.println(command);

        reader = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
        proc.waitFor();
        
        while (reader.ready())
            System.out.println(reader.readLine());

        reader.close();

        if (proc.exitValue() == 0)
            System.out.println("Now run make install as the administrator user");
        else
            System.out.println("Process terminated abnormally. Fix errors, and rerun java makehelp/Make");

	}
}
