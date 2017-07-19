import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by ice1000 on 17-7-3.
 *
 * @author ice1000
 */
public class Simplexer implements Iterator<Token> {
		private Iterator<String> iterator;

		private static LinkedList<String> tokenize(String prog) {
				LinkedList<String> tokens = new LinkedList<>();
				Pattern pattern = Pattern.compile("[-+*/()%=\\[\\]]|[a-zA-Z]+|\\d+|\"[^\"]*\"|[ \n\t\r]+");
				Matcher m = pattern.matcher(prog);
				while (m.find()) tokens.add(m.group());
				return tokens;
		}
		
		public Simplexer(String buffer) {
				iterator = tokenize(null == buffer ? "" : buffer).iterator();
		}

		public static void main(String[] args) {
				List<Token> list = new ArrayList<>();
				new Simplexer(new Scanner(System.in).nextLine()).forEachRemaining(list::add);
				System.out.println(list);
		}

		@Override
		public boolean hasNext() {
				return iterator.hasNext();
		}

		@Override
		public Token next() {
				String next = iterator.next();
				if (Character.isDigit(next.charAt(0))) return new Token(next, "integer");
				if (Character.isWhitespace(next.charAt(0))) return new Token(next, "whitespace");
				if ('\"' == next.charAt(0)) return new Token(next, "string");
				switch (next) {
				case "true":
				case "false":
						return new Token(next, "boolean");
				case "if":
				case "else":
				case "return":
				case "func":
				case "break":
				case "while":
				case "for":
						return new Token(next, "keyword");
				case "+":
				case "-":
				case "*":
				case "/":
				case "(":
				case ")":
				case "=":
				case "%":
						return new Token(next, "operator");
				default:
						return new Token(next, "identifier");
				}
		}
}

