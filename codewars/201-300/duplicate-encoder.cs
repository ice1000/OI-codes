using System.Linq;

public class Kata
{
		public static string DuplicateEncode(string s)
		{
				return new string(s.ToLower().Select(c => s.ToLower().Count(i => c == i) == 1 ? '(' : ')').ToArray());
		}
}
