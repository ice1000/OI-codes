public class Kata
{
		public static string AlphabetWar(string fight)
		{
				var l = 0;
				var r = 0;
				foreach (var c in fight)
				{
						l += c == 'w' ? 4 : c == 'p' ? 3 : c == 'b' ? 2 : c == 's' ? 1 : 0;
						r += c == 'm' ? 4 : c == 'q' ? 3 : c == 'd' ? 2 : c == 'z' ? 1 : 0;
				}
				return l > r ? "Left side wins!" : l == r ? "Let's fight again!" : "Right side wins!";
		}
}
