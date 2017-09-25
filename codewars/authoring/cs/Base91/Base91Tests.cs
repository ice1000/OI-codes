using System;
using System.Collections.Generic;
using NUnit.Framework;

[TestFixture]
public class Base91Tests
{
	private static class Solution
	{
		private static readonly char[] EncodeTable =
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$',
			'%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=',
			'>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '"'
		};

		private static Dictionary<byte, int> _decodeTable;

		static Solution()
		{
			InitDecodeTable();
		}

		private static void InitDecodeTable()
		{
			_decodeTable = new Dictionary<byte, int>();
			for (var i = 0; i < 255; i++)
				_decodeTable[(byte) i] = -1;
			for (var i = 0; i < EncodeTable.Length; i++)
				_decodeTable[(byte) EncodeTable[i]] = i;
		}

		public static string Encode(string input)
		{
			var output = "";
			var b = 0;
			var n = 0;
			foreach (var t in input)
			{
				b |= (byte) t << n;
				n += 8;
				if (n <= 13) continue;
				var v = b & 8191;
				if (v > 88)
				{
					b >>= 13;
					n -= 13;
				}
				else
				{
					v = b & 16383;
					b >>= 14;
					n -= 14;
				}
				output += EncodeTable[v % 91];
				output += EncodeTable[v / 91];
			}
			if (n == 0) return output;
			output += EncodeTable[b % 91];
			if (n > 7 || b > 90)
				output += EncodeTable[b / 91];
			return output;
		}
	}

	[Test]
	public void FixedTests()
	{
		Assert.AreEqual(Base91.Encode("test"), "fPNKd");
		Assert.AreEqual(Base91.Encode("Hello World!"), ">OwJh>Io0Tv!8PE");
		Assert.AreEqual(Base91.Decode("fPNKd"), "test");
		Assert.AreEqual(Base91.Decode(">OwJh>Io0Tv!8PE"), "Hello World!");
	}

	[Test]
	public void RandomTests()
	{
		var random = new Random(DateTime.Now.Millisecond);
		for (var i = 0; i < 200; i++)
		{
			var origin = string.Format("%s%s%s%s%s%s%s%s%s%s%s",
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString(),
				(random.NextDouble() * 10000).ToString());
			var encodNd = Solution.Encode(origin);
			Assert.AreEqual(Base91.Encode(origin), encodNd);
			Assert.AreEqual(Base91.Decode(encodNd), origin);
		}
	}
}