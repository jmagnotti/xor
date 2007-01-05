package makehelp;

/**
 * @author John Magnotti s
 */
public class Make {
	public static void main(String[] args) {
		MakefileGenerator generator = MakefileGenerator.GetInstance();
		generator.generateMakefile();
	}
}
