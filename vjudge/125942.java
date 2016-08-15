import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	private static BigInteger[] fib = new BigInteger[10005];

	private static BigInteger getFib(int n) {
		if (n == 3) return new BigInteger("4");
		if (n == 4) return new BigInteger("7");
		if (fib[n] != null) return fib[n];
		return fib[n] = getFib(n - 1).add(getFib(n - 2));
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		while (scanner.hasNext()) System.out.println(getFib(scanner.nextInt()));
	}
}
