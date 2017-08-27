public class Max {
		static int m(int[] arr, int len) {
				int max = arr[0];
				for (int i = 0; i < len; i++) {
						int sum = 0;
						for (int j = i; j < len; j++) {
								sum += arr[j];
								if (sum > max) max = sum;
						}
				}
				return max;
		}

		public static int sequence(int[] arr) {
				if (arr.length == 0) return 0;
				return m(arr, arr.length);
		}
}
