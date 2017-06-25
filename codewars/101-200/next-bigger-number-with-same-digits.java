/**
 * Created by ice1000 on 17-6-22.
 *
 * @author ice1000
 */
public class Kata {
		private static char[] array;

		private static void reverse(int begin, int end) {
				int mid = (begin + end) >> 1;
				int cnt = 0;
				while (true) {
						if (cnt > mid - begin) return;
						char t = array[begin + cnt];
						array[begin + cnt] = array[end - cnt];
						array[end - cnt] = t;
						cnt++;
				}
		}

		private static boolean nextPermutation(int begin, int end) {
				if (begin == end) return false;
				int i = end;
				for (; ; ) {
						int j = i--;
						if (array[i] < array[j]) {
								int t = end;
								while (array[i] >= array[t]) --t;
								char temp = array[i];
								array[i] = array[t];
								array[t] = temp;
								reverse(j, end);
								return true;
						}
						if (i == begin) {
								reverse(begin, end);
								return false;
						}
				}
		}

		public static long nextBiggerNumber(long n) {
				array = Long.toString(n).toCharArray();
				return nextPermutation(0, array.length - 1) ? Long.parseLong(new String(array)) : -1;
		}

		public static long nextSmaller(long n) {
				array = Long.toString(n).toCharArray();
				if (nextPermutation(0, array.length - 1)) {
						long a = Long.parseLong(new String(array));
						if (Long.toString(a).length() < array.length) return -1;
						else return a;
				} else return -1;
		}
}
