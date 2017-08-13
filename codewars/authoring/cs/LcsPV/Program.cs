using System;
using System.Text;

class LcsClass
{
	public static string Lcs(string a, string b)
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
}