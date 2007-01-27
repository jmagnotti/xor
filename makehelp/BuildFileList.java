package makehelp;

import java.io.File;
import java.io.FileFilter;
import java.util.Vector;

/**
 * @author John Magnotti
 * @version 1.0
 */
public final class BuildFileList {
	public final static int CPP = 0;
	public final static int H = 1;

	private class HeaderFileFilter implements FileFilter {
		private final String[] excludeDirs;
		private final String[] excludeFiles;

		public HeaderFileFilter(String[] excludeDirs, String[] excludeFiles) {
			this.excludeDirs = excludeDirs;
			this.excludeFiles = excludeFiles;
		}

		public boolean accept(File arg0) {
			boolean check = true;

			if (arg0.isDirectory())
				for (int i = 0; i < excludeDirs.length && check; i++)
					check = !excludeDirs[i].equalsIgnoreCase(arg0.getName());
			else
				for (int i = 0; i < excludeFiles.length && check; i++)
					check = !excludeFiles[i].equalsIgnoreCase(arg0.getName());

			return check && (arg0.isDirectory() || arg0.getName().endsWith(".h"));
		}

	};

	private class CPPFileFilter implements FileFilter {
		private final String[] excludeDirs;
		private final String[] excludeFiles;

		public CPPFileFilter(String[] excludeDirs, String[] excludeFiles) {
			this.excludeDirs = excludeDirs;
			this.excludeFiles = excludeFiles;
		}

		public boolean accept(File arg0) {
			boolean check = true;

			if (arg0.isDirectory())
				for (int i = 0; i < excludeDirs.length && check; i++)
					check = !excludeDirs[i].equalsIgnoreCase(arg0.getName());
			else
				for (int i = 0; i < excludeFiles.length && check; i++)
					check = !excludeFiles[i].equalsIgnoreCase(arg0.getName());

			return check && (arg0.isDirectory() || arg0.getName().endsWith(".cpp"));
		}

	};

	private final FileFilter filter;

	private final String[] excludeFiles = { "xor.h" };

	private final String[] excludeDirs = { "include", "lib", "bin", "demo",
			"doc", "immerge", "transition", "multicast" };

	private Vector<String> sourceList;

	// use this to strip off extra path chars
	private String pathToDir;

	public BuildFileList(String sourceDir, int type) {
		pathToDir = sourceDir;
		sourceList = new Vector<String>();

		if (type == H)
			filter = new HeaderFileFilter(excludeDirs, excludeFiles);
		else
			filter = new CPPFileFilter(excludeDirs, excludeFiles);
	}

	public Vector<String> buildSourceList() {
		File top = new File(pathToDir);
		pathToDir = top.getAbsolutePath();

		for (File f : top.listFiles(filter))
			buildAndDescend(f);

		return sourceList;
	}

	/**
	 * @param buildFile
	 */
	private void buildAndDescend(File currentFile) {
		if (currentFile.isDirectory()) {
			for (File f : currentFile.listFiles(filter))
				buildAndDescend(f);
		} else {
			String out = currentFile.getAbsolutePath();
			out = out.replaceAll(pathToDir + "/", "");
			sourceList.add(out);
		}
	}

}
