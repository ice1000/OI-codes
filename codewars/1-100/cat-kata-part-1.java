import java.util.ArrayList;
import java.util.List;

public class PeacefulYard {
		static class Point {
				private int x, y;
				
				double dis(Point p) {
						int a = x - p.x;
						int b = y - p.y;
						return Math.sqrt(a * a + b * b);
				}
				
				Point(int x, int y) {
						this.x = x;
						this.y = y;
				}
		}

		public static boolean peacefulYard(String[] yard, int minDistance) {
				List<Point> ls = new ArrayList<>(1000);
				for (int i = 0, yardLength = yard.length; i < yardLength; i++) {
						String line = yard[i];
						for (int j = 0, lineLength = line.length(); j < lineLength; j++)
								if ('-' != line.charAt(j)) ls.add(new Point(i, j));
				}
				for (Point i : ls) for (Point j : ls) if (i != j && i.dis(j) < minDistance) return false;
				return true;
		}
}

