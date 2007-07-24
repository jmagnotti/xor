package main;

public class LogMaker {

	public static void main(String[] args) {
		System.out.println("Logs:");

		for (double d = 1.0; d < 100; d += .1)
			System.out.println(d + ":\t" + Math.log(d));
	}
}
