using System;

public class Complex
{
		private static double Hypot(double a, double b)
		{
				a = Math.Abs(a);
				b = Math.Abs(b);
				double d1;
				double d2;
				if (a < b)
				{
						d1 = a;
						d2 = b;
				}
				else
				{
						d1 = b;
						d2 = a;
				}
				if (Math.Abs(d1) < 0.0000000001)
						return d2;
				if (double.IsPositiveInfinity(d2) && !double.IsNaN(d1))
						return double.PositiveInfinity;
				double num = d1 / d2;
				return d2 * Math.Sqrt(1.0 + num * num);
		}

		public static double[] Log(double[] z)
		{
				double x = z[0]; // Real part of z = x + iy
				double y = z[1]; // Imaginary part of z = x + iy
				if (x == 0 && y == 0) throw new ArgumentException();
				return new[] {Math.Log(Hypot(x, y)), Math.Atan2(y, x)};
		}
}
