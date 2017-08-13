class Lcs {

	static String lcs(String a, String b) {
		if ("".equals(a) || "".equals(b)) return "";
		int[][] m = new int[a.length()][];
		for (int i = 0; i < m.length; i++) m[i] = new int[b.length()];
		for (int i = 0; i < a.length(); i++) {
			for (int j = 0; j < b.length(); j++) {
				if (a.charAt(i) == b.charAt(j)) m[i][j] = i != 0 && j != 0 ? m[i - 1][j - 1] + 1 : 1;
				else
					m[i][j] = i != 0 && j != 0 ? Math.max(m[i][j - 1], m[i - 1][j]) : i != 0 ? m[i - 1][j] : j != 0 ? m[i][j - 1] : 0;
			}
		}
		StringBuilder r = new StringBuilder();
		int i = a.length() - 1, j = b.length() - 1;
		while (i >= 0 && j >= 0) {
			if (a.charAt(i) == b.charAt(j)) {
				r.insert(0, a.charAt(i));
				i--;
				j--;
			}
			else {
				int x = i != 0 ? m[i - 1][j] : 0, y = j != 0 ? m[i][j - 1] : 0;
				if (x < y) j--;
				else i--;
			}
		}
		return r.toString();
	}
}
