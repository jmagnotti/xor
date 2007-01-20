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

        Process proc = Runtime.getRuntime().exec(
                "make -f " + generator.getMakefileName() + " depend");
        BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
        proc.waitFor(); // wait for termination

        while (reader.ready())
            System.out.println(reader.readLine());

        reader.close();

        proc = Runtime.getRuntime().exec(
               "make -f " + generator.getMakefileName()); 

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
