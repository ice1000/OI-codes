import java.util.Stack;

/**
 * Created by ice1000 on 17-6-29.
 *
 * @author ice1000
 */
public class Evaluator {
		public long evaluate(String s) {
				String[] seq = s.split(" ");
				Stack<Long> stack = new Stack<>();
				for (String item : seq)
						switch (item) {
						case "+":
								stack.push(stack.pop() + stack.pop());
								break;
						case "-":
								stack.push(stack.pop() - stack.pop());
								break;
						case "*":
								stack.push(stack.pop() * stack.pop());
								break;
						case "/":
								long a = stack.pop();
								long b = stack.pop();
								stack.push(b / a);
								break;
						default:
								stack.push(Long.parseLong(item));
						}
				return stack.firstElement();
		}
}
