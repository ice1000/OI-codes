function padIt(str,n) {
		while (n --> 0) {
				if (n & 1) str = str + "*";
				else str = "*" + str;
		}
		return str;
}
