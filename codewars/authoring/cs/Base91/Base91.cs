using System.Collections.Generic;
using System.Linq;

class Base91
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

	static Base91()
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

	public static string Decode(string input)
	{
		var output = "";
		var v = -1;
		var b = 0;
		var n = 0;
		foreach (var c in from c in
			(from t in input
				select _decodeTable[(byte) t])
			where c != -1
			select c)
		{
			if (v < 0) v = c;
			else
			{
				v += c * 91;
				b |= v << n;
				n += (v & 8191) > 88 ? 13 : 14;
				do
				{
					output += (char) (b & 255);
					b >>= 8;
					n -= 8;
				} while (n > 7);
				v = -1;
			}
		}
		if (v + 1 != 0)
			output += (char) ((b | v << n) & 255);
		return output;
	}
}