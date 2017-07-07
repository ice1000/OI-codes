using System.Linq;

public class Kata
{
		public static int Count(string str) => str.Count(c => c == '#');

		public static string AlphabetWar(string battle)
		{
				var chars = ("]" + battle + "[").Split('[', ']');
				var cloned = chars.Clone() as string[];
				var hasBomb = Count(battle) >= 1;
				for (var i = 1; i < chars.Length - 1; i++)
				{
						if (Count(cloned[i - 1]) + Count(cloned[i + 1]) >= 2
								|| Count(cloned[i]) >= 1
								|| hasBomb && (i & 1) == 1)
								chars[i] = "";
				}
				return string.Concat(chars);
		}
}
