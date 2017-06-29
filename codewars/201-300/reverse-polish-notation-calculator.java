import java.util.Stack;

/**
 * Created by ice1000 on 17-6-29.
 *
 * @author ice1000
 */
public class Calc {

		public double evaluate(String s) {
				if ("".equals(s)) return 0;
				String[] seq = s.split(" ");
				Stack<Double> stack = new Stack<>();
				for (String item : seq)
						switch (item) {
						case "+":
								stack.push(stack.pop() + stack.pop());
								break;
						case "-":	{
								double a = stack.pop();
								double b = stack.pop();
								stack.push(b - a);
						}
								break;
						case "*":
								stack.push(stack.pop() * stack.pop());
								break;
						case "/": {
								double a = stack.pop();
								double b = stack.pop();
								stack.push(b / a);
						}
								break;
						default:
								stack.push(Double.parseDouble(item));
						}
				try { return stack.lastElement(); }
				catch (Throwable e) { return 0; }
		}
}
