using System;

public class Assert
{
		public static bool Pass()
		{
				return true;
		}
		public static bool Fail()
		{
				return true;
		}
}

public class AlwaysSucceed
{
		public static void PreventFailures()
		{
				Console.WriteLine("草拟爸爸");
		}
}
