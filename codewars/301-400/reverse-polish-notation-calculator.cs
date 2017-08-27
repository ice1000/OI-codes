using System;
using System.Linq;
using System.Collections.Generic;

public class Calc
{
		public double evaluate(string expr)
		{
				if ("".Equals(expr)) return 0;
				var stack = new Stack<double>();
				var split = expr.Split(' ');
				foreach (var sym in split)
						try
						{
								stack.Push(double.Parse(sym));
						}
				catch (Exception)
				{
						var b = stack.Pop();
						var a = stack.Pop();
						switch (sym)
						{
								case "+":
										stack.Push(a + b);
										break;
								case "-":
										stack.Push(a - b);
										break;
								case "*":
										stack.Push(a * b);
										break;
								case "/":
										stack.Push(a / b);
										break;
						}
				}
				return stack.Pop();
		}
}

