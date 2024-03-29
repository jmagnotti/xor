package makehelp;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

/**
 */
public class XOR_H
{
	public static void main(String[] args) throws Exception {
		File headerFile = new File("xor.h");
		PrintWriter out = new PrintWriter(headerFile);

		out.write("#ifndef XOR_H\n");
		out.write("#define XOR_H\n\n");

		BuildFileList lister = new BuildFileList("./src/", BuildFileList.H);
		
		for (String s : lister.buildSourceList())
			out.write("#include \"" + s + "\"\n");

		out.write("\n#endif\t\t\t// XOR_H\n\n");
		
		out.close();

        Process proc = Runtime.getRuntime().exec("mv xor.h src/");
        proc.waitFor();
	}
}

