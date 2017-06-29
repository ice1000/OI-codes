/**
 * Created by ice1000 on 17-6-29.
 *
 * @author ice1000
 */
public class Morpheus {
		public int[] find(Matrix matrix, int neo) {
				int size = matrix.size();
				int[] cat = new int[2];
				int low = 0;
				int high = size - 1;
				while (low < size && high >= 0) {
						if (matrix.get(low, high) == neo) {
								cat[0] = low;
								cat[1] = high;
								break;
						} else if (matrix.get(low, high) > neo) {
								high--;
						} else {
								low++;
						}
				}
				return cat;
		}
}
