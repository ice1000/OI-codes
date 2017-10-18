using System;
using NUnit.Framework;

[TestFixture]
public class ImmortalTest
{
	private static long _date;
	private static long _passed;
	private static bool _good = true;
	private readonly Random _random = new Random(DateTime.Now.Millisecond);

	[TestFixtureSetUp]
	public static void Init()
	{
		_date = DateTime.Now.Millisecond;
	}

	[Test]
	public void Example()
	{
		Assert.AreEqual((long) 5, Immortal.ElderAge(8, 5, 1, 100));
		Assert.AreEqual((long) 224, Immortal.ElderAge(8, 8, 0, 100007));
		Assert.AreEqual((long) 11925, Immortal.ElderAge(25, 31, 0, 100007));
		Assert.AreEqual((long) 4323, Immortal.ElderAge(5, 45, 3, 1000007));
		Assert.AreEqual((long) 1586, Immortal.ElderAge(31, 39, 7, 2345));
		Assert.AreEqual((long) 808451, Immortal.ElderAge(545, 435, 342, 1000007));
		// You need to run this test very quickly before attempting the actual tests :)
		Assert.AreEqual((long) 5456283, Immortal.ElderAge(28827050410L, 35165045587L, 7109602, 13719506));
	}

	[Test]
	public void TheElderIsInterested()
	{
		Console.WriteLine(
			"<p><font color=\"green\">100 test cases\\nm,n: 2^5 - 2^10\\nl: 0 - 19\\nt: 2^5 - 2^15</font></p>");
		Console.WriteLine("Young man, you should learn a thing or two...");
		for (var i = 0; i < 100; i++)
		{
			long m = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 5 + 5)),
				n = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 5 + 5)),
				l = (long) (_random.NextDouble() * 20),
				t = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 10 + 5));
			long expected = Immortal2.ElderAge(m, n, l, t), actual = Immortal.ElderAge(m, n, l, t);
			if (expected != actual)
			{
				_good = false;
				if (Immortal.Debug)
					Console.WriteLine("The Elder says: \\n<p><font color=\"yellow\">m=" + m + ", n=" + n + ", l=" + l + ", t=" + t +
					                  "</font></p>");
			}
			else _passed++;
			Assert.AreEqual(expected, actual);
		}
	}

	[Test]
	public void TheElderIsExcited()
	{
		Console.WriteLine(
			"<p><font color=\"yellow\">300 test cases\\nm,n: 2^8 - 2^20\\nl: 0 - 9999\\nt: 2^10 - 2^20</font></p>");
		Console.WriteLine("You're too young and too simple!");
		for (int i = 0; i < 300; i++)
		{
			long m = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 12 + 8)),
				n = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 12 + 8)),
				l = (long) (_random.NextDouble() * 10000),
				t = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 10 + 10));
			long expected = Immortal2.ElderAge(m, n, l, t), actual = Immortal.ElderAge(m, n, l, t);
			if (expected != actual)
			{
				_good = false;
				if (Immortal.Debug)
					Console.WriteLine("The Elder says: \\n<p><font color=\"yellow\">m=" + m + ", n=" + n + ", l=" + l + ", t=" + t +
					                  "</font></p>");
			}
			else _passed++;
			Assert.AreEqual(expected, actual);
		}
	}

	[Test]
	public void TheElderIsAngry()
	{
		Console.WriteLine(
			"<p><font color=\"red\">500 test cases\\nm,n: 2^32 - 2^48\\nl: 0 - 9999999\\nt: 2^16 - 2^26</font></p>");
		Console.WriteLine("And sometimes naive!");
		for (int i = 0; i < 500; i++)
		{
			long m = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 16 + 32)),
				n = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 16 + 32)),
				l = (long) (_random.NextDouble() * 1e7),
				t = (long) Math.Floor(Math.Pow(2, _random.NextDouble() * 10 + 16));
			long expected = Immortal2.ElderAge(m, n, l, t), actual = Immortal.ElderAge(m, n, l, t);
			if (expected != actual)
			{
				_good = false;
				if (Immortal.Debug)
					Console.WriteLine("The Elder says: \\n<p><font color=\"yellow\">m=" + m + ", n=" + n + ", l=" + l + ", t=" + t +
					                  "</font></p>");
			}
			else _passed++;
			Assert.AreEqual(expected, actual);
		}
	}

	[TestFixtureTearDown]
	public static void End()
	{
		long end = DateTime.Now.Millisecond;
		var timeDiff = (_date - end) / 1000;
		if (_passed >= 900)
		{
			Console.WriteLine("You spent.. " + timeDiff + "ms");
			Console.WriteLine(timeDiff <= 1
				? "You finished all the tests within 1 second. The Elder is very happy! +1s"
				: "The Elder is pleased!");
		}
		else
		{
			Console.WriteLine("The Elder is displeased!");
			Assert.Fail();
		}
	}
}

public static class Immortal2
{
	private static long _p = (int) 1e9;

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