using NUnit.Framework;
using System;
using System.Text;

[TestFixture]
public class Test
{
	private static Random R = new Random(DateTime.Now.Millisecond);

	private static string RandomString(int len)
	{
		var ret = new char[len];
		for (var j = 0; j < len; j++) ret[j] = (char) ((char) R.Next(26) + 97);
		return new string(ret);
	}

	[Test]
	public void FixedTests()
	{
		Assert.AreEqual("", LcsClass.Lcs("", ""));
		Assert.AreEqual("", LcsClass.Lcs("abc", ""));
		Assert.AreEqual("", LcsClass.Lcs("", "abc"));
		Assert.AreEqual("", LcsClass.Lcs("a", "b"));
		Assert.AreEqual("a", LcsClass.Lcs("a", "a"));
		Assert.AreEqual("ac", LcsClass.Lcs("abc", "ac"));
		Assert.AreEqual("abc", LcsClass.Lcs("abcdef", "abc"));
		Assert.AreEqual("acf", LcsClass.Lcs("abcdef", "acf"));
		Assert.AreEqual("nottest", LcsClass.Lcs("anothertest", "notatest"));
		Assert.AreEqual("12356", LcsClass.Lcs("132535365", "123456789"));
		Assert.AreEqual("final", LcsClass.Lcs("nothardlythefinaltest", "zzzfinallyzzz"));
		Assert.AreEqual("acdefghijklmnoq", LcsClass.Lcs("abcdefghijklmnopq", "apcdefghijklmnobq"));
	}

	private static string Lcs(string a, string b)
	{
		if ("".Equals(a) || "".Equals(b)) return "";
		var m = new int[a.Length][];
		for (var iii = 0; iii < m.Length; iii++) m[iii] = new int[b.Length];
		for (var ili = 0; ili < a.Length; ili++)
		for (var lil = 0; lil < b.Length; lil++)
			if (a[ili] == b[lil]) m[ili][lil] = ili != 0 && lil != 0 ? m[ili - 1][lil - 1] + 1 : 1;
			else
				m[ili][lil] = ili != 0 && lil != 0
					? Math.Max(m[ili][lil - 1], m[ili - 1][lil])
					: ili != 0
						? m[ili - 1][lil]
						: lil != 0
							? m[ili][lil - 1]
							: 0;
		var r = new StringBuilder();
		int i = a.Length - 1, j = b.Length - 1;
		while (i >= 0 && j >= 0)
			if (a[i] == b[j])
			{
				r.Insert(0, a[i]);
				i--;
				j--;
			}
			else
			{
				int x = i != 0 ? m[i - 1][j] : 0, y = j != 0 ? m[i][j - 1] : 0;
				if (x < y) j--;
				else i--;
			}
		return r.ToString();
	}

	private static void Try(string a, string b)
	{
		Assert.AreEqual(Lcs(a, b), LcsClass.Lcs(a, b));
	}

	[Test]
	public void IntermediateRandomTest()
	{
		for (var i = 0; i < 72; i++) Try(RandomString(20), RandomString(20));
	}

	[Test]
	public void HardRandomTest()
	{
		for (var i = 0; i < 24; i++) Try(RandomString(400), RandomString(400));
	}

	[Test]
	public void ExtremeRandomTest()
	{
		for (var i = 0; i < 12; i++) Try(RandomString(6000), RandomString(6000));
	}
}