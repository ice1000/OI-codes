import java.math.BigInteger;
import java.util.Scanner;

/**
 * Created by ice1000 on 2016/8/17.
 *
 * @author ice1000
 */
public class Main {
	private static BigInteger[] fib = new BigInteger[10005];

	private static BigInteger getFib(int n) {
		if (n == 1 || n == 0) return new BigInteger("1");
		if (fib[n] != null) return fib[n];
		return fib[n] = getFib(n - 1).add(getFib(n - 2));
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int t = scanner.nextInt();
		while (t-- > 0) System.out.println(getFib(scanner.next().length()));
	}
}
