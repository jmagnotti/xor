package makehelp;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public abstract class MakefileGenerator 
{

	private static File makefile;
	private static BuildFileList fileLister;

	public MakefileGenerator() {
		fileLister = new BuildFileList("./", BuildFileList.CPP);
	}


    public String getMakefileName()
    {
        if (makefile != null)
            return makefile.getName(); 
        else
            return "";
    }


	public abstract File generateMakefile();


    /**
     * Return the appropriate inner class
     */
    public static MakefileGenerator GetInstance()
    {
		if ("Mac OS X".equals(System.getProperty("os.name")))
			return new MacGenerator();
		else if ("Linux".equals(System.getProperty("os.name")))
			return new UnixGenerator();
		else
			return new MinGWGenerator();
    }

	protected void generateMakefileBody(PrintWriter pout) {
		pout.write("#\n# The following part of the makefile is "
				+ "generic; it can be used to\n");
		pout.write("# build any executable just by changing "
				+ "the definitions above and by\n");
		pout.write("# deleting dependencies appended to "
				+ "the file from 'make depend'\n");
		pout.write("#\n\n");

		pout.write("all:\t\t$(MAIN)\n");
		pout.write("\t\t\tcp -f $(MAIN) ./lib/$(MAIN)\n\n");

		pout.write("install:\t$(SPECIAL)\n");
		pout.write("\t\t\tcp -f ./lib/$(MAIN) $(LIBDIR)/$(MAIN)\n\n");

		pout.write("$(MAIN):\t$(OBJS)\n");
		pout.write("\t\t\t$(CC) $(LFLAGS) -o $(MAIN) $(OBJS) $(LIBS)\n\n");

		pout.write(".cpp.o:\n");
		pout.write("\t\t\t$(CC) $(CFLAGS) -o $@ -c $<\n\n");

		pout.write("clean:\n");
		pout.write("\t\t\t$(RM) $(OBJS) $(MAIN)\n\n");

		pout.write("depend:\t\t$(SRCS)\n");
		pout.write("\t\t\t$(MKDP) -f$(MAKEFILE) 2> "
				+ "/dev/null $(INCLUDES) $^\n\n\n");

		pout.write("# DO NOT DELETE THIS LINE -- make depend needs it\n");
	}

	public static final class MacGenerator extends MakefileGenerator {

        public MacGenerator()
        {
            super();
        }

		public File generateMakefile() {
			makefile = new File("Makefile");

			try {
				PrintWriter out = new PrintWriter(makefile);

				out.write("# Makefile for the macintosh\n");
				out.write("# This file was autogenerated using "
						+ "java GenerateMakefile\n");
				out.write("MAKEFILE = Makefile.osx\n\n");
				out.write("# Change the location of makedepend "
						+ "with this line, then comment out "
						+ "the following definition.\n");
				out.write("#MKDP = /usr/X11R6/bin/makedepend\n");
				out.write("MKDP = makedepend\n");
				out.write("CC = g++\n");
				out.write("LFLAGS = -dynamiclib\n");
				out.write("LIBS = -framework OpenGL -lSDL -lSDL_image -lm\n\n");
				out
						.write("# Notice that libdir does not specify the ending /\n");
				out.write("LIBDIR = /usr/local/lib\n");
				out.write("\n");
				out.write("#Packages\n");
				out.write("SRCS = ");

				// use the source builder to aggregate all the source files
				for (String s : fileLister.buildSourceList())
					out.write(s + " ");
				out.write("\n\n");

				out.write("OBJS = $(SRCS:.cpp=.o)\n\n");
				out.write("MAIN = libXOR.so\n\n");
				out.write(".PHONY: FIRST depend clean\n\n");

				out.write("# Since we are using an extra rule, "
						+ "we need to make sure that default"
						+ "\n# processing goes to the all target first.\n");
				out.write("FIRST: all\n\n");

				// for macintosh we need both libXOR.dylib & libXOR.so. make use
				// of the SPECIAL macro
				out
						.write("# The install target will depend on SPECIAL, which means "
								+ "that\n# this target will acutally execute first.\n# Because "
								+ "we are just symlinking, that won't cause any problems.\n");
				out.write("SPECIAL = libXOR.dylib\n\n");
				out.write("$(SPECIAL):\t\n");
				out
						.write("\t\t\tln -fs $(LIBDIR)/$(MAIN) $(LIBDIR)/$(SPECIAL)\n\n");

				// delegate the rest to the parent
				generateMakefileBody(out);

				out.write("\n");
				out.close();

			} catch (FileNotFoundException e) {
				throw new RuntimeException(e);
			}

			return makefile;
		}
	}

	public static final class MinGWGenerator extends MakefileGenerator {

        public MinGWGenerator()
        {
            super();
        }


		public File generateMakefile() {
			makefile = new File("Makefile.mingw.test");

			try {
				PrintWriter out = new PrintWriter(makefile);

				out.write("#Makefile for windows using MinGW\n");
				out.write("#This file was autogenerated using "
						+ "java GenerateMakefile\n");
				out.write("MAKEFILE = Makefile.mingw\n\n");
				out.write("CC = g++\n");
				out.write("LFLAGS = -dynamiclib\n");
				out.write("LIBS = -framework OpenGL -lSDL -lSDL_image -lm\n");
				out
						.write("#Notice that libs dir does not specify the ending /\n");
				out.write("LIBDIR = /usr/local/lib\n");
				out.write("\n");
				out.write("#Packages\n");
				out.write("SRCS = ");

				// use the source builder to aggregate all the source files
				for (String s : fileLister.buildSourceList())
					out.write(s + " ");

				out.write("\n\n");
				out.write("OBJS = $(SRCS:.cpp=.o)\n");
				out.write("\n");
				out.write("MAIN = libXOR.so\n");
				out.write("\n");

				// delegate the rest to the parent
				generateMakefileBody(out);

				out.write("\n");
				out.close();

			} catch (FileNotFoundException e) {
				throw new RuntimeException(e);
			}

			return makefile;
		}

	}

	public static final class UnixGenerator extends MakefileGenerator {

        public UnixGenerator()
        {
            super();
        }


		public File generateMakefile() {
			makefile = new File("Makefile.unix");

			try {
				PrintWriter out = new PrintWriter(makefile);

				out.write("#Makefile for linux using gcc\n");
				out.write("#This file was autogenerated using "
						+ "java GenerateMakefile\n");
				out.write("MAKEFILE = Makefile.unix\n");
				out.write("MKDP = makedepend\n\n");
				out.write("CC = g++\n");
				out.write("CFLAGS = -fPIC\n");
				out.write("LFLAGS = -shared\n");
				out.write("LIBS = -lGL -lGLU -lSDL -lSDL_image -lm\n");
				out.write("LIBDIR = /usr/lib\n");
				out.write("\n");
				out.write("#Packages\n");
				out.write("SRCS = ");

				// use the source builder to aggregate all the source files
				for (String s : fileLister.buildSourceList())
					out.write(s + " ");

				out.write("\n\n");
				out.write("OBJS = $(SRCS:.cpp=.o)\n");
				out.write("\n");
				out.write("MAIN = libXOR.so\n");
				out.write("\n");

				// delegate the rest to the parent
				generateMakefileBody(out);

				out.write("\n");
				out.close();

			} catch (FileNotFoundException e) {
				throw new RuntimeException(e);
			}

			return makefile;
		}

	}


}
