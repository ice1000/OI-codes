using System;
using System.Collections;

public static class Kata
{
		public static int sumTwoSmallestNumbers(int[] numbers0)
		{
				var numbers = new int[numbers0.Length];
				for (int i = 0; i < numbers0.Length; ++i) numbers[i] = numbers0[i];
				Array.Sort(numbers);
				return numbers[0] + numbers[1];
		}
}
