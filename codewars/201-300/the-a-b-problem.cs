public class Kata
{
		public static int problem(int A, int B)
		{
				int C = (A - B);
				if (C % 10 == 0) return C + 1;
				return C / 10 * 10;
		}
}
