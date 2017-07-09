using System.Linq;

public class Kata
{
		public static int[] SortArray(int[] a)
		{
				var sorted = a
						.Where(p => (p & 1) > 0)
						.OrderBy(p => p)
						.ToArray();
				var idx = 0;
				for (var j = 0; j < a.Length; j++)
						a[j] = (a[j] & 1) > 0 ? sorted[idx++] : a[j];
				return a;
		}
}
