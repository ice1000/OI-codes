public class Morpheus {
		public int[] find(Matrix m, int neo) {
				for (int i = 0; i < m.size(); ++i)
						for (int j = 0; j < m.size(); ++j)
								if (m.get(i, j) == neo) return new int[]{i, j};
				throw new RuntimeException("shit");
		}
}
