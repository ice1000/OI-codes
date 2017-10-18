using System;

public static class Immortal
{
	private static long _p = (int) 1e9;

	/// set true to enable debug
	public static bool Debug = false;

	private static int Log2(long x)
	{
		var ans = 0;
		while ((x >>= 1) != 0) ans++;
		return ans;
	}

	private static long Mul(long x, long y, long z)
	{
		if (z != 2) return x % _p * (y % _p) % _p;
		if ((x & 1) != 0) y >>= 1;
		else if ((y & 1) != 0) x >>= 1;
		else throw new Exception("shit");
		return x % _p * (y % _p) % _p;
	}

	private static long SumTimes(long first, long n, long k, long t)
	{
		first -= k;
		if (first >= 1) return n <= 0 ? 0 : Mul(Mul(first + first + n - 1, n, 2L), t, 1);
		n -= 1 - first;
		first = 1;
		return n <= 0 ? 0 : Mul(Mul(first + first + n - 1, n, 2L), t, 1);
	}

	public static long ElderAge(long n, long m, long k, long newp)
	{
		if (n == 0 || m == 0) return 0;
		if (k < 0) k = 0;
		if (n < m)
		{
			var tmp = n;
			n = m;
			m = tmp;
		}
		_p = newp;
		if (n == m && (n & -n) == n) return SumTimes(1, n - 1, k, m);
		int nn = Log2(n), mm = Log2(m);
		long centerWidth = 1L << nn, centerHeight = 1L << mm;
		if (nn == mm)
		{
			long rightWidth = n - centerWidth, bottomHeight = m - centerHeight;
			var bottomSum = SumTimes(centerHeight, centerWidth, k, bottomHeight);
			return ((SumTimes(centerWidth, centerHeight, k, rightWidth) + bottomSum) % _p +
			        (ElderAge(rightWidth, bottomHeight, k, _p) + ElderAge(centerWidth, centerHeight, k, _p)) % _p) % _p;
		}
		var leftWidth = 1L << nn;
		var leftSum = SumTimes(0, leftWidth, k, m);
		var rightSum = ElderAge(n - leftWidth, m, k - leftWidth, _p);
		if (leftWidth <= k) return (leftSum + rightSum) % _p;
		rightSum += Mul(Mul(leftWidth - k, m, 1), n - leftWidth, 1);
		rightSum %= _p;
		return (leftSum + rightSum) % _p;
	}
}