package makehelp;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

/**
 */
public class Source
{
	public static void main(String[] args) throws IOException {
		File headerFile = new File("sourceList.list");
		PrintWriter out = new PrintWriter(headerFile);

		BuildFileList lister = new BuildFileList(
				"./", BuildFileList.CPP);
		
		for (String s : lister.buildSourceList())
			out.write(s + " ");
		
		out.write("\n");
		out.close();
	}
}

